#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

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

std::unordered_map<char, int> Precedence = { {'+', 10}, {'-', 10}, {'*', 20}, {'/', 20} };

std::queue<Token> infixToPostfix(const std::vector<Token>& tokens) {
    std::queue<Token> outputQueue;
    std::stack<Token> operatorStack;

    for (const Token& token : tokens) {
        switch(token.type) {
            case OPERAND:
                outputQueue.push(token);
                break;

            case OPERATOR:
                while (!operatorStack.empty() && operatorStack.top().type != LEFT_BRACKET &&
                       Precedence[operatorStack.top().op] >= Precedence[token.op]) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token);
                break;

            case LEFT_BRACKET:
                operatorStack.push(token);
                break;

            case RIGHT_BRACKET:
                while (!operatorStack.empty() && operatorStack.top().type != LEFT_BRACKET) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                if (operatorStack.empty() || operatorStack.top().type != LEFT_BRACKET) {
                    throw std::runtime_error("Mismatched parentheses");
                }
                operatorStack.pop();
                break;
        }
    }
    while (!operatorStack.empty()) {
        if (operatorStack.top().type == LEFT_BRACKET) {
            throw std::runtime_error("Mismatched parentheses");
        }
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }
    return outputQueue;
}