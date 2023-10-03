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
#include <iomanip>

#include <cstdint>
#include <functional>
#include <algorithm>

#include <map>
#include <string>
#include <vector>

namespace GridTraveller
{
    void grid_traveller()
    {
        auto print_ln = DPUtils::print_ln;

        print_ln("< Grid Traveller >\n");

        print_ln("Given a rectangular grid of dimensions m * n in which you can only ");
        print_ln("move right and down, how many ways can you get to the bottom right?\n");
        print_ln("  Usage:\n");
        print_ln("    Fibonacci::Grid grid{x, y};");
        print_ln("    uint64_t rec = Fibonacci::Recursion.compute(grid);");
        print_ln("    uint64_t mem = Fibonacci::Recursion.compute(grid);");
        print_ln("    uint64_t tab = Fibonacci::Memoization.compute(grid);\n");
        print_ln("  Example grid and path:\n");
        print_ln(R"~(              n = 4       )~");
        print_ln(R"~(        +---------------+ )~");
        print_ln(R"~(        | > | v |   |   | )~");
        print_ln(R"~(        |---------------| )~");
        print_ln(R"~(   m=3  |   | > | > | v | )~");
        print_ln(R"~(        |---------------| )~");
        print_ln(R"~(        |   |   |   | E | )~");
        print_ln(R"~(        +---------------+ )~");

        print_ln("\n< Recursion/Memoization >\n");

        print_ln("The number of ways to the end from any given spot is the sum of the");
        print_ln("number of ways from the tile directly below and to the right.");
        print_ln("\nConsequently, we can recursively compute these values until an edge");
        print_ln("is hit; there is only 1 way to the end in this case. Notably, there");
        print_ln("are the same number of ways to travel from tile (n,m) and (m,n).\n");
        print_ln(R"~(          fn(3,4) = 10                  )~");
        print_ln(R"~(                   / \                  )~");
        print_ln(R"~(           down   /   \   right         )~");
        print_ln(R"~(                 /     \                )~");
        print_ln(R"~(      fn(2,4) = 4   +    6 = fn(3,3)    )~");
        print_ln(R"~(               / \      / \             )~");
        print_ln(R"~(              /   \    3*  3* = fn(3,2) )~");
        print_ln(R"~(             /     \                    )~");
        print_ln(R"~(  fn(1,4) = 1   +   3 = fn(2,3)         )~");
        print_ln(R"~(                   / \                  )~");
        print_ln(R"~(                  /   \                 )~");
        print_ln(R"~(       fn(1,3) = 1  +  2 = fn(2,2)      )~");
        print_ln(R"~(                      / \               )~");
        print_ln(R"~(                     /   \              )~");
        print_ln(R"~(          fn(1,2) = 1  +  1 = fn(2,1)   )~");

        print_ln("\n< Tabulation >\n");
        print_ln("Treat each tile as the bottom right of its own subgrid. Its value is");
        print_ln("the number of ways to it in its own subgrid.\n");
        print_ln("Init all values to 1 for the borders and loop through each value setting");
        print_ln("it to the sum of the value above and to the left as below. The bottom");
        print_ln("right value represents the paths to the end of the whole grid.\n");
        print_ln(R"~(              n = 4           )~");
        print_ln(R"~(        +-------------------+ )~");
        print_ln(R"~(        |  1 |  1 |  1 |  1 | )~");
        print_ln(R"~(        |-------------------| )~");
        print_ln(R"~(   m=3  |  1 |  2 |  3 |  4 | )~");
        print_ln(R"~(        |-------------------| )~");
        print_ln(R"~(        |  1 |  3 |  6 | 10 | )~");
        print_ln(R"~(        +-------------------+ )~");
    }           

    REGISTER_PROBLEM(grid_traveller);

    // Setup

    struct Grid
    {
        std::pair<int, int> dims;

        Grid(int m, int n) : dims(m, n){};

        friend std::ostream &operator<<(std::ostream &os, const Grid grid)
        {
            auto dims = grid.dims;

            int dim_width = 2;

            os << std::setw(dim_width) << std::right << dims.first
               << ","
               << std::setw(dim_width) << std::right << dims.second;

            return os;
        }
    };

    // Implementations

    namespace Recursion
    {
        static uint64_t _aux(int m, int n)
        {
            if (m <= 1 || n <= 1)
                return 1;

            // Return # of paths after moving down + paths after moving right
            return _aux(m - 1, n) + _aux(m, n - 1);
        }

        uint64_t compute(Grid grid)
        {
            auto [m, n] = grid.dims;

            return _aux(m, n);
        }
    }

    namespace Memoization
    {
        using Dims = std::pair<int, int>;
        using MemoTable = std::map<Dims, uint64_t>;

        static Dims _sorted_pair(int m, int n)
        {
            if (m >= n)
                return Dims{m, n};

            return Dims{n, m};
        }

        static uint64_t _aux(int m, int n, MemoTable &memo)
        {
            if (m <= 1 || n <= 1)
                return 1;

            Dims coord = _sorted_pair(m, n);

            if (memo.count(coord))
                return memo[coord];

            Dims down = _sorted_pair(m - 1, n);
            Dims right = _sorted_pair(m, n - 1);

            memo[down] = _aux(down.first, down.second, memo);
            memo[right] = _aux(right.first, right.second, memo);

            return memo[down] + memo[right];
        }

        uint64_t compute(Grid grid)
        {
            auto [m, n] = grid.dims;

            MemoTable memo;

            return _aux(m, n, memo);
        }
    }

    namespace Tabulation
    {
        uint64_t compute(Grid grid)
        {
            auto [m, n] = grid.dims;

            if (m == 1 || n == 1)
                return 1;

            // Create m * n array filled with ones (bottom and right have only 1 path)
            std::vector<std::vector<uint64_t>> arr(m, std::vector<uint64_t>(n, 1));

            // Iteratively fill grid array w/ paths to each square until bottom right reached
            for (int i = 1; i < m; i++)
            {
                for (int j = 1; j < n; j++)
                {
                    arr[i][j] = arr[i - 1][j] + arr[i][j - 1];
                }
            }

            return arr[m - 1][n - 1];
        }
    }

    // Unit Tests

    void unit_tests(std::function<uint64_t(Grid)> fn, bool do_hard)
    {
        CHECK(DPUtils::test_fn(Grid(1, 1), fn) == 1);
        CHECK(DPUtils::test_fn(Grid(2, 2), fn) == 2);
        CHECK(DPUtils::test_fn(Grid(3, 2), fn) == 3);
        CHECK(DPUtils::test_fn(Grid(3, 3), fn) == 6);
        CHECK(DPUtils::test_fn(Grid(12, 10), fn) == 167'960);

        if (do_hard)
            CHECK(DPUtils::test_fn(Grid(18, 18), fn) == 2'333'606'220);

        std::cout << std::endl;
    }

    TEST_CASE("grid_r", "[grid_traveller]")
    {
        std::function<uint64_t(Grid)> fn(Recursion::compute);

        DPUtils::print_header("recursion", "O(2^(n+m))", "O(n + m)");

        unit_tests(fn, false);
    }

    TEST_CASE("grid_m", "[grid_traveller]")
    {
        std::function<uint64_t(Grid)> fn(Memoization::compute);

        DPUtils::print_header("memoization", "O(n * m)", "O(n * m)");

        unit_tests(fn, true);
    }

    TEST_CASE("grid_t", "[grid_traveller]")
    {
        std::function<uint64_t(Grid)> fn(Tabulation::compute);

        DPUtils::print_header("tabulation", "O(n * m)", "O(n * m)");

        unit_tests(fn, true);
    }
}
