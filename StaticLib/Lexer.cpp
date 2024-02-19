#include "pch.h"

#include "../StaticLib/LexerHeader.h"
#include "../StaticLib/framework.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;


Lexer::Lexer(istream& stream) : state{ 0 }, stream{ stream }
{
    read(cache, stream);
}

Lexer::~Lexer()
{
    //dtor
}

Lexem Lexer::getNextLexem() {
    Lexem lex = LEX_EMPTY;
    while (lex == LEX_EMPTY and state >= 0) {
        auto res = tick(state, stream, cache);
        state = res.first;
        lex = res.second;
    }
    return lex;
}


