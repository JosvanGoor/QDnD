#ifndef JB_DICE_PARSER_H
#define JB_DICE_PARSER_H

#include "expression.h"
#include "tokenizer.h"

/*
    // ? = 0 or 1
    // * = 0 or more
    // + = 1 or more

    expression      -> addition ( ":" message ) EOL ;

    addition        -> unary ( [ "+" | "-" ] unary )? ;
    unary           -> "-"? roll ;
    roll            -> value | ( number? [ "d" | "ad" | "dd" ] number rollmod* ) ;
    rollmod         -> filter | retention ;
    filter          -> ["e" | "rr" | "ro" ] arglist ;
    retention       -> ["kh" | "kl" | "dh" | "dl" ] number;
    
    arglist         -> number ( "," number )* ;
    value           -> number ;
    number          -> '0' ... '9' ;
    message         -> any_ascii*;
*/

namespace jb::dice
{

    class Parser
    {
        std::size_t _caret;
        std::vector<Token> _tokens;

        public:
            Parser(const std::string& expression);
            ExpressionPtr parse();

        private:
            ExpressionPtr expression();

            ExpressionPtr addition();
            ExpressionPtr unary();
            ExpressionPtr roll();
            ExpressionPtr rollmod(ExpressionPtr&& roll);         
            std::set<std::uint16_t> arglist();

            bool has_rollmod();

            bool at_end() const;
            Token peek() const;
            Token peek_previous() const;
            Token advance();
            bool match(TokenType type);
            bool match(std::initializer_list<TokenType> types);
    };

}

#endif