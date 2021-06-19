#include "main.h"

void removeSpaces(string& s) {
    s.erase(remove_if(s.begin(), s.end(), [](char c){
        return c == ' ';
    }), s.end());
}

void solve(string& s) {
    vector<node> a;
    removeSpaces(s);
    if(!parse(s, a)) {
        cout << "error: wrong input format" << endl;
        return;
    }
    int i = 0;
    double ans = calculate(i, a);
    cout << doubleToRoman(ans) << endl;
}