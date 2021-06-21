#include "main.h"

bool IsLowPriority(const Node& n) {
    return (n.character == '+' || n.character == '-');
}

Node Combinate(const double& lhs, const double& rhs, const char& operation) {
    switch (operation) {
        case '+': {
            return { lhs + rhs, '0' };
        }
        case '-': {
            return { lhs - rhs, '0' };
        }
        case '*': {
            return { lhs * rhs, '0' };
        }
        case '/': {
            if(rhs == 0) {
                return { 0, 'e' };
            }
            return { lhs / rhs, '0' };
        }
        default: {
            throw std::invalid_argument("Unknown operation");
        }
    }
}


double CalculateExpr(int &i, const std::vector<Node>& parsedExpr) {
    std::stack<Node> stack;
    for(; i < parsedExpr.size(); i++) {
        if(parsedExpr[i].character == ')') {
            break;
        }
        if(IsOperation(parsedExpr[i].character)) {
            stack.push(parsedExpr[i]);
            continue;
        }
        Node temp = parsedExpr[i];
        if(parsedExpr[i].character == '(') {
            i++;
            temp = Node(CalculateExpr(i, parsedExpr), '0');
        }
        if(stack.empty()) {
            stack.push(temp);
        } else if (IsLowPriority(stack.top())) {
            if(stack.top().character == '-') {
                stack.pop();
                stack.push(Node(0, '+'));
                temp.value = -temp.value;
            }
            stack.push(temp);
        } else {
            Node operation = stack.top(); stack.pop();
            Node val = stack.top(); stack.pop();
            Node result = Combinate(val.value, temp.value, operation.character);
            if(result.character == 'e') {
                std::cout << "error: divide by zero ";
                return 0;
            }
            stack.push(result);
        }
    }
    while(stack.size() > 1) {
        Node value2 = stack.top(); stack.pop();
        Node operation = stack.top(); stack.pop();
        Node value1 = stack.top(); stack.pop();
        Node result = Combinate(value1.value, value2.value, operation.character);
        if(result.character == 'e') {
            std::cout << "error: divide by zero ";
            return 0;
        }
        stack.push(result);
    }
    return stack.top().value;
}

