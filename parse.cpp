#include "main.h"

unordered_map<char, int> mapRoman{
    {'M', 1000},
    {'D', 500},
    {'C', 100},
    {'L', 50},
    {'X', 10},
    {'V', 5},
    {'I', 1},
    {'Z', 0},
};
int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
string str_romans[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

bool isOperation(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

string doubleToRoman(double n) {
    if(1 > abs(n)) return "Z";
    string result = "";
    if(n < 0) {
        n = -n;
        result = "-";
    }
    for (int i = 0; i < 13; ++i)
    {
        while(n - values[i] >= 0)
        {
            result += str_romans[i];
            n -= values[i];
        }
    }
    return result;
}

double romanToDouble(string s) {
    double res = 0;
    for(int i = 0; i < s.length(); ++i) {
        if(i+1 < s.length() && mapRoman[s[i]] < mapRoman[s[i+1]]) {
            res += mapRoman[s[i+1]] - mapRoman[s[i]];
            i++;
        } else {
            res += mapRoman[s[i]];
        }
    }
    return res;
}

bool isCorrectOperation(vector<node>& a) {
    bool isOp = 0;
    int scope = 0;
    for(int i = 0; i < a.size(); ++i) {
        if(a[i].symbol == '(') {
            scope++; continue;
        } else if(a[i].symbol == ')') {
            if(--scope < 0) {
                return 0;
            }
            continue;
        }
        if(isOp ^ isOperation(a[i].symbol)) {
            return 0;
        }
        isOp = !isOp;
    }
    return scope == 0;
}

bool isCorrectRomanNumber(string s) {
    if(s.length() == 1 && s[0] == 'Z') return 1;
    regex roman_expr ("^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$");
    bool ok = regex_match(s, roman_expr);
    return ok && !s.empty();
}

bool parse(string& s, vector<node>& a) {
    bool isOp = 0;
    for(int i = 0; i < s.length(); ) {
        if(s[i] == ')' || s[i] == '(') {
            a.push_back(node(0, s[i++]));
            continue;
        }
        if(isOp) {
            a.push_back(node(0, s[i++]));
            isOp = 0;
            continue;
        }
        int sign = 1;
        if(s[i] == '-') {
            i++;
            sign = -1;
        }
        int start = i;
        while(mapRoman.count(s[i])) {
            i++;
        } 
        string romanNumber = s.substr(start, i-start);
        if(isCorrectRomanNumber(romanNumber)) {
            double val = sign * romanToDouble(romanNumber);
            a.push_back(node(val, '0'));
        } else return 0;
        isOp = 1;
    }
    return isCorrectOperation(a);
}