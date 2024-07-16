#include <iostream>
#include <string>

enum TokenType {OPERAND, OPERATOR, LEFT_BRACKET, RIGHT_BRACKET};

struct Token {
    TokenType type;
    double value;
    char op;
};