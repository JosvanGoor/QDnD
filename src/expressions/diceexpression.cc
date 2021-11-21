#include "diceexpression.h"

////////////////////
//      Roll      //
////////////////////

DiceRegularRoleExpression::DiceRegularRoleExpression(int die, int times)
:   d_die(die),
    d_times(times)
{ }


DiceResult DiceRegularRoleExpression::evaluate()
{
    QString text = QString::number(d_times) + "d" + QString::number(d_die) + " (";
    int64_t result = 0;

    if (d_times < 1 || d_die < 2)
        return {text + ")", result};

    int64_t random = QRandomGenerator::global()->bounded(d_die) + 1;
    text += QString::number(random);
    result += random;

    for (int roll = 1; roll < d_times; ++roll)
    {
        random = QRandomGenerator::global()->bounded(d_die) + 1;
        text += ", " + QString::number(random);
        result += random;
    }

    return {text + ")", result};
}


////////////////////
//   Advantage    //
////////////////////

DiceAdvantageRollExpression::DiceAdvantageRollExpression(int die, int times)
:   d_die(die),
    d_times(times)
{ }


DiceResult DiceAdvantageRollExpression::evaluate()
{
    QString text = QString::number(d_times) + "ad" + QString::number(d_die) + " (";
    int64_t result = 0;

    if (d_times < 1 || d_die < 2)
        return {text + ")", result};

    int64_t random_first = QRandomGenerator::global()->bounded(d_die) + 1;
    int64_t random_second = QRandomGenerator::global()->bounded(d_die) + 1;
    if (random_first >= random_second)
        text += "{" + QString::number(random_first) + ", <s>" + QString::number(random_second) + "</s>}";
    else
        text += "{<s>" + QString::number(random_first) + "</s>, " + QString::number(random_second) + "}";
    result += random_first > random_second ? random_first : random_second;

    for (int roll = 1; roll < d_times; ++roll)
    {
        random_first = QRandomGenerator::global()->bounded(d_die) + 1;
        random_second = QRandomGenerator::global()->bounded(d_die) + 1;
        if (random_first >= random_second)
            text += ", {" + QString::number(random_first) + ", <s>" + QString::number(random_second) + "</s>}";
        else
            text += ", {<s>" + QString::number(random_first) + "</s>, " + QString::number(random_second) + "}";
        result += random_first > random_second ? random_first : random_second;
    }

    return {text + ")", result};
}


////////////////////
//  Disadvantage  //
////////////////////

DiceDisadvantageRollExpression::DiceDisadvantageRollExpression(int die, int times)
:   d_die(die),
    d_times(times)
{ }


DiceResult DiceDisadvantageRollExpression::evaluate()
{
    QString text = QString::number(d_times) + "dd" + QString::number(d_die) + " (";
    int64_t result = 0;

    if (d_times < 1 || d_die < 2)
        return {text + ")", result};

    int64_t random_first = QRandomGenerator::global()->bounded(d_die) + 1;
    int64_t random_second = QRandomGenerator::global()->bounded(d_die) + 1;
    if (random_first <= random_second)
        text += "{" + QString::number(random_first) + ", <s>" + QString::number(random_second) + "</s>}";
    else
        text += "{<s>" + QString::number(random_first) + "</s>, " + QString::number(random_second) + "}";
    result += random_first < random_second ? random_first : random_second;

    for (int roll = 1; roll < d_times; ++roll)
    {
        random_first = QRandomGenerator::global()->bounded(d_die) + 1;
        random_second = QRandomGenerator::global()->bounded(d_die) + 1;
        if (random_first <= random_second)
            text += ", {" + QString::number(random_first) + ", <s>" + QString::number(random_second) + "</s>}";
        else
            text += ", {<s>" + QString::number(random_first) + "</s>, " + QString::number(random_second) + "}";
        result += random_first < random_second ? random_first : random_second;
    }

    return {text + ")", result};
}


////////////////////
//     Negate     //
////////////////////

DiceNegateExpression::DiceNegateExpression(DiceExpressionPtr &&expr)
:   d_expression(move(expr))
{ }


DiceResult DiceNegateExpression::evaluate()
{
    DiceResult result = d_expression->evaluate();
    return {"-" + result.text, -result.result};
}


////////////////////
//     Binary     //
////////////////////

DiceBinaryExpression::DiceBinaryExpression(DiceExpressionPtr &&lhs, DiceExpressionPtr &&rhs, bool plus)
:   d_lhs(move(lhs)),
    d_rhs(move(rhs)),
    d_plus(plus)
{ }


DiceResult DiceBinaryExpression::evaluate()
{
    DiceResult result_lhs = d_lhs->evaluate();
    DiceResult result_rhs = d_rhs->evaluate();

    QString text = result_lhs.text + (d_plus ? " + " : " - ") + result_rhs.text;
    int64_t value = d_plus ? (result_lhs.result + result_rhs.result) : (result_lhs.result - result_rhs.result);

    return {text, value};
}


////////////////////
//     Value      //
////////////////////

DiceValueExpression::DiceValueExpression(int64_t value)
:   d_value(value)
{ }


DiceResult DiceValueExpression::evaluate()
{
    return {QString::number(d_value), d_value};
}