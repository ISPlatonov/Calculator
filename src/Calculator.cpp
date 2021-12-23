#include "Calculator.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cctype>


std::string Calculator::ParseInput(std::string input)
{
    std::replace(input.begin(), input.end(), ',', '.');

    try {
        /*
        bool has_determ = true;
        auto iter = input.begin();

        while (iter++ != input.end())
        {
            if (isspace(*iter))
            {
                has_determ = false;
                {
                    while (isspace(*(iter++)));
                    if (brackets.find(*iter) != brackets.end() || signs.find(*iter) != signs.end())
                        has_determ = true;
                    else if (*iter == '.' || isdigit(*iter))
                        if (!has_determ)
                            throw std::invalid_argument("Между числами нет знака-разделителя");
                }
            }
        }
        */

        auto prev_iter = input.begin();
        auto iter = input.begin();
        bool has_determ = true;
        size_t signs_num = 0;
        size_t brackets_num = 0;

        while (iter != input.end())
        {
            signs_num = std::count_if(prev_iter, iter, [=] (char c) -> bool { return signs.find(c) != signs.end(); });
            brackets_num = std::count_if(prev_iter, iter, [=] (char c) -> bool { return brackets.find(c) != brackets.end(); });

            //std::cout << "signs_num: " << signs_num << std::endl;
            //std::cout << "bob: " << std::string(prev_iter, iter) << std::endl;
            //std::cout << "iter index: " << iter - input.begin() << std::endl;
            //std::cout << "prev index: " << prev_iter - input.begin() << std::endl;

            if (prev_iter == input.begin());
                //std::cout << "prev_iter == input.begin()" << std::endl;
            else if (signs_num == 0)
                throw std::invalid_argument("Между числами нет знака-разделителя");
            else if (signs_num > brackets_num + 1)
                throw std::invalid_argument("Слишком много знаков между числами");

            while (isdigit(*iter) || *iter == '.')
                ++iter;
            
            prev_iter = iter;
            iter = std::find_if(iter, input.end(), [] (char c) -> bool { return isdigit(c) || c == '.'; });
        }
    }
    catch (std::exception)
    {
        throw;
    }

    input.erase(std::remove_if(input.begin(), input.end(), isspace), input.end());

    size_t n = 0;
    auto iter = input.begin();
    auto end = input.end();
    
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


void Calculator::CheckSign(std::string::iterator& iter, char& sign)
{
    if (*iter == '+')
        ++iter;
    else if (*iter == '-')
        sign = *(iter), iter++;
    else if (*iter == '*' || *iter == '/')
        throw std::invalid_argument("Знак умножения или деления в начале выражения (м.б. внутри скобки); что имелось ввиду?");
}


void Calculator::CheckSign(std::string::iterator& iter)
{
    if (*iter == '+')
        ++iter;
    else if (*iter == '-')
        iter++;
    else if (*iter == '*' || *iter == '/')
        throw std::invalid_argument("Знак умножения или деления в начале выражения (м.б. внутри скобки); что имелось ввиду?");
}


float Calculator::BracketToFloat(std::string::iterator& begin, std::string::iterator& end, char sign, float result)
{
    //std::cout << "init: " << std::string(begin, end) << std::endl;
    //std::cout << "result: " << result << std::endl;
    //std::cout << "sign: " << sign << std::endl;

    auto iter = begin;
    auto new_iter = iter;

    if (end - begin == 0)
        return 0;
    
    CheckSign(iter, sign);

    bool do_find = true;

    while (true)
    {
        if (do_find)
            new_iter = std::find_first_of(iter, end, signs.begin(), signs.end());
        else
            do_find = true;

        //std::cout << "rest: " << std::string(iter, end) << std::endl;

        //std::cout << "sign: " << sign << std::endl;
        //std::cout << "result: " << result << std::endl;

        if (*iter == '(')
        {
            //std::cout << "skobka" << std::endl;
            auto local_iter = iter + 1;
            auto &local_end = end;
            std::string local_result = std::to_string(this->BracketToFloat(local_iter, local_end));

            //std::cout << "end - local_iter: " << end - local_iter << ", end - local_end: " << end - local_end << std::endl;
            //std::cout << "before: " << std::string(iter, local_end) << ' ' << "after: " << local_result << std::endl;

            auto index = iter - input.begin();

            input.replace(iter, local_end, local_result.begin(), local_result.end());

            iter = input.begin() + index;
            //begin = input.begin();
            end = this->input.end();

            //std::cout << "after replacing: " << std::string(iter, end) << std::endl;
            
            //if (iter != input.begin())
            //    --iter;
            if (sign == ' ')
                CheckSign(iter, sign);

            do_find = false;
            new_iter = std::find_first_of(iter + 1, end, signs.begin(), signs.end());

            continue;
        }
        else if (*(new_iter - 1) == ')')
        {
            //std::cout << "skobka szadi" << std::endl;
            while (*(new_iter - 1) == ')')
                --new_iter;
            result = this->PerformMathOperation(iter, new_iter, sign, result);
            end = ++new_iter;
            //std::cout << "exit 2: " << std::string(input.begin(), end) << std::endl;
            return result;
        }
    
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
                            //std::cout << "left operand: " << left_operand << std::endl;
                            auto local_result = std::to_string(this->BracketToFloat(local_iter, local_end, local_sign, left_operand));

                            //std::cout << "local result: " << local_result << std::endl;

                            //std::cout << "before: " << std::string(iter, local_end) << ' ' << "after: " << local_result << std::endl;

                            //std::cout << "rest before replace: " << std::string(iter, end) << std::endl;
                            //std::cout << "addressof: " << std::addressof(iter) << ' ' << std::addressof(end) << std::endl;
                            //std::cout << "input: " << input << std::endl;
                            
                            auto index = iter - input.begin();

                            input.replace(iter, local_end, local_result.begin(), local_result.end());

                            iter = input.begin() + index;
                            //begin = input.begin();
                            end = input.end();
                            //std::cout << "rest after replace: " << std::string(iter, end) << std::endl;
                            //std::cout << "addressof: " << std::addressof(iter) << ' ' << std::addressof(end) << std::endl;
                            //std::cout << "input: " << input << std::endl;

                            //std::cout << std::string(iter, local_end) << ' ' << sign << std::endl;

                            if (sign == ' ')
                                CheckSign(iter, sign);

                            continue;
                        }
                    }
                    else if (*new_iter == '+' || *new_iter == '-')
                    {
                        if (sign == '*' || sign == '/')
                        {
                            result = this->PerformMathOperation(iter, new_iter, sign, result);
                            end = new_iter;
                            //std::cout << "exit 1: " << std::string(iter, end) << std::endl;
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
                //std::cerr << e.what() << std::endl;
                throw;
            }
        }

        //std::cout << std::string(iter, end) << std::endl;
        if (new_iter == end)
        {
            //std::cout << "new_iter == end" << std::endl;
            break;
        }
        else
        {
            sign = *new_iter;
            iter = new_iter + 1;
        }
        
    }

    //std::cout << "exit 0: " << std::string(input.begin(), end) << std::endl;
    return result;
}


float Calculator::PerformMathOperation(const std::string::iterator& iter, const std::string::iterator& new_iter, const char& sign, const float& prev_num)
{
    try
    {
        //std::cout << "  math: " << prev_num << sign << std::string(iter, new_iter) << std::endl;

        auto num = std::stof(std::string(iter, new_iter));
        //std::cout << "left: " << num << "\tright: " << prev_num << std::endl;
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
                if (num == 0)
                    throw std::logic_error("Деление на 0");
                else
                    result /= num;
        }

        return result;
    }
    catch (const std::invalid_argument&)
    {
        //std::cerr << "Не получилось привести к числу (" << std::string(iter, new_iter) << ')' << std::endl;
        throw std::invalid_argument("Не получилось привести к числу (" + std::string(iter, new_iter) + ')');
    }
    catch (const std::exception& e)
    {
        //std::cerr << "math exit" << std::endl;
        throw;
    }
}


const float Calculator::GetResult()
{
    return this->result;
}