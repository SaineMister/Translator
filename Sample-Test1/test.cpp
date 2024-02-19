#include "pch.h"
#include "fstream"
#include "../StaticLib/framework.h"
#include "../StaticLib/LexerHeader.h"


TEST(FromFile, program) {
	std::ifstream program("program1.txt");
	Lexer lex(program);

	EXPECT_EQ(lex.getNextLexem(), Lexem("keywords","int"));

}