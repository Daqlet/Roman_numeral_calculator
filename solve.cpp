#include "main.h"

void RunConverter(std::istream& is) {
    std::string task;
    while (std::getline(is, task)) {
        Solve(task);
    }
}

void Solve(std::string& task) {
    std::vector<Node> parsedExpr;
    task.erase(remove(task.begin(), task.end(), ' '), task.end());
     if (Parse(task, parsedExpr)) {
        int idx = 0;
        double answer = CalculateExpr(idx, parsedExpr);
        std::cout << ConvertToRoman(answer) << std::endl;
    }
    else {
        std::cout << "error: wrong input format" << std::endl;
    }
}