#include "pch.h"
#include "framework.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

ShuntingYard::ShuntingYard(istream& stream)
    : lexer{ stream }
{
}

ShuntingYard::~ShuntingYard()
{
    // dtor
}

Lexem ShuntingYard::getNextLexem()
{
    // TODO: implement shunting yarg algorithm
    return lexer.getNextLexem();
}