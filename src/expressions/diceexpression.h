#ifndef EXPRESSIONS_DICEEXPRESSION_H
#define EXPRESSIONS_DICEEXPRESSION_H

#include <memory>
#include <QRandomGenerator>
#include <QString>

#include <iostream>

struct DiceResult
{
    QString text;
    int64_t result;
};

class DiceExpression
{
    public:
        virtual DiceResult evaluate() = 0;
};

using DiceExpressionPtr = std::unique_ptr<DiceExpression>;


class DiceRegularRoleExpression : public DiceExpression
{
    int d_die;
    int d_times;

    public:
        DiceRegularRoleExpression(int die, int times = 1);
        DiceResult evaluate() override;
};


class DiceAdvantageRollExpression : public DiceExpression
{
    int d_die;
    int d_times;

    public:
        DiceAdvantageRollExpression(int die, int times = 1);
        DiceResult evaluate() override;
};


class DiceDisadvantageRollExpression : public DiceExpression
{
    int d_die;
    int d_times;

    public:
        DiceDisadvantageRollExpression(int die, int times = 1);
        DiceResult evaluate() override;
};


class DiceNegateExpression : public DiceExpression
{
    DiceExpressionPtr d_expression;

    public:
        DiceNegateExpression(DiceExpressionPtr &&expression);
        DiceResult evaluate() override;
};


class DiceBinaryExpression : public DiceExpression
{
    DiceExpressionPtr d_lhs;
    DiceExpressionPtr d_rhs;
    bool d_plus;

    public:
        DiceBinaryExpression(DiceExpressionPtr &&lhs, DiceExpressionPtr &&rhs, bool plus);
        DiceResult evaluate() override;
};


class DiceValueExpression : public DiceExpression
{
    int64_t d_value;

    public:
        DiceValueExpression(int64_t value);
        DiceResult evaluate() override;  
};

#endif