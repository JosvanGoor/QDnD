#ifndef EXPRESSIONS_PARSERSTATE_H
#define EXPRESSIONS_PARSERSTATE_H

#include <QString>

struct ParserState
{
    int caret = 0;
    QString const &line;

    bool eof() const;
    char advance();
    bool accept(char c);
    char peek();
    char peek_next();
    void skip_whitespace();
};

#endif