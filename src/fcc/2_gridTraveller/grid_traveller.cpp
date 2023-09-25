/* Grid traveller

    Given a rectangular grid of dimensions m * n where you can only
    move right and down, how many ways can you get to the bottom right?

*/

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

namespace GridTraveller
{
    class Input
    {
    public:
        int m;
        int n;

        Input(int m, int n) : m(m), n(n){};

        friend std::ostream &operator<<(std::ostream &os, const Input &input);
    };

    std::ostream &operator<<(std::ostream &os, const Input &input)
    {
        os << "(" << input.m << "*" << input.n << ")";
        return os;
    }

    using Coord = std::pair<int, int>;
    using MemoTable = std::map<Coord, uint64_t>;

    // Recursion

    uint64_t _recursion_aux(int m, int n)
    {
        if (m <= 1 || n <= 1)
            return 1;

        // Return # of paths after moving down + paths after moving right
        return _recursion_aux(m - 1, n) + _recursion_aux(m, n - 1);
    }

    uint64_t recursion(Input input)
    {
        int m = input.m;
        int n = input.n;

        return _recursion_aux(m, n);
    }

    // DP (memoization)

    uint64_t _memoization_aux(int m, int n, MemoTable &memo)
    {
        if (m <= 1 || n <= 1)
            return 1;

        Coord coord = Coord(m, n);

        if (memo.count(coord))
            return memo[coord];

        Coord down = Coord(m - 1, n);
        Coord right = Coord(m, n - 1);

        memo.insert(std::make_pair(down, _memoization_aux(down.first, down.second, memo)));
        memo.insert(std::make_pair(right, _memoization_aux(right.first, right.second, memo)));

        return memo[down] + memo[right];
    }

    uint64_t memoization(Input input)
    {
        int m = input.m;
        int n = input.n;

        MemoTable memo;

        return _memoization_aux(m, n, memo);
    }

    // DP (tabulation)

    uint64_t tabulation(Input input)
    {
        int m = input.m;
        int n = input.n;

        if (m == 1 || n == 1)
            return 1;

        // Create m * n grid filled with ones (bottom and right have only 1 path)
        std::vector<std::vector<uint64_t>> grid(m, std::vector<uint64_t>(n, 1));

        // Iteratively fill grid w/ paths to each square until bottom right reached
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                grid[i][j] = grid[i - 1][j] + grid[i][j - 1];
            }
        }

        return grid[m - 1][n - 1];
    }

    // Unit Tests

    void unit_tests(std::function<uint64_t(Input)> fn, bool do_hard)
    {
        CHECK(DPUtils::test_val(Input(1, 1), fn) == 1);
        CHECK(DPUtils::test_val(Input(2, 2), fn) == 2);
        CHECK(DPUtils::test_val(Input(3, 2), fn) == 3);
        CHECK(DPUtils::test_val(Input(3, 3), fn) == 6);

        if (do_hard)
            CHECK(DPUtils::test_val(Input(18, 18), fn) == 2333606220);
    }

    TEST_CASE("grid_r", "[grid_traveller]")
    {
        std::function<uint64_t(Input)> fn(recursion);

        DPUtils::print_header("recursion", "O(2^(n+m))", "O(n + m)");

        unit_tests(fn, false);
    }

    TEST_CASE("grid_m", "[grid_traveller]")
    {
        std::function<uint64_t(Input)> fn(memoization);

        DPUtils::print_header("memoization", "O(n *m)", "O(n * m)");

        unit_tests(fn, true);
    }

    TEST_CASE("grid_t", "[grid_traveller]")
    {
        std::function<uint64_t(Input)> fn(tabulation);

        DPUtils::print_header("tabulation", "O(n * m)", "O(n * m)");

        unit_tests(fn, true);
    }

    // Core function

    void grid_traveller()
    {
        std::cout << "Grid traveller" << std::endl;
    }

    REGISTER_PROBLEM(grid_traveller);
}
