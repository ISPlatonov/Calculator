#pragma once

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cctype>


class Calculator
// namespace -> class
{
public:
    Calculator(std::string input);

    std::string ParseInput(std::string input);
    float BracketToFloat(std::string::iterator& begin, std::string::iterator& end, char sign = ' ', float result = 0);
    float PerformMathOperation(const std::string::iterator& iter, const std::string::iterator& new_iter, const char& sign, const float& prev_num);
    const float GetResult();

private:
    std::string input;
    float result;

    std::set<char> brackets = {'(', ')'};
    std::set<char> signs = {'+', '-', '*', '/'};//')', '('};
    std::set<char> signs_1st = {'*', '/'};
    std::set<char> signs_2nd = {'+', '-'};

    void CheckSign(std::string::iterator&, char&);
    void CheckSign(std::string::iterator&);
};