/* Fibonacci sequence */

// Unit testing
#include <catch2/catch_test_macros.hpp>

// Local
#include "ProblemRegistry.h"
#include "Utils.h"

#include <iostream>
#include <cstdint>
#include <functional>

#include <unordered_map>
#include <string>
#include <vector>

namespace Fibonacci
{
    void fibonacci()
    {
        auto print_ln = DPUtils::print_ln;

        print_ln("< Fibonacci Sequence >\n");

        print_ln("Given an input value n, find fib(n) according to the following:\n");
        print_ln("  1)  fib(1) = fib(2) = 1");
        print_ln("  2)  fib(n) = fib(n - 1) + fib(n - 2)");

        print_ln("\nUsage:\n");
        print_ln("  uint64_t result = Fibonacci::Recursion.compute(n);");
        print_ln("  uint64_t result = Fibonacci::Memoization.compute(n);");
        print_ln("  uint64_t result = Fibonacci::Tabulation.compute(n);");

        print_ln("\n< Recursion/Memoization >\n");

        print_ln(R"~(                fib(6) = 8                 )~");
        print_ln(R"~(                        / \                )~");
        print_ln(R"~(                       /   \               )~");
        print_ln(R"~(             fib(5) = 5  +  3* = fib(4)    )~");
        print_ln(R"~(                     / \                   )~");
        print_ln(R"~(                    /   \                  )~");
        print_ln(R"~(          fib(4) = 3  +  2* = fib(3)       )~");
        print_ln(R"~(                  / \                      )~");
        print_ln(R"~(                 /   \                     )~");
        print_ln(R"~(       fib(3) = 2  +  1 = fib(2)           )~");
        print_ln(R"~(               / \                         )~");
        print_ln(R"~(              /   \                        )~");
        print_ln(R"~(    fib(2) = 1  +  1 = fib(1)              )~");

        print_ln("\n< Tabulation >\n");
        print_ln("Each value is the sum of the previous two values.\n");
        print_ln("    n  :   1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 ...");
        print_ln("fib(n) :   1 |  1 |  2 |  3 |  5 |  8 | 13 | 21 ...");
        print_ln("                1 +  2 =  3 ->                     ");
    }

    REGISTER_PROBLEM(fibonacci);

    // Implementations

    namespace Recursion
    {
        uint64_t compute(int n)
        {
            if (n <= 2)
                return 1;

            return compute(n - 2) + compute(n - 1);
        }
    }

    namespace Memoization
    {
        using MemoTable = std::unordered_map<int, uint64_t>;

        static uint64_t aux(int n, MemoTable &memo)
        {
            if (n <= 2)
                return 1;

            if (memo.count(n))
                return memo[n];

            int left = n - 2;
            int right = n - 1;

            // Calculate components and store in results in map
            memo.insert(std::make_pair(left, aux(left, memo)));
            memo.insert(std::make_pair(right, aux(right, memo)));

            return memo[left] + memo[right];
        }

        uint64_t compute(int n)
        {
            // Call recursive function
            MemoTable memo;
            return aux(n, memo);
        }
    }

    namespace Tabulation
    {
        uint64_t compute(int n)
        {
            if (n <= 2)
                return 1;

            std::vector<uint64_t> arr(n, 1);

            for (int i = 2; i < n; i++)
                arr[i] = arr[i - 2] + arr[i - 1];

            return arr[n - 1];
        }
    }

    // Unit tests

    void unit_tests(std::function<uint64_t(int)> fn, bool do_hard)
    {
        CHECK(DPUtils::test_fn(1, fn) == 1);
        CHECK(DPUtils::test_fn(2, fn) == 1);
        CHECK(DPUtils::test_fn(5, fn) == 5);
        CHECK(DPUtils::test_fn(10, fn) == 55);
        CHECK(DPUtils::test_fn(20, fn) == 6'765);
        CHECK(DPUtils::test_fn(40, fn) == 102'334'155);

        if (do_hard)
        {
            CHECK(DPUtils::test_fn(50, fn) == 12'586'269'025);
        }

        std::cout << std::endl;
    }

    TEST_CASE("fib_r", "[fibonacci]")
    {
        std::function<uint64_t(int)> fn(Recursion::compute);

        DPUtils::print_header("recursion", "O(2^n)", "O(n)");

        unit_tests(fn, false);
    }

    TEST_CASE("fib_m", "[fibonacci]")
    {
        std::function<uint64_t(int)> fn(Memoization::compute);

        DPUtils::print_header("memoization", "O(n)", "O(n)");

        unit_tests(fn, true);

        std::cout << std::endl;
    }

    TEST_CASE("fib_t", "[fibonacci]")
    {
        std::function<uint64_t(int)> fn(Tabulation::compute);

        DPUtils::print_header("tabulation", "O(n)", "O(n)");

        unit_tests(fn, true);

        std::cout << std::endl;
    }
}
