#include "expression.h"

#include "../common/exceptions.h"

namespace jb::dice
{

    BinaryExpression::BinaryExpression(TokenType op, ExpressionPtr lhs, ExpressionPtr rhs)
    :   _op(op),
        _lhs(std::move(lhs)),
        _rhs(std::move(rhs))
    { }


    Roll BinaryExpression::evaluate() const
    {
        Roll roll_left = _lhs->evaluate();
        Roll roll_right = _rhs->evaluate();

        switch (_op)
        {
            case TokenType::MINUS:
                roll_right.negate();
                [[fallthrough]];
            case TokenType::PLUS:
                roll_left.merge(roll_right);
                return roll_left;
            default:
                throw LogicException{"dice::BinaryExpression has invalid op."};
        }
    }


    FilterExpression::FilterExpression(TokenType type, ExpressionPtr expr, const std::set<std::uint16_t>& filter)
    :   _type(type),
        _expr(std::move(expr)),
        _filter(filter)
    { }


    Roll FilterExpression::evaluate() const
    {
        Roll result = _expr->evaluate();

        switch (_type)
        {
            case TokenType::EXPLODE:
                result.explode(_filter);
            break;

            case TokenType::REROLL:
                result.reroll(_filter);
            break;

            case TokenType::REROLL_ONCE:
                result.reroll_once(_filter);
            break;

            default:
                throw LogicException{"dice::FilterExpression has invalid type."};
        }

        return result;
    }


    MessageExpression::MessageExpression(ExpressionPtr expr, const std::string& message)
    :   _expr(std::move(expr)),
        _message(message)
    { }


    Roll MessageExpression::evaluate() const
    {
        Roll roll = _expr->evaluate();
        roll.add_message(_message);
        return roll;
    }


    NegateExpression::NegateExpression(ExpressionPtr expr)
    :   _expr(std::move(expr))
    { }


    Roll NegateExpression::evaluate() const
    {
        Roll result = _expr->evaluate();
        result.negate();
        return result;
    }


    RetentionExpression::RetentionExpression(TokenType type, ExpressionPtr expr, std::uint16_t amount)
    :   _type(type),
        _expr(std::move(expr)),
        _amount(amount)
    { }


    Roll RetentionExpression::evaluate() const
    {
        Roll result = _expr->evaluate();
        RollResult& operand = result.most_recent();

        switch (_type)
        {
            case TokenType::KEEP_HIGHEST:
                operand.keep_higest(_amount);
            break;

            case TokenType::KEEP_LOWEST:
                operand.drop_highest(operand.number() - _amount);
            break;

            case TokenType::DROP_HIGHEST:
                operand.drop_highest(_amount);
            break;

            case TokenType::DROP_LOWEST:
                operand.keep_higest(operand.number() - _amount);
            break;

            default:
                throw LogicException{"dice::RetentionExpression has invalid type."};
        }

        return result;
    }


    RollExpression::RollExpression(TokenType type, std::uint16_t number, std::uint16_t sides)
    :   _type(type),
        _number(number),
        _sides(sides)
    { }


    Roll RollExpression::evaluate() const
    {
        switch (_type)
        {
            case TokenType::DIE:
                return Roll{RollResult{_number, _sides}};
            case TokenType::DIE_ADVANTAGE:
                return advantage();
            case TokenType::DIE_DISADVANTAGE:
                return disadvantage();

            default:
                throw LogicException{"dice::RollException has invalid type"};
        }
    }


    Roll RollExpression::advantage() const
    {
        RollResult first{_number, _sides};
        RollResult second{_number, _sides};

        first.score() >= second.score() ? second.reject() : first.reject();
        first.merge(second);
        first.set_display(fmt::format("{}ad{}", _number, _sides));

        return Roll{first};
    }


    Roll RollExpression::disadvantage() const
    {
        RollResult first{_number, _sides};
        RollResult second{_number, _sides};

        first.score() <= second.score() ? second.reject() : first.reject();
        first.merge(second);
        first.set_display(fmt::format("{}dd{}", _number, _sides));
        
        return Roll{first};
    }


    ValueExpression::ValueExpression(std::uint16_t value)
    :   _value(value)
    { }


    Roll ValueExpression::evaluate() const
    {
        Roll roll;
        RollResult result;
        result.feed_value(RollValue{_value, RollValue::PLAIN_VALUE});
        roll.add_result(result);
        return roll;
    }


}