#pragma once
#include <bits/stdc++.h>
using namespace std;

struct node {
    double value;
    char symbol;
    node(double value_, char symbol_) {
        value = value_;
        symbol = symbol_;
    }
};


void solve(string&);
string doubleToRoman(double);
bool parse(string&, vector<node>&);
bool isOperation(char);
double calculate(int&, vector<node>&);