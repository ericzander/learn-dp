/* LeetCode 70: Climbing Stairs */

// Unit testing
#include <catch2/catch_test_macros.hpp>

// Local
#include "ProblemRegistry.hpp"
#include "Utils.hpp"

#include <iostream>
#include <vector>

namespace ClimbingStairs
{
    void climbing_stairs()
    {
        auto print_ln = DPUtils::print_ln;

        print_ln("< 70: Climbing Stairs >\n");
        
        print_ln("Given n, give number of ways to climb this number");
        print_ln("of steps by taking 1 or 2 steps at a time.\n");

        print_ln("Simple bottom-up dynamic programming problem.");
    }

    REGISTER_PROBLEM(climbing_stairs);

    // Implementations

    namespace Tabulation
    {
        uint64_t compute(int n)
        {
            std::vector<int> table(n + 1, 1);

            for (int i = 2; i < n + 1; i ++)
                table[i] = table[i - 2] + table[i - 1];

            return table[n];
        }
    }

    // Unit tests

    TEST_CASE("climb_t", "[climbing_stairs]")
    {
        std::function<uint64_t(int)> fn(Tabulation::compute);

        DPUtils::print_header("tabulation");

        CHECK(DPUtils::test_fn(2, fn) == 2);
        CHECK(DPUtils::test_fn(3, fn) == 3);

        std::cout << std::endl;
    }
}
