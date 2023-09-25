/* bestSum

    Given a target sum (int) and a collection of other integers, return an array
    containing any combination of elements that add up to the sum. Return null
    if no solutions. The solution should have the minimum number of elements.

*/

#include <iostream>

#include <map>
#include <string>

#include <set>
#include <vector>

namespace BestSum
{
    using Addends = std::set<int>;

    class Solution
    {
    public:
        std::vector<int> vec;
        bool valid = false;

        Solution &validated()
        {
            this->valid = true;
            return *this;
        }
    };

    using MemoTable = std::map<int, Solution>;

    // Recursion

    Solution _best_recursion_aux(int n, const Addends &addends)
    {
        Solution short_sol;

        if (n < 0)
            return short_sol;
        if (n == 0)
            return short_sol.validated();

        for (auto add : addends)
        {
            int remainder = n - add;
            Solution rem_sol = _best_recursion_aux(remainder, addends);

            if (rem_sol.valid)
            {
                rem_sol.vec.push_back(add);

                if (!short_sol.valid || rem_sol.vec.size() < short_sol.vec.size())
                    short_sol = rem_sol;
            }
        }

        return short_sol;
    }

    std::vector<int> best_recursion(int n, const Addends &addends)
    {
        // Recursively find best solution
        Solution solution = _best_recursion_aux(n, addends);

        return solution.vec;
    }

    // DP (memoization)

    Solution _best_memo_aux(int n, const Addends &addends, MemoTable &memo)
    {
        if (memo.count(n))
            return memo[n];
        if (n < 0)
            return Solution();
        if (n == 0)
            return Solution().validated();

        Solution short_sol;

        for (auto add : addends)
        {
            int remainder = n - add;
            Solution rem_sol = _best_memo_aux(remainder, addends, memo);

            if (rem_sol.valid)
            {
                rem_sol.vec.push_back(add);

                if (!short_sol.valid || rem_sol.vec.size() < short_sol.vec.size())
                    short_sol = rem_sol;
            }
        }

        memo.insert(std::make_pair(n, short_sol));
        return short_sol;
    }

    std::vector<int> best_memo(int n, const Addends &addends)
    {
        MemoTable memo;

        // Recursively find best solution
        Solution solution = _best_memo_aux(n, addends, memo);

        return solution.vec;
    }

    // DP (tabulation)

    std::vector<int> best_tab(int n, const Addends &addends)
    {
        if (n == 0)
            return std::vector<int>();

        std::vector<Solution> stacks(n + 1, Solution());
        stacks[0].valid = true;

        for (int i = 0; i <= n; i++)
        {
            if (stacks[i].valid)
            {
                // Look forward to indices achievable from current w/ addends
                for (const &add : addends)
                {
                    int new_sum = i + add;

                    if (new_sum <= n)
                    {
                        // Mark new sum as valid and save list
                        stacks[new_sum].valid = true;
                        std::vector<int> &new_vec = stacks[new_sum].vec;

                        if (new_vec.empty() || stacks[i].vec.size() + 1 < new_vec.size())
                        {
                            new_vec = stacks[i].vec;
                            new_vec.push_back(add);
                        }
                    }
                }
            }
        }

        return stacks[n].vec;
    }

    // Tests

    void test_val(int n, const Addends &addends, const std::string &fn_type)
    {
        std::vector<int> output;

        if (fn_type == "recursion")
            output = best_recursion(n, addends);
        else if (fn_type == "memo")
            output = best_memo(n, addends);
        else if (fn_type == "tab")
            output = best_tab(n, addends);

        // Create string from set of addends
        std::string setStr;
        for (const int add : addends)
        {
            setStr += std::to_string(add);
            setStr += ",";
        }

        // Create string from results
        std::string solStr;
        for (const int res : output)
        {
            solStr += std::to_string(res);
            solStr += ",";
        }

        std::cout << fn_type << ": " << n << ", [" << setStr << "] --> [" << solStr << "]" << std::endl;
    }

    void test_recursion()
    {
        std::string fn_type = "recursion";

        test_val(7, {2, 3}, fn_type);
        test_val(7, {5, 3, 4, 7}, fn_type);
        test_val(7, {2, 4}, fn_type);
        test_val(8, {2, 3, 5}, fn_type);
        test_val(30, {12, 4, 2}, fn_type);
    }

    void test_memo()
    {
        std::string fn_type = "memo";

        test_val(7, {2, 3}, fn_type);
        test_val(7, {5, 3, 4, 7}, fn_type);
        test_val(7, {2, 4}, fn_type);
        test_val(8, {2, 3, 5}, fn_type);
        test_val(30, {12, 4, 2}, fn_type);

        test_val(300, {7, 14}, fn_type);
    }

    void test_tab()
    {
        std::string fn_type = "tab";

        test_val(7, {2, 3}, fn_type);
        test_val(7, {5, 3, 4, 7}, fn_type);
        test_val(7, {2, 4}, fn_type);
        test_val(8, {2, 3, 5}, fn_type);
        test_val(30, {12, 4, 2}, fn_type);

        test_val(300, {7, 14}, fn_type);
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
