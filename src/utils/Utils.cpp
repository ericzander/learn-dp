#include "Utils.hpp"

#include <iostream>

#include <functional>
#include <string>

namespace DPUtils
{
    void print_header(std::string fn_type,
        std::string time_complexity, std::string space_complexity)
    {
        std::cout << "-------------------" << std::endl;
        std::cout << fn_type << std::endl;

        if (!time_complexity.empty())
            std::cout << "   time : " << time_complexity << std::endl;

        if (!space_complexity.empty())
            std::cout << "  space : " << space_complexity << std::endl;
            
        std::cout << "-------------------" << std::endl;
    }

    void print_ln(const std::string &line)
    {
        std::cout << line << "\n";
    }
}
