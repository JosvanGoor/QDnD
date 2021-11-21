#include "parserstate.h"

bool ParserState::eof() const
{
    return caret >= line.size();
}


char ParserState::advance()
{
    if (eof())
        return '\0';
    ++caret;
    return line[caret - 1].toLatin1();
}


bool ParserState::accept(char c)
{
    if (eof())
        return false;
    
    if (line[caret] == c)
    {
        ++caret;
        return true;
    }

    return false;
}


char ParserState::peek()
{
    return eof() ? '\0' : line[caret].toLatin1();
}


char ParserState::peek_next()
{
    return (caret >= (line.size() - 1)) ? '\0' : line[caret + 1].toLatin1();
}


void ParserState::skip_whitespace()
{
    while (!eof())
    {
        if (line[caret] == ' ')
            ++caret;
        else
            return;
    }
}