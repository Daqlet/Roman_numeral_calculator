#pragma once
#include <bits/stdc++.h>

struct Node {
    double value;
    char character;
    Node(double value_, char character_) {
        value = value_;
        character = character_;
    }
};

void RunConverter(std::istream&);
void Solve(std::string&);
std::string ConvertToRoman(double);
bool Parse(const std::string&, std::vector<Node>&);
bool IsOperation(const char&);
double CalculateExpr(int&, const std::vector<Node>&);