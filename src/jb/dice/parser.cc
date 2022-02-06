#include "parser.h"

#include "../common/exceptions.h"

namespace jb::dice
{

    Parser::Parser(const std::string& expression)
    :   _caret(0),
        _tokens()
    {
        Tokenizer tokenizer{expression};
        _tokens = tokenizer.tokenize();
    }


    ExpressionPtr Parser::parse()
    {
        return expression();
    }


    ExpressionPtr Parser::expression()
    {
        ExpressionPtr ptr = addition();
        
        if (peek().type == TokenType::MESSAGE)
            ptr = std::make_unique<MessageExpression>(std::move(ptr), advance().literal);
        
        if (!at_end())
            throw ParserException{"No path till end of expression."};

        return ptr;
    }


    ExpressionPtr Parser::addition()
    {
        ExpressionPtr lhs = unary();

        while (match({TokenType::PLUS, TokenType::MINUS}))
        {
            Token op = peek_previous();
            ExpressionPtr rhs = unary();
            lhs = std::make_unique<BinaryExpression>(op.type, std::move(lhs), std::move(rhs));
        }

        return lhs;
    }


    ExpressionPtr Parser::unary()
    {
        ExpressionPtr ptr;

        if (match(TokenType::MINUS))
            ptr = std::make_unique<NegateExpression>(roll());
        else
            ptr = roll();

        return ptr;
    }


    ExpressionPtr Parser::roll()
    {
        bool has_number = false;
        Token value;

        if (peek().type == TokenType::NUMBER)
        {
            value = advance();
            has_number = true;
        }

        if (match({TokenType::DIE, TokenType::DIE_ADVANTAGE, TokenType::DIE_DISADVANTAGE}))
        {
            Token type = peek_previous();
            if (peek().type != TokenType::NUMBER)
                throw ParserException{"Expected number after die token."};

            ExpressionPtr expr = std::make_unique<RollExpression>(type.type, has_number ? value.parse_number() : std::uint16_t(1), advance().parse_number());

            while (has_rollmod())
                expr = rollmod(std::move(expr));
            return expr;
        }
        else if (has_number)
            return std::make_unique<ValueExpression>(value.parse_number());
        else
            throw ParserException{"Unexpected token expected number or dietoken."};
    }

    bool Parser::has_rollmod()
    {
        switch (peek().type)
        {
            case TokenType::DROP_HIGHEST:   [[fallthrough]];
            case TokenType::DROP_LOWEST:    [[fallthrough]];
            case TokenType::KEEP_HIGHEST:   [[fallthrough]];
            case TokenType::KEEP_LOWEST:    [[fallthrough]];
            case TokenType::EXPLODE:        [[fallthrough]];
            case TokenType::REROLL:         [[fallthrough]];
            case TokenType::REROLL_ONCE:
                return true;
            default: break;
        }
        return false;
    }


    ExpressionPtr Parser::rollmod(ExpressionPtr&& roll)
    {
        if (match({TokenType::EXPLODE, TokenType::REROLL, TokenType::REROLL_ONCE}))
        {
            Token op = peek_previous();
            return std::make_unique<FilterExpression>(op.type, std::move(roll), arglist());
        }

        Token op = advance(); // must be drop/keep token.
        if (peek().type != TokenType::NUMBER)
            throw ParserException{"Expected number after keep/drop token."};

        return std::make_unique<RetentionExpression>(op.type, std::move(roll), advance().parse_number());
    }


    std::set<std::uint16_t> Parser::arglist()
    {
        std::set<std::uint16_t> args;

        if (peek().type != TokenType::NUMBER)
            throw ParserException{"Expected number as arglist start."};
        args.insert(advance().parse_number());

        while (match(TokenType::COMMA))
        {
            if (peek().type != TokenType::NUMBER)
                throw ParserException{"Expected number after ','."};
            args.insert(advance().parse_number());
        }

        return args;
    }


    bool Parser::at_end() const
    {
        return _caret == _tokens.size();
    }


    Token Parser::peek() const
    {
        if (at_end())
            return Token{TokenType::END_OF_EXPRESSION, ""};
        return _tokens[_caret];
    }


    Token Parser::peek_previous() const
    {
        return _tokens[_caret - 1];
    }


    Token Parser::advance()
    {
        Token rval = peek();
        if (!at_end()) 
            ++_caret;
        return rval;
    }


    bool Parser::match(TokenType type)
    {
        if (peek().type == type)
        {
            advance();
            return true;
        }
        return false;
    }


    bool Parser::match(std::initializer_list<TokenType> types)
    {
        for (auto type : types)
        {
            if (peek().type == type)
            {
                advance();
                return true;
            }
        }
        
        return false;
    }
}
