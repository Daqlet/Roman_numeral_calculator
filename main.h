#pragma once
#include <bits/stdc++.h>
using namespace std;

struct node {
    double value;
    char symbol;
    node(double v, char c) {
        value = v;
        symbol = c;
    }
};


void solve(string&);
string doubleToRoman(double);
bool parse(string&, vector<node>&);
bool isOperation(char);
double calculate(int&, vector<node>&);