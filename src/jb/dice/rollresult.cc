#include "rollresult.h"

#include <algorithm>
#include <random>
#include <fmt/core.h>
#include <time.h>

#include "../common/exceptions.h"

namespace jb::dice
{

    // RNG for all rollers
    static std::default_random_engine random_generator{static_cast<std::uint32_t>(time(nullptr))};


    RollResult::RollResult()
    :   _negative(false),
        _number(0),
        _sides(0),
        _display(),
        _filter_limit(0),
        _result(),
        _distribution()
    { }


    RollResult::RollResult(std::uint16_t number, std::uint16_t sides)
    :   _negative(false),
        _number(number),
        _sides(sides),
        _display(),
        _filter_limit(0),
        _result(),
        _distribution(1, sides)
    {
        roll();
        _display = fmt::format("{}d{}", _number, _sides);
    }


    void RollResult::explode(const std::set<std::uint16_t>& exploders)
    {
        _filter_limit = 0;
        std::vector<RollValue> exploded;

        for (const auto& result : _result)
        {
            exploded.push_back(result);
            if ((result.flags & RollValue::REJECTED) != 0)
                continue;

            while (exploders.find(exploded.back().value) != exploders.end())
            {
                limit_check();
                exploded.push_back(generate());
                exploded.back().flags |= RollValue::EXPLODED_DIE;
            }
        }

        _result.swap(exploded);
    }


    void RollResult::reroll_once(const std::set<std::uint16_t>& rerollers)
    {
        std::vector<RollValue> rerolled;

        for (const auto& result : _result)
        {
            rerolled.push_back(result);
            if ((result.flags & RollValue::REJECTED) != 0)
                continue;
            
            if (rerollers.find(result.value) != rerollers.end())
            {
                rerolled.back().flags |= RollValue::REJECTED;
                rerolled.push_back(generate());
            }
        }

        _result.swap(rerolled);
    }

    
    void RollResult::reroll(const std::set<std::uint16_t>& rerollers)
    {
        _filter_limit = 1000;
        std::vector<RollValue> rerolled;

        for (const auto& result : _result)
        {
            rerolled.push_back(result);
            if ((result.flags & RollValue::REJECTED) != 0)
                continue;

            while (rerollers.find(rerolled.back().value) != rerollers.end())
            {
                limit_check();
                rerolled.back().flags |= RollValue::REJECTED;
                rerolled.push_back(generate());
            }
        }

        _result.swap(rerolled);
    }


    void RollResult::keep_higest(std::uint16_t amount)
    {
        auto sorted_indices = sort_indices();

        for (auto it = sorted_indices.rbegin(); it != sorted_indices.rend(); ++it)
        {
            if (amount == 0)
                _result[*it].flags |= RollValue::REJECTED;
            else if ((_result[*it].flags & RollValue::REJECTED) == 0)
                --amount;
        }
    }


    void RollResult::drop_highest(std::uint16_t amount)
    {
        auto sorted_indices = sort_indices();

        for (auto it = sorted_indices.rbegin(); it != sorted_indices.rend(); ++it)
        {
            if (amount == 0)
                break;

            if ((_result[*it].flags & RollValue::REJECTED) == 0)
            {
                _result[*it].flags |= RollValue::REJECTED;
                --amount;
            }
        }
    }

    bool RollResult::is_negative() const
    {
        return _negative;
    }


    std::uint16_t RollResult::number() const
    {
        return _number;
    }


    const std::string& RollResult::display() const
    {
        return _display;
    }


    const std::vector<RollValue>& RollResult::result() const
    {
        return _result;
    }


    void RollResult::reject()
    {
        for (auto& roll : _result)
            roll.flags |= RollValue::REJECTED;
    }


    void RollResult::negate()
    {
        _negative = !_negative;
    }


    std::int32_t RollResult::score() const
    {
        std::int32_t value = 0;
        for (auto &roll : _result)
        {
            if ((roll.flags & RollValue::REJECTED) == 0)
                value += roll.value;
        }
        return _negative ? -value : value;
    }


    void RollResult::merge(const RollResult& result)
    {
        for (auto& roll : result._result)
            _result.push_back(roll);
    }


    void RollResult::feed_value(const RollValue& value)
    {
        _result.push_back(value);
    }


    void RollResult::set_display(const std::string& display)
    {
        _display = display;
    }


    std::string RollResult::debug_print() const
    {
        std::string rval;

        rval += _display + ": ";
        if (_negative) rval += "-";
        rval += "(";

        for (auto &val : _result)
        {
            if (val.flags & RollValue::REJECTED)
                rval += fmt::format("_{}_", val.value);
            else if (val.flags & RollValue::EXPLODED_DIE)
                rval += fmt::format("*{}*", val.value);
            else
                rval += fmt::format("[{}]", val.value);
        }
        rval += ")";
        return rval;
    }


    void RollResult::roll()
    {
        for (std::uint16_t epoch = _number; epoch--; )
            _result.push_back(generate());
    }


    void RollResult::limit_check()
    {
        if (--_filter_limit == 0)
            throw RuntimeException{"Hit filter limit."};
    }


    RollValue RollResult::generate()
    {
        RollValue value{_distribution(random_generator), RollValue::ROLL_VALUE};
        if (value.value == 1)
            value.flags |= RollValue::MINIMUM_VALUE;
        if (value.value == _sides)
            value.flags |= RollValue::MAXIMUM_VALUE;
        return value;
    }


    std::vector<std::size_t> RollResult::sort_indices()
    {
        std::vector<size_t> indices(_result.size());
        std::iota(indices.begin(), indices.end(), 0);

        std::stable_sort(indices.begin(), indices.end(),
            [&](std::size_t lhs, std::size_t rhs)
            {
                return _result[lhs].value < _result[rhs].value;
            });

        return indices;
    }

}
