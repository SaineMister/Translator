// StaticLib.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"

//#include "fsm.h"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <set>

using namespace std;

void read(char& cache, istream& stream) {
    if (stream) {
        stream.get(cache);
    }
    if (!stream) {
        cache = 0;
    }
}

std::string char_rem;

std::string cache_pull;

std::string deco;

std::string value;


std::set<std::string> keywords = { "int","char","if","else","while","for","out","in","switch","case","return" };

pair<int, Lexem> tick(int state, istream& stream, char& cache) {
    switch (state) {
        //state switcher
    case 0:
        if (isdigit(cache)) {
            value = cache;
            read(cache, stream);
            return { 23,LEX_EMPTY };
        }
        else if (isalpha(cache)) {
            deco = cache;
            read(cache, stream);
            return { 21, LEX_EMPTY };
        }
        else {
            switch (cache) {
                //right-up
            case ' ':
                read(cache, stream);
                return { 0, LEX_EMPTY };

            case '\t':
                read(cache, stream);
                return { 0, LEX_EMPTY };

            case '\n':
                read(cache, stream);
                return { 0, LEX_EMPTY };

            case '<':
                read(cache, stream);
                return { 2, LEX_EMPTY };

            case '!':
                read(cache, stream);
                return { 4, LEX_EMPTY };

            case '=':
                read(cache, stream);
                return { 6, LEX_EMPTY };

            case '+':
                read(cache, stream);
                return { 8, LEX_EMPTY };
                //right-down
            case '(':
                read(cache, stream);
                return { 1, {"lpar",""} };

            case ')':
                read(cache, stream);
                return { 1, {"rpar",""} };

            case '{':
                read(cache, stream);
                return { 1, {"lbrace",""} };

            case '}':
                read(cache, stream);
                return { 1, {"rbrace",""} };

            case ';':
                read(cache, stream);
                return { 1, {"semicolon",""} };

            case ',':
                read(cache, stream);
                return { 1, {"coma",""} };

            case '.':
                read(cache, stream);
                return { 1, {"colon",""} };

            case '>':
                read(cache, stream);
                return { 1, {"opgt",""} };

            case '*':
                read(cache, stream);
                return { 1, {"opmul",""} };

            case '|':
                read(cache, stream);
                return { 10, LEX_EMPTY };

            case '&':
                read(cache, stream);
                return { 12, LEX_EMPTY };

            case '-':
                read(cache, stream);
                return { 22, LEX_EMPTY };

            case '"':// "
                read(cache, stream);
                return { 18, LEX_EMPTY };

            case 39: // '
                read(cache, stream);
                return { 14, LEX_EMPTY };

            default:
                return { -1, LEX_ERROR };
            }
    case 1:
        switch (cache) {
        case '\n':
            return { 0, LEX_EMPTY };
        default:
            return { 0, LEX_EMPTY };
        }

    case 2:
        if (cache == '=') {
            read(cache, stream);
            return { 3, {"ople",""} };
        }
        else {
            return { 0, {"oplt", ""} };
        }

    case 3:
        return { 0, LEX_EMPTY };

    case 4:
        if (cache == '=') {
            read(cache, stream);
            return { 5, {"opne",""} };
        }
        else {
            return { 0, {"opnot",""} };
        }
    case 5:
        return { 0, LEX_EMPTY };

    case 6:

        if (cache == '=') {
            read(cache, stream);
            return { 7, {"opeq",""} };

        }
        else {
            return { 0, {"opassign",""} };
        }

    case 7:
        return { 0, LEX_EMPTY };

    case 8:
        if (cache == '+') {
            read(cache, stream);
            return { 9, LEX_EMPTY };
        }
        else {
            return { 0, {"opplus", ""} };
        }

    case 9:
        return { 0, {"opinc",""} };

    case 10:
        if (cache == '|') {
            read(cache, stream);
            return { 11, LEX_EMPTY };
        }
        else {
            return { -1, LEX_ERROR };
        }

    case 11:
        return { 0, {"opor",""} };

    case 12:
        if (cache == '&') {
            read(cache, stream);
            return { 13, LEX_EMPTY };
        }
        else {
            return { -1, LEX_ERROR };
        }

    case 13:
        return  { 0, {"opand",""} };

    case 14:
        if (cache == 39) {
            //read(cache, stream);
            return { 15, LEX_EMPTY };
        }
        else if (isprint(cache) && cache != 39) {
            char_rem = cache;
            read(cache, stream);
            return { 16, LEX_EMPTY };
        }

    case 15:
        return { -1, LEX_ERROR };

    case 16:
        if (cache == 39) {
            read(cache, stream);
            return { 17, {"char",char_rem} };
        }
        else {
            return { -1, LEX_ERROR };
        }

    case 17:
        return { 0, LEX_EMPTY };

    case 18:
        if (isprint(cache) && cache != '\n') {
            while (cache != '"' && cache != '\n') {
                cache_pull += cache;
                read(cache, stream);
            }
            if (cache != '"') {
                return { 19, LEX_EMPTY };
            }
            return { 20, LEX_EMPTY };
        }
        else {
            return { 19, LEX_EMPTY };
        }

    case 19:
        return { -1, LEX_ERROR };

    case 20:
        read(cache, stream);
        return { 0, {"str",cache_pull} };

    case 21:
        while (isalpha(cache) || isdigit(cache)) {
            deco += cache;
            read(cache, stream);
        }
        if (keywords.find(deco) != keywords.end()) { //типо прошли всю коллекцию, а эл-а нет

            return { 0, {"kw" + deco, ""}};
        }
        else {

            return { 0, {"id",deco} };
        }

    case 22:
        if (isdigit(cache)) {
            value = '-';
            value += cache;
            read(cache, stream);
            return { 23, LEX_EMPTY };
        }
        else {
            return { 0, {"opminus",""} };
        }

    case 23:
        while (isdigit(cache)) {
            value += cache;
            read(cache, stream);
        }
        return { 0, {"num",value} };

    default:
        return { -1, LEX_EMPTY };


        }
    }
}
