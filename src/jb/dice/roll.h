#ifndef JB_DICE_ROLL_H
#define JB_DICE_ROLL_H

#include <cstdint>

#include "rollresult.h"

namespace jb::dice
{

    class Roll
    {
        std::string _message;
        std::vector<RollResult> _results;

        public:
            Roll() = default;
            explicit Roll(const RollResult& result);

            void merge(const Roll& roll);
            void add_result(const RollResult& result);
            void add_message(const std::string& message);

            std::int32_t score() const;
            RollResult& most_recent();
            const std::string& message() const;
            const std::vector<RollResult>& results() const;

            void negate();
            void explode(const std::set<std::uint16_t> set);
            void reroll(const std::set<std::uint16_t> set);
            void reroll_once(const std::set<std::uint16_t> set);
    };

}

#endif