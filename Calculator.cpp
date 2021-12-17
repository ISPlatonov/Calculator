#include "Calculator.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cctype>


std::string Calculator::ParseInput(std::string input)
{
    input.erase(std::remove_if(input.begin(), input.end(), isspace), input.end());
    std::replace(input.begin(), input.end(), ',', '.');

    size_t n = 0;
    auto iter = input.begin();
    auto end = input.end();
    std::set<char> brackets = {'(', ')'};
    while (true)
    {
        iter = std::find_first_of(iter, end, brackets.begin(), brackets.end());
        if (iter == end)
            break;
        switch (*iter)
        {
            case ('('):
                ++n;
                break;
            case (')'):
                if (n == 0)
                    throw std::invalid_argument("Неправильный порядок скобок");
                else
                    --n;
                break;
        }
        iter += 1;
    }
    if (n != 0)
            throw std::invalid_argument("Не хватает скобок");

    return input;
}


Calculator::Calculator(std::string input)
{
    this->input = input;

    this->input = this->ParseInput(this->input);
    auto end = this->input.end();
    auto begin = this->input.begin();
    result = this->BracketToFloat(begin, end);
}


float Calculator::BracketToFloat(std::string::iterator& begin, std::string::iterator& end, char sign, float result)
{
    std::set<char> signs = {'+', '-', '*', '/'};//')', '('};
    std::set<char> signs_1st = {'*', '/'};
    std::set<char> signs_2nd = {'+', '-'};

    auto iter = begin;
    auto new_iter = iter;

    if (end - begin == 0)
        return 0;

    while (true)
    {
        new_iter = std::find_first_of(iter, end, signs.begin(), signs.end());

        if (*iter == '(')
        {
            //const auto &local_iter = iter + 1;
            auto &local_end = end;
            std::string local_result = std::to_string(this->BracketToFloat(++iter, local_end));

            auto index = --iter - input.begin();

            input.replace(iter, local_end, local_result.begin(), local_result.end());

            iter = input.begin() + index;
            //begin = input.begin();
            end = this->input.end();

            continue;
        }
        else if (*(new_iter - 1) == ')')
        {
            result = this->PerformMathOperation(iter, new_iter - 1, sign, result);
            end = new_iter;
            return result;
        }
    
        if (*iter == '+')
        {
            ++iter;
            continue;
        }
        else if (*iter == '-')
        {
            sign = *(iter), iter++;
            continue;
        }
        else if (*iter == '*' || *iter == '/')
            throw std::invalid_argument("Знак умножения или деления в начале выражения (м.б. внутри скобки); что имелось ввиду?");
    
        else
        {
            // mb try
            try
            {
                if (new_iter != end)
                {
                    if (*new_iter == '*' || *new_iter == '/')
                    {
                        if (sign == '*' || sign == '/')
                        {
                            result = this->PerformMathOperation(iter, new_iter, sign, result);
                        }
                        else
                        {
                            std::string::iterator &local_end = end;

                            float left_operand = std::stof(std::string(iter, new_iter));
                            auto local_sign = *(new_iter);
                            auto &local_iter = ++new_iter;
                            auto local_result = std::to_string(this->BracketToFloat(local_iter, local_end, local_sign, left_operand));

                            auto index = iter - input.begin();

                            input.replace(iter, local_end, local_result.begin(), local_result.end());

                            iter = input.begin() + index;
                            //begin = input.begin();
                            end = input.end();
                            
                            continue;
                        }
                    }
                    else if (*new_iter == '+' || *new_iter == '-')
                    {
                        if (sign == '*' || sign == '/')
                        {
                            result = this->PerformMathOperation(iter, new_iter, sign, result);
                            end = new_iter;
                            
                            return result;
                        }
                        else
                        {                            
                            result = this->PerformMathOperation(iter, new_iter, sign, result);
                        }
                    }
                }
                else
                {
                    result = this->PerformMathOperation(iter, new_iter, sign, result);
                    return result;
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
                throw;
            }
        }

        if (new_iter == end)
        {
            break;
        }
        else
        {
            sign = *new_iter;
            iter = new_iter + 1;
        }
        
    }

    return result;
}


float Calculator::PerformMathOperation(const std::string::iterator& iter, const std::string::iterator& new_iter, const char& sign, const float& prev_num)
{
    try
    {
        auto num = std::stof(std::string(iter, new_iter));
        //iter = new_iter + 1;
        float result = prev_num;

        switch (sign)
        {
            case '+':
                result += num;
                break;
            case ' ':
                result += num;
                break;
            case '-':
                result -= num;
                break;
            case '*':
                result *= num;
                break;
            case '/':
                try
                {
                    result / num;
                }
                catch(const std::logic_error& e)
                {
                    std::cerr << "На ноль делишь" << std::endl;
                    throw;
                }
        }

        return result;
    }
    catch (const std::invalid_argument&)
    {
        std::cerr << "Не получилось привести к числу (" << std::string(iter, new_iter) << ')' << std::endl;
        throw;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
}


const float Calculator::GetResult()
{
    return this->result;
}