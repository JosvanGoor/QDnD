#include "diceparser.h"

////////////////////
//  Constructor   //
////////////////////

DiceParser::DiceParser(QString const &expression)
:   d_index(0),
    d_tokens(dice_tokenize(expression))
{ }


////////////////////
//     Static     //
////////////////////

DiceExpressionPtr DiceParser::parse(QString const &expression)
{
    try 
    {
        DiceParser parser{expression};
        return parser.addition();
    }
    catch (std::exception &ex)
    {
        // TODO: show result
        return nullptr;
    }
}


////////////////////
//    Utility     //
////////////////////

bool DiceParser::eol() const
{
    return d_index >= d_tokens.size();
}


DiceToken DiceParser::peek() const
{
    if (eol())
        return {DiceTokenType::EOL, "\0"};
    return d_tokens[d_index];
}


DiceToken DiceParser::advance()
{
    if (eol())
        return {DiceTokenType::EOL, "\0"};
    return d_tokens[d_index++];
}


////////////////////
//    Parsing     //
////////////////////
#include <iostream> // TODO remove

DiceExpressionPtr DiceParser::roll()
{
    int times = 0;
    bool number = false;

    if (peek().type == DiceTokenType::NUMBER)
    {
        times = advance().literal.toInt();
        number = true;
    }

    if (peek().type != DiceTokenType::ADVANTAGE_ROLL
        && peek().type != DiceTokenType::DISADVANTAGE_ROLL
        && peek().type != DiceTokenType::REGULAR_ROLL
        && number)
    {
        return std::make_unique<DiceValueExpression>(times);
    }
    
    DiceToken oper = advance(); // store this for later

    if (peek().type != DiceTokenType::NUMBER)
    {
        throw std::runtime_error("Expected a number");
    }

    switch(oper.type)
    {
        case DiceTokenType::ADVANTAGE_ROLL:
            return std::make_unique<DiceAdvantageRollExpression>(advance().literal.toInt(), times);
        case DiceTokenType::DISADVANTAGE_ROLL:
            return std::make_unique<DiceDisadvantageRollExpression>(advance().literal.toInt(), times);
        case DiceTokenType::REGULAR_ROLL:
            return std::make_unique<DiceRegularRoleExpression>(advance().literal.toInt(), times);
        default:
            std::cout << "got " << int(oper.type) << " - " << oper.literal.toStdString() << ".\n" << std::flush;
            throw std::runtime_error("Expected DIE_OP");
    }
}


DiceExpressionPtr DiceParser::unary()
{
    if (peek().type == DiceTokenType::MINUS)
    {
        advance();
        return std::make_unique<DiceNegateExpression>(unary());
    }
    return roll();
}


DiceExpressionPtr DiceParser::addition()
{
    DiceExpressionPtr lhs = unary();

    while (peek().type == DiceTokenType::MINUS || peek().type == DiceTokenType::PLUS)
    {
        DiceToken op = advance();
        DiceExpressionPtr rhs = unary();

        lhs = std::make_unique<DiceBinaryExpression>(move(lhs), move(rhs), op.type == DiceTokenType::PLUS);
    }

    return lhs;
}