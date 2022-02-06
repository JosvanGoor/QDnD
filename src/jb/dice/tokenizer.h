#ifndef JB_DICE_TOKENIZER_H
#define JB_DICE_TOKENIZER_H

#include <string>
#include <vector>

namespace jb::dice
{

    enum class TokenType
    {
        // complex ops
        DIE,                // 'd'  !
        DIE_ADVANTAGE,      // 'ad' !
        DIE_DISADVANTAGE,   // 'dd' !
        KEEP_HIGHEST,       // 'kh' !
        KEEP_LOWEST,        // 'kl' !
        DROP_HIGHEST,       // 'dh' !
        DROP_LOWEST,        // 'dl' !
        EXPLODE,            // 'e'  !
        REROLL_ONCE,        // 'ro'
        REROLL,             // 'rr'

        // binary ops
        PLUS,               // '+'
        MINUS,              // '-'

        // control characters
        COMMA,              // ','

        // literals
        NUMBER,             // ( '0' ... '9' )+
        MESSAGE,            // ( any_character )+

        // control
        END_OF_EXPRESSION
    };

    struct Token
    {
        TokenType type;
        std::string literal;

        std::uint16_t parse_number() const;
    };


    class Tokenizer
    {
        std::size_t _caret;
        std::string _expression;

        public:
            Tokenizer(std::string&& expression);
            Tokenizer(const std::string& expression);

            std::vector<Token> tokenize();

        private:
            Token number();
            Token message();

            bool at_end() const noexcept;
            char peek() const noexcept;
            char peek_next() const noexcept;
            char advance() noexcept;
            bool match(char ch) noexcept;
            void skip_whitespace();
    };

}

#endif