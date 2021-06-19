#include "main.h"

bool lowPriority(node n) {
    return n.symbol == '+' || n.symbol == '-';
}

node comb(double val1, double val2, char op) {
    if(op == '+') {
        return {val1 + val2, '0'};
    } else if(op == '-') {
        return {val1 - val2, '0'};
    } else if(op == '*') {
        return {val1 * val2, '0'};
    } else {
        return {val1 / val2, '0'};
    }
}

double calculate(int &i, vector<node>& a) {
    stack<node> stack;
    for(; i < a.size(); i++) {
        if(a[i].symbol == ')') {
            break;
        }
        if(isOperation(a[i].symbol)) {
            stack.push(a[i]);
            continue;
        }
        node temp = a[i];
        if(a[i].symbol == '(') {
            i++;
            temp = node(calculate(i, a), '0');
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
            node oper = stack.top(); stack.pop();
            node val = stack.top(); stack.pop();
            stack.push(comb(val.value, temp.value, oper.symbol));
        }
    }
    while(stack.size() > 1) {
        node val2 = stack.top(); stack.pop();
        node oper = stack.top(); stack.pop();
        node val1 = stack.top(); stack.pop();
        stack.push(comb(val1.value, val2.value, oper.symbol));
    }
    return stack.top().value;
}

