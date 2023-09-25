/* Grid traveller

    Given a rectangular grid of dimensions m * n where you can only
    move right and down, how many ways can you get to the bottom right?

*/

#include <iostream>

#include <map>
#include <string>
#include <vector>

namespace GridTraveller
{
    using Coord = std::pair<int, int>;
    using MemoTable = std::map<Coord, long long>;
    using Grid = std::vector<std::vector<long long>>;

    // Recursion

    long long grid_recursion(int m, int n)
    {
        if (m <= 1 || n <= 1)
            return 1;

        // Return # of paths after moving down + paths after moving right
        return grid_recursion(m - 1, n) + grid_recursion(m, n - 1);
    }

    // DP (memoization)

    long long _grid_memo_aux(int m, int n, MemoTable &memo)
    {
        if (m <= 1 || n <= 1)
            return 1;

        Coord coord = Coord(m, n);

        if (memo.count(coord))
            return memo[coord];

        Coord down = Coord(m - 1, n);
        Coord right = Coord(m, n - 1);

        memo.insert(std::make_pair(down, _grid_memo_aux(down.first, down.second, memo)));
        memo.insert(std::make_pair(right, _grid_memo_aux(right.first, right.second, memo)));

        return memo[down] + memo[right];
    }

    long long can_memo(int m, int n)
    {
        MemoTable memo;

        return _grid_memo_aux(m, n, memo);
    }

    // DP (tabulation)

    long long can_tab(int m, int n)
    {
        if (m == 1 || n == 1)
            return 1;

        // Create m * n grid filled with ones (bottom and right have only 1 path)
        Grid grid(m, std::vector<long long>(n, 1));

        // Build from bottom right corner with number of paths to end
        for (int i = m - 2; i >= 0; i--)
        {
            for (int j = n - 2; j >= 0; j--)
            {
                grid[i][j] = grid[i + 1][j] + grid[i][j + 1];
            }
        }

        return grid[0][0];
    }

    // Tests

    void test_val(int m, int n, const std::string &fn_type)
    {
        long long output = 0;

        if (fn_type == "recursion")
            output = grid_recursion(m, n);
        else if (fn_type == "memo")
            output = can_memo(m, n);
        else if (fn_type == "tab")
            output = can_tab(m, n);

        std::cout << fn_type << ": " << m << "*" << n << " --> " << output << std::endl;
    }

    void test_recursion()
    {
        std::string fn_type = "recursion";

        test_val(1, 1, fn_type); // 1
        test_val(2, 2, fn_type); // 3
        test_val(3, 2, fn_type); // 3
        test_val(3, 3, fn_type); // 6
    }

    void test_memo()
    {
        std::string fn_type = "memo";

        test_val(1, 1, fn_type); // 1
        test_val(2, 2, fn_type); // 3
        test_val(3, 2, fn_type); // 3
        test_val(3, 3, fn_type); // 6

        test_val(18, 18, fn_type); // 2333606220
    }

    void test_tab()
    {
        std::string fn_type = "tab";

        test_val(1, 1, fn_type); // 1
        test_val(2, 2, fn_type); // 3
        test_val(3, 2, fn_type); // 3
        test_val(3, 3, fn_type); // 6

        test_val(18, 18, fn_type); // 2333606220
    }

    int main(void)
    {
        test_recursion();
        std::cout << std::endl;
        test_memo();
        std::cout << std::endl;
        test_tab();

        return 0;
    }
}
