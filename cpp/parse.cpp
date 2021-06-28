#include "main.h"

std::unordered_map<char, int> mapRoman{
    {'M', 1000},
    {'D', 500},
    {'C', 100},
    {'L', 50},
    {'X', 10},
    {'V', 5},
    {'I', 1},
    {'Z', 0},
};
const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
const std::string romans[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

bool IsOperation(const char& c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string ConvertToRoman(double value) {
    value = floor(value);
    if(1 > abs(value)) return "Z";
    std::string result = "";
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

double ConvertToDouble(const std::string& roman) {
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

bool IsCorrectOperation(const std::vector<Node>& parsedExpr) {
    bool needOperation = 0;
    int scopeCount = 0;
    for(int i = 0; i < parsedExpr.size(); ++i) {
        if(parsedExpr[i].character == '(') {
            scopeCount++; continue;
        } else if(parsedExpr[i].character == ')') {
            if(--scopeCount < 0) {
                return 0;
            }
            continue;
        }
        if(needOperation != IsOperation(parsedExpr[i].character)) {
            return 0;
        }
        needOperation = !needOperation;
    }
    return scopeCount == 0;
}

bool IsCorrectRomanNumber(const std::string& roman) {
    if(roman.length() == 1 && roman[0] == 'Z') return 1;
    std::regex romanExpr ("^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$");
    bool ok = regex_match(roman, romanExpr);
    return ok && !roman.empty();
}

bool Parse(const std::string& task, std::vector<Node>& parsedExpr) {
    bool needOperation = 0;
    for(int i = 0; i < task.length(); ) {
        if(task[i] == ')' || task[i] == '(') {
            parsedExpr.push_back(Node(0, task[i++]));
            continue;
        }
        if(needOperation) {
            parsedExpr.push_back(Node(0, task[i++]));
            needOperation = 0;
            continue;
        }
        int sign = 1;
        if(task[i] == '-') {
            i++;
            sign = -1;
        }
        int start = i;
        while(mapRoman.count(task[i])) {
            i++;
        } 
        std::string romanNumber = task.substr(start, i-start);
        if(IsCorrectRomanNumber(romanNumber)) {
            double val = sign * ConvertToDouble(romanNumber);
            parsedExpr.push_back(Node(val, '0'));
        } else return 0;
        needOperation = 1;
    }
    return IsCorrectOperation(parsedExpr);
}