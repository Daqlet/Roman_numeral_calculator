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
    double val;
    char op;
};
vector<node> a;

string doubleToRoman(double n) {
    if(1 > abs(n)) return "Z";
    string result = "";
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
    int sign = 1, i = 0;
    if(s[0] == '-') {
        sign = -1; 
        i++;
    }
    while(i < s.length()) {
        if(roman[s[i]] < roman[s[i+1]]) {
            res += roman[s[i+1]] - roman[s[i]];
            i++;
        } else {
            res += roman[s[i]];
        }
        i++;
    }
    return res*sign;
}

void parse(string s) {
    bool isOp = 0;
    for(int i = 0; i < s.length(); ) {
        if(s[i] == ' ') {
            i++;
            continue;
        }
        if(isOp || s[i] == ')' || s[i] == '(') {
            a.push_back({0, s[i]});
            isOp = s[i] == ')';
            i++;
            continue;
        }
        int start = i;
        if(s[i] == '-') {
            i++;
        }
        while(roman.count(s[i])) {
            i++;
        } 
        a.push_back({romanToDouble(s.substr(start, i-start)), '0'});
        isOp = 1;
    }
    for(int i = 0; i < a.size(); ++i) {
        //cout << i << " " << a[i].op << " " << a[i].val << endl;
    }
}

bool lowPriority(node n) {
    return n.op == '+' || n.op == '-';
}

bool isOperation(node n) {
    return n.op == '+' || n.op == '-' || n.op == '*' || n.op == '/';
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
    //cout << "start: " << i << " a size " << a.size() << endl;
    stack<node> st;
    for(; i < a.size(); i++) {
        //cout << "in " << i << endl;
        if(a[i].op == ')') {
            break;
        }
        if(isOperation(a[i])) {
            st.push(a[i]);
            continue;
        }
        node temp = a[i];
        if(a[i].op == '(') {
            i++;
            temp = {calculate(i), '0'};
        }
        if(st.empty() || lowPriority(st.top())) {
            st.push(temp);
        } else {
            node oper = st.top(); st.pop();
            node val = st.top(); st.pop();
            st.push(comb(temp.val, val.val, oper.op));
            //cout << "push " << temp.val << " " << val.val << endl;
        }
    }
    while(st.size() > 1) {
        node val2 = st.top(); st.pop();
        node oper = st.top(); st.pop();
        node val1 = st.top(); st.pop();
        st.push(comb(val1.val, val2.val, oper.op));
    }
    //cout << "finish " << i << " val " << st.top().val << endl;
    return st.top().val;
}

void solve(string s) {
    a.clear();
    parse(s);
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
        solve(s);
    }
    return 0;
}