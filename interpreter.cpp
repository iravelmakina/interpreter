#include <iostream>
#include <string>
#include <vector>


enum TokenType {OPERAND, OPERATOR, LEFT_BRACKET, RIGHT_BRACKET};

struct Token {
    TokenType type;
    double value;
    char op;
};

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::vector<Token> tokenize(const std::string& expression) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < expression.size()) {
        char current = expression[i];

        if (isspace(current)) {
            ++i;
            continue;
        }

        if (isdigit(current) || current == '.') {
            size_t length;
            double value = std::stod(&expression[i], &length);
            tokens.push_back({OPERAND, value, 0});
            i += length;
            continue;
        }

        if (isOperator(current)) {
            tokens.push_back({OPERATOR, 0, current});
        } else if (current == '(') {
            tokens.push_back({LEFT_BRACKET, 0, current});
        } else if (current == ')') {
            tokens.push_back({RIGHT_BRACKET, 0, current});
        } else {
            throw std::runtime_error("Unknown character");
        }
        ++i;
    }

    if (tokens.empty()) {
        throw std::runtime_error("Empty input");
    }

    return tokens;
}
