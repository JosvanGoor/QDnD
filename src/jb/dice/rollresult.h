#ifndef JB_DICE_ROLLRESULT_H
#define JB_DICE_ROLLRESULT_H

#include <cstdint>
#include <random>
#include <set>
#include <string>
#include <vector>

namespace jb::dice
{

    struct RollValue
    {
        static constexpr std::uint16_t PLAIN_VALUE      = 0b1;
        static constexpr std::uint16_t ROLL_VALUE       = 0b10;
        static constexpr std::uint16_t MAXIMUM_VALUE    = 0b100;
        static constexpr std::uint16_t MINIMUM_VALUE    = 0b1000;
        static constexpr std::uint16_t EXPLODED_DIE     = 0b10000;
        static constexpr std::uint16_t REJECTED         = 0b100000;
        
        std::uint16_t value = 0;
        std::uint16_t flags = PLAIN_VALUE | REJECTED;
    };

    class RollResult
    {
        static std::default_random_engine random_generator;

        bool _negative;
        std::uint16_t _number;
        std::uint16_t _sides;
        std::string _display;
        std::uint16_t _filter_limit;
        std::vector<RollValue> _result;
        std::uniform_int_distribution<std::uint16_t> _distribution;

        public:
            RollResult();
            RollResult(std::uint16_t number,  std::uint16_t sides);

            void explode(const std::set<std::uint16_t>& exploders);
            void reroll_once(const std::set<std::uint16_t>& rerollers);
            void reroll(const std::set<std::uint16_t>& rerollers);
            void keep_higest(std::uint16_t number);
            void drop_highest(std::uint16_t number);

            bool is_negative() const;
            std::uint16_t number() const;
            const std::string& display() const;
            const std::vector<RollValue>& result() const;

            void reject();
            void negate();
            std::int32_t score() const;
            void merge(const RollResult& result);
            void feed_value(const RollValue& value);
            void set_display(const std::string& display);

            std::string debug_print() const;

        private:
            void roll();
            void limit_check();
            RollValue generate();
            std::vector<size_t> sort_indices();
    };

}

#endif
