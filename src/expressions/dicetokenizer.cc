#include "dicetokenizer.h"

////////////////////
//    Utility     //
////////////////////

static DiceToken number(ParserState &line)
{
    DiceToken token;
    token.type = DiceTokenType::NUMBER;

    while (!line.eof())
    {
        if (isdigit(line.peek()))
            token.literal += line.advance();
        else break;
    }

    return token;
}


////////////////////
//   Tokenizer    //
////////////////////

QVector<DiceToken> dice_tokenize(QString const &expression)
{
    QVector<DiceToken> tokens;
    ParserState line{0, expression.simplified()};

    while (!line.eof())
    {
        line.skip_whitespace();

        switch (line.peek())
        {
            case '0': [[fallthrough]];
            case '1': [[fallthrough]];
            case '2': [[fallthrough]];
            case '3': [[fallthrough]];
            case '4': [[fallthrough]];
            case '5': [[fallthrough]];
            case '6': [[fallthrough]];
            case '7': [[fallthrough]];
            case '8': [[fallthrough]];
            case '9':
                tokens.push_back(number(line));
            break;

            case 'a': [[fallthrough]];
            case 'A':
                line.advance();
                if (line.accept('d') || line.accept('D'))
                    tokens.push_back({DiceTokenType::ADVANTAGE_ROLL, "ad"});
                else
                    throw std::runtime_error("'a' is not recognized");
            break;

            case 'd': [[fallthrough]];
            case 'D':
                line.advance();
                if (line.accept('d') || line.accept('D'))
                    tokens.push_back({DiceTokenType::DISADVANTAGE_ROLL, "dd"});
                else
                    tokens.push_back({DiceTokenType::REGULAR_ROLL, "d"});
            break;

            case '+':
                line.advance();
                tokens.push_back({DiceTokenType::PLUS, "+"});
            break;

            case '-':
                line.advance();
                tokens.push_back({DiceTokenType::MINUS, "-"});
            break;

            default:
                throw std::runtime_error("Illegal token encountered");
        }
    }

    return tokens;
}