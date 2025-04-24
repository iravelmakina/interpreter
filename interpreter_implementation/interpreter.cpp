#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <cmath>


enum TokenType {OPERAND, OPERATOR, FUNCTION, LEFT_BRACKET, RIGHT_BRACKET, COMMA};

struct Token {
    TokenType type;
    double value;
    char op;
    bool isUnary;
    std::string func;

    explicit Token(TokenType type, double value = 0, char op = 0, const std::string& func = "", bool isUnary = false)
            : type(type), value(value), op(op), func(func), isUnary(isUnary) {} // constructor to initialize token with default values
};


bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}


bool isFunction(const std::string& str) {
    return str == "pow" || str == "abs" || str == "max" || str == "min";
}


double applyUnaryOperation(char unaryOp, double value) {
    if (unaryOp == '-') return -value;
    return value; // unary + does nothing
}


std::vector<Token> tokenize(const std::string& expression) {
    if (expression.empty()) throw std::runtime_error("Empty input");
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
            if (!tokens.empty() && tokens.back().type == OPERATOR && tokens.back().op == '-') {
                value = applyUnaryOperation(tokens.back().op, value);
                tokens.pop_back(); // remove the unary operator token
            }
            tokens.emplace_back(OPERAND, value);
            i += length;
            continue;
        }

        if (isalpha(current)) {
            std::string func;
            while (i < expression.size() && isalpha(expression[i])) {
                func += expression[i++];
            }
            if (isFunction(func)) {
                tokens.emplace_back(FUNCTION, 0, 0, func);
            }
            else {
                throw std::runtime_error("Unknown function");
            }
            continue;
        }

        if (isOperator(current)) {
            bool isUnary = (current == '-' && (tokens.empty() || tokens.back().type == OPERATOR || tokens.back().type == LEFT_BRACKET));
            tokens.emplace_back(OPERATOR, 0, current, "", isUnary);
        } else if (current == '(') {
            tokens.emplace_back( LEFT_BRACKET, 0, current, "", false );
        } else if (current == ')') {
            tokens.emplace_back( RIGHT_BRACKET, 0, current, "", false );
        } else if (current == ',') {
            tokens.emplace_back( COMMA, 0, current, "", false );
        } else {
            throw std::runtime_error("Unknown character");
        }
        ++i;
    }

    return tokens;
}


std::unordered_map<char, int> precedence = {{'+', 10}, {'-', 10}, {'*', 20}, {'/', 20} };


std::queue<Token> infixToPostfix(const std::vector<Token>& tokens) {
    std::queue<Token> outputQueue;
    std::stack<Token> operatorStack;

    for (const Token& token : tokens) {
        switch(token.type) {
            case OPERAND:
                outputQueue.push(token);
                break;

            case OPERATOR:
                if (token.isUnary) {
                    operatorStack.push(token);
                } else {
                    while (!operatorStack.empty() && operatorStack.top().type != LEFT_BRACKET &&
                           precedence[operatorStack.top().op] >= precedence[token.op]) {
                        outputQueue.push(operatorStack.top());
                        operatorStack.pop();
                    }
                    operatorStack.push(token);
                }
                break;

            case FUNCTION:
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
                if (!operatorStack.empty() && operatorStack.top().type == FUNCTION) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                break;

            case COMMA:
                while (!operatorStack.empty() && operatorStack.top().type != LEFT_BRACKET) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
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


double applyOperator(char operatorChar, double a, double b) {
    switch(operatorChar) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        default: throw std::runtime_error("Unknown operator");
    }
}


double applyFunction(const std::string& func, const std::vector<double>& args) {
    if (func == "pow") return std::pow(args[0], args[1]);
    if (func == "abs") return std::abs(args[0]);
    if (func == "max") return std::max(args[0], args[1]);
    if (func == "min") return std::min(args[0], args[1]);
    throw std::runtime_error("Unknown function");
}


double evaluatePostfix(std::queue<Token>& postfix) {
    std::stack<double> evalStack;

    while (!postfix.empty()) {
        Token token = postfix.front();
        postfix.pop();

        if (token.type == OPERAND) {
            evalStack.push(token.value);
        } else if (token.type == OPERATOR) {
            if (token.isUnary) {
                if (evalStack.empty()) {
                    throw std::runtime_error("Incorrect syntax");
                }
                double a = evalStack.top(); evalStack.pop();
                evalStack.push(applyUnaryOperation(token.op, a));
            } else {
                if (evalStack.size() < 2) {
                    throw std::runtime_error("Incorrect syntax");
                }
                double b = evalStack.top();
                evalStack.pop();
                double a = evalStack.top();
                evalStack.pop();
                evalStack.push(applyOperator(token.op, a, b));
            }
        } else if (token.type == FUNCTION) {
            std::vector<double> args;
            int expectedArgs = (token.func == "abs") ? 1 : 2;

            for (int i = 0; i < expectedArgs; ++i) {
                if (evalStack.empty()) {
                    throw std::runtime_error("Incorrect syntax");
                }
                args.insert(args.begin(), evalStack.top());
                evalStack.pop();
            }
            evalStack.push(applyFunction(token.func, args));
        }
    }
    if (evalStack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return evalStack.top();
}


int main() {
    std::string expression;
    std::getline(std::cin, expression);

    try {
        std::vector<Token> tokens = tokenize(expression);
        std::queue<Token> postfix = infixToPostfix(tokens);
        double result = evaluatePostfix(postfix);
        std::cout << result << std::endl;
    } catch (const std::exception &ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
