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
            stack.push(Combinate(val.value, temp.value, operation.character));
        }
    }
    while(stack.size() > 1) {
        Node value2 = stack.top(); stack.pop();
        Node operation = stack.top(); stack.pop();
        Node value1 = stack.top(); stack.pop();
        stack.push(Combinate(value1.value, value2.value, operation.character));
    }
    return stack.top().value;
}

