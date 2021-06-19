#include <bits/stdc++.h>
using namespace std;
#define ll long long

unordered_map<char, int> roman{
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

struct node {
    double value;
    char operation;
    bool isOperation;
};
vector<node> a;

bool isOperation(node n) {
    return n.isOperation;
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
        if(i+1 < s.length() && roman[s[i]] < roman[s[i+1]]) {
            res += roman[s[i+1]] - roman[s[i]];
            i++;
        } else {
            res += roman[s[i]];
        }
    }
    return res;
}

string isCorrectOperation() {
    bool isOp = 0, error = 0;
    int scope = 0;
    for(int i = 0; i < a.size(); i++) {
        //cout << i << " " << isOp << " " << a[i].operation << endl;
        if(isOp) {
            if(a[i].operation == ')') {
                if(--scope < 0) {
                    error = 1;
                }
            } else if (a[i].operation == '(' || !isOperation(a[i])) {
                error = 1;
            } else {
                isOp = 0;
            }
        } else {
            if(a[i].operation == '(') {
                ++scope;
            } else if(a[i].operation == ')' || isOperation(a[i])) {
                error = 1;
            } else {
                isOp = 1;
            }
        }
        if (error) break;
    }
    if(error || scope || !isOp) return "error: wrong input format";
    return "ok";
}

bool isCorrectPair(int first, int second) {
    if(!first || !second) return 0;
    int temp = first;
    while(temp % 10 == 0) temp /= 10;
    return (second / first <= 10) && temp == 1; 
}

bool isCorrectRomanNumber(string s) {
    if(!s.length() || !roman.count(s[0])) return 0;
    int count = 1, mustGoDown = 0, was = -1;
    for(int i = 1; i < s.length(); i++) {
        if(!roman.count(s[i])) return 0;
        int first = roman[s[i-1]], second = roman[s[i]];
        if(first < second) {
            if(was != -1 && second > was) {
                return 0;
            }
            if(mustGoDown || count > 1 || !isCorrectPair(first, second)) {
                return 0;
            } 
            mustGoDown = 1;
            count = 1;
        } else if(first == second) {
            if(++count > 3 || mustGoDown || !isCorrectPair(first, second)) {
                return 0;
            }
        } else {
            count = 1;
            mustGoDown = 0;
            if(was != -1 && second >= was) {
                return 0;
            }
        }
        was = first;
    }
    return 1;
}

bool parse(string s) {
    bool isOp = 0;
    for(int i = 0; i < s.length(); ) {
        //cout << "i = " << i << " " << s[i] << endl;
        if(s[i] == ' ') {
            i++;
            continue;
        }
        if(isOp || s[i] == ')' || s[i] == '(') {
            bool oper = s[i] != ')' && s[i] != '(';
            a.push_back({0, s[i], oper});
            isOp = s[i] == ')';
            i++;
            continue;
        }
        int sign = 1;
        if(s[i] == '-') {
            i++;
            sign = -1;
        }
        while(s[i] == ' ') i++;
        int start = i;
        while(roman.count(s[i])) {
            i++;
        } 
        string romanNumber = s.substr(start, i-start);
        if(isCorrectRomanNumber(romanNumber)) {
            double val = sign * romanToDouble(romanNumber);
            a.push_back({val, '0', 0});
        }
        isOp = 1;
    }
    for(int i = 0; i < a.size(); ++i) {
        //cout << i << " " << a[i].operation << " " << a[i].value << endl;
    }
    string message = isCorrectOperation();
    if(message != "ok") {
        cout << message << endl;
        return 0;
    }
    return 1;
}

bool lowPriority(node n) {
    return n.operation == '+' || n.operation == '-';
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

double calculate(int &i) {
    cout << "start: " << i << " a size " << a.size() << endl;
    stack<node> st;
    for(; i < a.size(); i++) {
        cout << "in " << i << endl;
        if(a[i].operation == ')') {
            break;
        }
        if(isOperation(a[i])) {
            st.push(a[i]);
            continue;
        }
        node temp = a[i];
        if(a[i].operation == '(') {
            i++;
            temp = {calculate(i), '0', 0};
        }
        if(st.empty()) {
            st.push(temp);
        } else if (lowPriority(st.top())) {
            if(st.top().operation == '-') {
                st.pop();
                st.push({0, '+', 1});
                temp.value = -temp.value;
            }
            st.push(temp);
        } else {
            node oper = st.top(); st.pop();
            node val = st.top(); st.pop();
            st.push(comb(val.value, temp.value, oper.operation));
            cout << "push " << temp.value << " " << val.value << endl;
        }
    }
    while(st.size() > 1) {
        node val2 = st.top(); st.pop();
        node oper = st.top(); st.pop();
        node val1 = st.top(); st.pop();
        cout << val1.value << " " << oper.operation << " " << val2.value << endl;
        st.push(comb(val1.value, val2.value, oper.operation));
    }
    cout << "finish " << i << " val " << st.top().value << endl;
    return st.top().value;
}

void solve(string s) {
    a.clear();
    if(!parse(s)) {
        return;
    }
    int i = 0;
    double ans = calculate(i);
    //cout << ans << endl;
    cout << doubleToRoman(ans) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; //cin >> t;
    string s;
    while(getline(cin, s)) {
        cout << isCorrectRomanNumber(s) << endl;
        //solve(s);
    }
    return 0;
}