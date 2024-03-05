#include "pch.h"
#include <iostream>
#include <stack>
#include <queue>
#include "../StaticLib/LexerHeader.h"
#include <sstream>



 /*Функция для проверки является ли символ операцией*/
bool isOperator(std::string c) {
    return c == "opplus" || c == "opminus" || c == "opmul";
}

// Функция для определения приоритета операции
int getPriority(std::string op) {
    if (op == "opplus" || op == "opminus") {
        return 1;
    }
    else if (op == "opmul") {
        return 2;
    }
    else {
        return 0;  // для скобок
    }
}

std::queue<std::string> sorter(std::string prog) {
 
    std::stack<std::string> operators;
    std::queue<std::string> output;

    std::stringstream stream{ prog };
    Lexer lexer(stream);

    while (true) {
        auto c = lexer.getNextLexem().first;
        if (c == "num") {
            output.push(c);
        }
        else if (c == "lpar") {
            operators.push(c);
        }
        else if (c == "rpar") {
            while (!operators.empty() && operators.top() != "lpar") {
                output.push(operators.top());
                operators.pop();
            }
            if (operators.empty()) {
                std::cout << "Ошибка: не найдена открывающая скобка!" << std::endl;
                return output;
            }
            operators.pop();  // Убираем открывающую скобку со стека
        }
        else if (isOperator(c)) {
            while (!operators.empty() && (getPriority(operators.top()) > getPriority(c) || (getPriority(operators.top()) == getPriority(c)))) {
                output.push(operators.top());
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        if (operators.top() == "lpar") {
            std::cout << "Ошибка: найдена открывающая скобка!" << std::endl;
            return output;
        }
        output.push(operators.top());
        operators.pop();
    }

    // Выводим результат работы алгоритма
    std::cout << "Результат работы алгоритма: ";
    while (!output.empty()) {
        std::cout << output.front() << " ";
        output.pop();
    }
    std::cout << std::endl;

    return output;
}
