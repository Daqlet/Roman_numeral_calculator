#include "main.h"

bool lowPriority(node n) {
    return n.symbol == '+' || n.symbol == '-';
}

node comb(double value1, double value2, char operation) {
    if(operation == '+') {
        return {value1 + value2, '0'};
    } else if(operation == '-') {
        return {value1 - value2, '0'};
    } else if(operation == '*') {
        return {value1 * value2, '0'};
    } else {
        return {value1 / value2, '0'};
    }
}

double calculate(int &i, vector<node>& parsedExpr) {
    stack<node> stack;
    for(; i < parsedExpr.size(); i++) {
        if(parsedExpr[i].symbol == ')') {
            break;
        }
        if(isOperation(parsedExpr[i].symbol)) {
            stack.push(parsedExpr[i]);
            continue;
        }
        node temp = parsedExpr[i];
        if(parsedExpr[i].symbol == '(') {
            i++;
            temp = node(calculate(i, parsedExpr), '0');
        }
        if(stack.empty()) {
            stack.push(temp);
        } else if (lowPriority(stack.top())) {
            if(stack.top().symbol == '-') {
                stack.pop();
                stack.push(node(0, '+'));
                temp.value = -temp.value;
            }
            stack.push(temp);
        } else {
            node operation = stack.top(); stack.pop();
            node val = stack.top(); stack.pop();
            stack.push(comb(val.value, temp.value, operation.symbol));
        }
    }
    while(stack.size() > 1) {
        node value2 = stack.top(); stack.pop();
        node operation = stack.top(); stack.pop();
        node value1 = stack.top(); stack.pop();
        stack.push(comb(value1.value, value2.value, operation.symbol));
    }
    return stack.top().value;
}

