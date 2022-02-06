#include "tokenizer.h"

#include <charconv>

#include "../common/exceptions.h"

namespace jb::dice
{

    std::uint16_t Token::parse_number() const
    {
        std::uint16_t rval;
        if (auto [ptr, ec] = std::from_chars(literal.data(), literal.data() + literal.size(), rval, 10); ec == std::errc())
            return rval;
        throw ParserException{"Failed to parse number from literal '{}'", literal};
    }


    Tokenizer::Tokenizer(std::string&& expression)
    :   _caret(0),
        _expression(move(expression))
    { }

    
    Tokenizer::Tokenizer(const std::string& expression)
    :   _caret(0),
        _expression(expression)
    { }


    std::vector<Token> Tokenizer::tokenize()
    {
        std::vector<Token> rval;

        while (!at_end())
        {
            skip_whitespace();

            if (std::isdigit(peek()))
            {
                rval.push_back(number());
                continue;
            }

            switch(advance())
            {
                // single char
                case '+':
                    rval.push_back(Token{TokenType::PLUS, "+"});
                break;

                case '-':
                    rval.push_back(Token{TokenType::MINUS, "-"});
                break;

                case ',':
                    rval.push_back(Token{TokenType::COMMA, ","});
                break;

                case ':':
                    rval.push_back(message());
                break;

                case 'a':
                    if (match('d'))
                    {
                        rval.push_back(Token{TokenType::DIE_ADVANTAGE, "ad"});
                        break;
                    }
                    throw ParserException{"Unknown token 'a{}'.", peek()};

                case 'd':
                    if (match('d'))
                        rval.push_back(Token{TokenType::DIE_DISADVANTAGE, "dd"});
                    else if (match('h'))
                        rval.push_back(Token{TokenType::DROP_HIGHEST, "dh"});
                    else if (match('l'))
                        rval.push_back(Token{TokenType::DROP_LOWEST, "dl"});
                    else
                        rval.push_back(Token{TokenType::DIE, "d"});
                break;

                case 'e':
                    rval.push_back(Token{TokenType::EXPLODE, "e"});
                break;

                case 'k':
                    if (match('h'))
                        rval.push_back(Token{TokenType::KEEP_HIGHEST, "kh"});
                    else if (match('l'))
                        rval.push_back(Token{TokenType::KEEP_LOWEST, "kl"});
                    else
                        throw ParserException{"Unknown token 'k{}'.", peek()};
                break;

                case 'r':
                    if (match('o'))
                        rval.push_back(Token{TokenType::REROLL_ONCE, "ro"});
                    else if (match('r'))
                        rval.push_back(Token{TokenType::REROLL, "rr"});
                    else
                        throw RuntimeException{"Unknown token 'r{}'.", peek()};
                break;

                default:
                    throw RuntimeException{"Unknown token '{}'.", _expression[_caret - 1]};
            }
        }

        return rval;
    }


    Token Tokenizer::number()
    {
        std::size_t start = _caret;
        while (std::isdigit(peek()))
            advance();
        return Token{TokenType::NUMBER, _expression.substr(start, (_caret - start))};
    }


    Token Tokenizer::message()
    {
        skip_whitespace();
        std::string rval = _expression.substr(_caret);
        _caret = _expression.size();
        return Token{TokenType::MESSAGE, rval};
    }


    bool Tokenizer::at_end() const noexcept
    {
        return _caret == _expression.size();
    }


    char Tokenizer::peek() const noexcept
    {
        if (at_end())
            return '\0';
        return _expression[_caret];
    }


    char Tokenizer::peek_next() const noexcept
    {
        if ((_caret + 1) >= _expression.size())
            return '\0';
        return _expression[_caret + 1];
    }


    char Tokenizer::advance() noexcept
    {
        if (at_end())
            return '\0';
        ++_caret;
        return _expression[_caret - 1];
    }


    bool Tokenizer::match(char ch) noexcept
    {
        if (peek() == ch)
        {
            advance();
            return true;
        }

        return false;
    }


    void Tokenizer::skip_whitespace()
    {
        while (true)
        {
            switch (peek())
            {
                case ' ':   [[fallthrough]];
                case '\n':  [[fallthrough]];
                case '\t':
                    advance();
                break;

                default:
                    return;
            }
        }
    }

}