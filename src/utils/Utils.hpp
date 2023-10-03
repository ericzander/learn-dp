#ifndef DP_UTILS_H
#define DP_UTILS_H

#include <iostream>
#include <iomanip>

#include <functional>
#include <string>
#include <chrono>

namespace DPUtils
{
    template <typename T1, typename T2>
    T1 test_fn(T2 n, std::function<T1(T2)> fn,
               int n_width = 2, int out_width = 12, int time_width = 7)
    {
        using namespace std::chrono;

        // Start timer
        auto t1 = high_resolution_clock::now();

        // Given function call
        T1 output = fn(n);

        // Stop timer
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;

        // Print output
        std::cout << "fn(" << std::setw(n_width) << std::right << n << ")"
                  << " = " << std::setw(out_width) << std::right << output
                  << "  :  [ " << std::setw(time_width) << std::left << ms_double.count() << " ms ]"
                  << std::endl;

        return output;
    }

    void print_header(std::string fn_type,
                      std::string time_complexity = "", std::string space_complexity = "");

    void print_ln(const std::string &line);
}

#endif
