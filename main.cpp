#include <iostream>

#include "Calculator.hpp"


int main()
{
    std::string input;
    std::getline(std::cin, input);

    float result;

    try
    {
        auto calculator = Calculator(input);

        result = calculator.GetResult();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка, выход из программы: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Результат: " << result << std::endl;

    return 0;
}