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

double applyOperation(char operatorChar, double a, double b) {
    switch(operatorChar) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        default: throw std::runtime_error("Unknown operator");
    }
}

double evaluatePostfix(std::queue<Token>& postfix) {
    std::stack<double> evalStack;

    while (!postfix.empty()) {
        Token token = postfix.front();
        postfix.pop();

        if (token.type == OPERAND) {
            evalStack.push(token.value);
        } else if (token.type == OPERATOR) {
            if (evalStack.size() < 2) {
                throw std::runtime_error("Incorrect syntax");
            }
            double b = evalStack.top(); evalStack.pop();
            double a = evalStack.top(); evalStack.pop();
            evalStack.push(applyOperation(token.op, a, b));
        }
    }
    if (evalStack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return evalStack.top();
}

int main() {
    std::string expression;
    do {
        std::cout << "Enter an arithmetic expression (or 'e' to exit): ";
        std::getline(std::cin, expression);

        if (expression == "e") {
            std::cout << "Exiting...";
            break;
        }

        try {
            std::vector<Token> tokens = tokenize(expression);
            std::queue<Token> postfix = infixToPostfix(tokens);
            double result = evaluatePostfix(postfix);
            std::cout << "Result: " << result << std::endl;
        } catch (const std::exception &ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
        }
    } while (true);

    return 0;
}
