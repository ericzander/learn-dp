#ifndef DP_UTILS_H
#define DP_UTILS_H

#include <iostream>

#include <functional>
#include <string>

namespace DPUtils
{
    template <typename T1, typename T2>
    T1 test_val(T2 n, std::function<T1(T2)> fn)
    {
        T1 output = fn(n);

        std::cout << "fn(" << n << ") == " << output << std::endl;

        return output;
    }

    void print_header(std::string fn_type,
                      std::string time_complexity = "", std::string space_complexity = "");
}

#endif
