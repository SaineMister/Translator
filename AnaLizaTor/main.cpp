#include <iostream>
#include <vector>
#include "../StaticLib/LexerHeader.h"
#include "../StaticLib/framework.h"

using namespace std;

//int dice();

int main()
{
    Lexer lex(cin);
    Lexem currentLex;

    while ((currentLex = lex.getNextLexem()), currentLex != LEX_EOF) {
        if (currentLex.second != "") {
            cout << currentLex.first << '(' << currentLex.second <<  ')' << endl;
        }
        else if (currentLex == LEX_ERROR) {
            cout << currentLex.first << endl;
            break;
        }
        else {
            cout << currentLex.first << endl;
        }
    }

    return 0;
}
