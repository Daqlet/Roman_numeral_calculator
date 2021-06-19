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
string romans[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

bool isOperation(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

string doubleToRoman(double value) {
    if(1 > abs(value)) return "Z";
    string result = "";
    if(value < 0) {
        value = -value;
        result = "-";
    }
    for (int i = 0; i < 13; ++i)
    {
        while(value - values[i] >= 0)
        {
            result += romans[i];
            value -= values[i];
        }
    }
    return result;
}

double romanToDouble(string roman) {
    double res = 0;
    for(int i = 0; i < roman.length(); ++i) {
        if(i+1 < roman.length() && mapRoman[roman[i]] < mapRoman[roman[i+1]]) {
            res += mapRoman[roman[i+1]] - mapRoman[roman[i]];
            i++;
        } else {
            res += mapRoman[roman[i]];
        }
    }
    return res;
}

bool isCorrectOperation(vector<node>& parsedExpr) {
    bool needOper = 0;
    int scope = 0;
    for(int i = 0; i < parsedExpr.size(); ++i) {
        if(parsedExpr[i].symbol == '(') {
            scope++; continue;
        } else if(parsedExpr[i].symbol == ')') {
            if(--scope < 0) {
                return 0;
            }
            continue;
        }
        if(needOper ^ isOperation(parsedExpr[i].symbol)) {
            return 0;
        }
        needOper = !needOper;
    }
    return scope == 0;
}

bool isCorrectRomanNumber(string roman) {
    if(roman.length() == 1 && roman[0] == 'Z') return 1;
    regex romanExpr ("^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$");
    bool ok = regex_match(roman, romanExpr);
    return ok && !roman.empty();
}

bool parse(string& roman, vector<node>& parsedExpr) {
    bool needOper = 0;
    for(int i = 0; i < roman.length(); ) {
        if(roman[i] == ')' || roman[i] == '(') {
            parsedExpr.push_back(node(0, roman[i++]));
            continue;
        }
        if(needOper) {
            parsedExpr.push_back(node(0, roman[i++]));
            needOper = 0;
            continue;
        }
        int sign = 1;
        if(roman[i] == '-') {
            i++;
            sign = -1;
        }
        int start = i;
        while(mapRoman.count(roman[i])) {
            i++;
        } 
        string romanNumber = roman.substr(start, i-start);
        if(isCorrectRomanNumber(romanNumber)) {
            double val = sign * romanToDouble(romanNumber);
            parsedExpr.push_back(node(val, '0'));
        } else return 0;
        needOper = 1;
    }
    return isCorrectOperation(parsedExpr);
}