#include "pch.h"
#include "fstream"
#include "sstream"
#include "../StaticLib/framework.h"
#include "../StaticLib/LexerHeader.h"


TEST(Lexer, keywords) {
	std::istringstream program("int else switch");
	Lexer lex(program);
	EXPECT_EQ(lex.getNextLexem(), Lexem("int", ""));
	EXPECT_EQ(lex.getNextLexem(), Lexem("else", ""));
	EXPECT_EQ(lex.getNextLexem(), Lexem("switch", ""));
}

TEST(Lexer, names) {
	std::istringstream program2("hello");
	Lexer lex(program2);
	EXPECT_EQ(lex.getNextLexem(), Lexem("id(hello)", ""));
}

TEST(Lexer, arithm) {
	std::istringstream program3("33--99");
	Lexer lex(program3);
	EXPECT_EQ(lex.getNextLexem(), Lexem("num(33)", ""));
	EXPECT_EQ(lex.getNextLexem(), Lexem("opminus", ""));
	EXPECT_EQ(lex.getNextLexem(), Lexem("num(-99)", ""));
}

TEST(Lexer, quotes) {
	std::istringstream program4("'p' 'sdsd'");
	Lexer lex(program4);
	EXPECT_EQ(lex.getNextLexem(), Lexem("char(p)", ""));
	EXPECT_EQ(lex.getNextLexem(), LEX_ERROR);
}