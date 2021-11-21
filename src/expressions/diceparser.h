#ifndef EXPRESSIONS_DICEPARSER_H
#define EXPRESSIONS_DICEPARSER_H

// Syntax:
//   command -> addition EOL ;
//
//   roll    -> NUMBER ( DIE_OP NUMBER )? ;             
//   unary   -> MINUS? (unary | roll);
//   addition-> addition ( (PLUS | MINUS) addition)* | unary ; 
//   
//   NUMBER  -> DIGIT+ ;
//   DIGIT   -> '0' ... '9' ;
//   DIE_OP  -> 'd' | 'ad' | 'dd' ;
//   MINUS   -> '-' ;
//   PLUS    -> '+' ;

#include <stdexcept>

#include "diceexpression.h"
#include "dicetokenizer.h"

class DiceParser
{
    int d_index;
    QVector<DiceToken> d_tokens;

    public:
        static DiceExpressionPtr parse(QString const &expression);

    private:
        DiceParser(QString const &line);

        bool eol() const;
        DiceToken peek() const;
        DiceToken advance();

        DiceExpressionPtr roll();
        DiceExpressionPtr unary();
        DiceExpressionPtr addition();
};

#endif