#include "main.h"

void removeSpaces(string& task) {
    task.erase(remove_if(task.begin(), task.end(), [](char c){
        return c == ' ';
    }), task.end());
}

void solve(string& task) {
    vector<node> parsedExpr;
    removeSpaces(task);
    if(!parse(task, parsedExpr)) {
        cout << "error: wrong input format" << endl;
        return;
    }
    int i = 0;
    double answer = calculate(i, parsedExpr);
    cout << doubleToRoman(answer) << endl;
}