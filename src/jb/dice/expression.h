#ifndef JB_DICE_EXPRESSION_H
#define JB_DICE_EXPRESSION_H

#include <memory>
#include <set>

#include "roll.h"
#include "rollresult.h"
#include "tokenizer.h"

namespace jb::dice
{

    class Expression
    {
        public:
            virtual ~Expression() { };
            virtual Roll evaluate() const = 0;
    };
    using ExpressionPtr = std::unique_ptr<Expression>;


    class BinaryExpression : public Expression
    {
        TokenType _op;
        ExpressionPtr _lhs;
        ExpressionPtr _rhs;

        public:
            BinaryExpression(TokenType op, ExpressionPtr lhs, ExpressionPtr rhs);
            Roll evaluate() const override;
    };


    class FilterExpression : public Expression
    {
        TokenType _type;
        ExpressionPtr _expr;
        std::set<std::uint16_t> _filter;

        public:
            FilterExpression(TokenType type, ExpressionPtr expr, const std::set<std::uint16_t>& filter);
            Roll evaluate() const override;
    };


    class MessageExpression : public Expression
    {
        ExpressionPtr _expr;
        std::string _message;

        public:
            MessageExpression(ExpressionPtr expr, const std::string& message);
            Roll evaluate() const override;
    };


    class NegateExpression : public Expression
    {
        ExpressionPtr _expr;

        public:
            NegateExpression(ExpressionPtr expr);
            Roll evaluate() const override;
    };


    class RetentionExpression : public Expression
    {
        TokenType _type;
        ExpressionPtr _expr;
        std::uint16_t _amount;

        public:
            RetentionExpression(TokenType type, ExpressionPtr _expr, std::uint16_t amount);
            Roll evaluate() const override;
    };


    class RollExpression : public Expression
    {
        TokenType _type;
        std::uint16_t _number;
        std::uint16_t _sides;

        public:
            RollExpression(TokenType type, std::uint16_t number, std::uint16_t sides);
            Roll evaluate() const override;

        private:
            Roll advantage() const;
            Roll disadvantage() const;
    };


    class ValueExpression : public Expression
    {
        std::uint16_t _value;

        public:
            ValueExpression(std::uint16_t value);
            Roll evaluate() const override;
    };

}

#endif