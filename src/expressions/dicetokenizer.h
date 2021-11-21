#ifndef EXPRESSIONS_TOKENIZER_H
#define EXPRESSIONS_TOKENIZER_H

#include <QString>
#include <QVector>
#include <stdexcept>

#include "parserstate.h"

enum class DiceTokenType
{
    NUMBER,
    REGULAR_ROLL,
    ADVANTAGE_ROLL,
    DISADVANTAGE_ROLL,
    MINUS,
    PLUS,
    EOL
};


struct DiceToken
{
    DiceTokenType type;
    QString literal;
};

QVector<DiceToken> dice_tokenize(QString const &expression);

#endif