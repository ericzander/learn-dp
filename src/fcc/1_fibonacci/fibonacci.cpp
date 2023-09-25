/* Fibonacci sequence */

// Unit testing
#include <catch2/catch_test_macros.hpp>

// Local
#include "ProblemRegistry.h"
#include "Utils.h"

#include <iostream>
#include <cstdint>
#include <functional>

#include <map>
#include <string>
#include <vector>

namespace Fibonacci
{
    using MemoTable = std::map<int, uint64_t>;

    // Recursion

    uint64_t recursion(int n)
    {
        if (n <= 2)
            return 1;

        return recursion(n - 2) + recursion(n - 1);
    }

    // DP (memoization)

    uint64_t _memoization_aux(int n, MemoTable &memo)
    {
        if (n <= 2)
            return 1;

        if (memo.count(n))
            return memo[n];

        int left = n - 2;
        int right = n - 1;

        // Calculate components and store in results in map
        memo.insert(std::make_pair(left, _memoization_aux(left, memo)));
        memo.insert(std::make_pair(right, _memoization_aux(right, memo)));

        return memo[left] + memo[right];
    }

    uint64_t memoization(int n)
    {
        MemoTable memo;

        return _memoization_aux(n, memo);
    }

    // DP (tabulation)

    uint64_t tabulation(int n)
    {
        if (n <= 2)
            return 1;

        std::vector<uint64_t> arr(n, 1);

        for (int i = 2; i < n; i++)
            arr[i] = arr[i - 2] + arr[i - 1];

        return arr[n - 1];
    }

    // Unit tests

    void unit_tests(std::function<uint64_t(int)> fn, bool do_hard)
    {
        CHECK(DPUtils::test_val(1, fn) == 1);
        CHECK(DPUtils::test_val(2, fn) == 1);
        CHECK(DPUtils::test_val(3, fn) == 2);
        CHECK(DPUtils::test_val(4, fn) == 3);
        CHECK(DPUtils::test_val(5, fn) == 5);
        CHECK(DPUtils::test_val(10, fn) == 55);

        if (do_hard)
            CHECK(DPUtils::test_val(30, fn) == 832040);
    }

    TEST_CASE("fib_r", "[fibonacci]")
    {
        std::function<uint64_t(int)> fn(recursion);

        DPUtils::print_header("recursion", "O(2^n)", "O(n)");

        unit_tests(fn, false);
    }

    TEST_CASE("fib_m", "[fibonacci]")
    {
        std::function<uint64_t(int)> fn(memoization);

        DPUtils::print_header("memoization", "O(n)", "O(n)");

        unit_tests(fn, true);
    }

    TEST_CASE("fib_t", "[fibonacci]")
    {
        std::function<uint64_t(int)> fn(tabulation);

        DPUtils::print_header("tabulation", "O(n)", "O(n)");

        unit_tests(fn, true);
    }

    // Core function

    void fibonacci()
    {
        std::cout << "Fibonacci Sequence" << std::endl;
    }

    REGISTER_PROBLEM(fibonacci);
}
