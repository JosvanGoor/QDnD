#include "roll.h"

#include "../common/exceptions.h"

namespace jb::dice
{

    Roll::Roll(const RollResult& result)
    {
        _results.push_back(result);
    }


    void Roll::merge(const Roll& roll)
    {
        _message += roll._message;
        for (auto &result : roll._results)
            _results.push_back(result);
    }


    void Roll::add_result(const RollResult& result)
    {
        _results.push_back(result);
    }


    void Roll::add_message(const std::string& message)
    {
        _message = message;
    }


    std::int32_t Roll::score() const
    {
        std::int32_t val = 0;
        for (auto const &result : _results)
            val += result.score();
        return val;
    }


    RollResult& Roll::most_recent()
    {
        if (_results.empty())
            throw LogicException{"No 'recent' RollResult in Roll."};
        return _results.back();
    }


    const std::string& Roll::message() const
    {
        return _message;
    }


    const std::vector<RollResult>& Roll::results() const
    {
        return _results;
    }


    void Roll::negate()
    {
        for (auto& roll : _results)
            roll.negate();
    }


    void Roll::explode(const std::set<std::uint16_t> set)
    {
        for (auto& result : _results)
            result.explode(set);
    }
            
            
    void Roll::reroll(const std::set<std::uint16_t> set)
    {
        for (auto& result : _results)
            result.reroll(set);
    }
    
    
    void Roll::reroll_once(const std::set<std::uint16_t> set)
    {
        for (auto& result : _results)
            result.reroll_once(set);
    }
}