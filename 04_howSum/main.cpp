/* howSum

    Given a target sum (int) and a collection of other integers, return an array
    containing any combination of elements that add up to the sum. Return null
    if no solutions. Only one possible combination needs to be returned.

*/

#include <iostream>

#include <map>
#include <string>

#include <set>
#include <vector>

using Addends = std::set<int>;
using Solution = std::vector<int>;
using MemoSet = std::set<int>;

// Recursion

bool _how_recursion_aux(int n, const Addends &addends, int running_total, Solution &solution)
{
    for (auto add : addends)
    {
        int new_total = running_total + add;
        bool solution_found = false;

        // Check recursively for solution
        if (new_total == n)
            solution_found = true;
        else if (new_total < n && _how_recursion_aux(n, addends, new_total, solution))
            solution_found = true;

        if (solution_found)
        {
            solution.push_back(add);
            return true;
        }
    }

    return false;
}

Solution how_recursion(int n, const Addends &addends)
{
    Solution solution;

    if (n == 0)
        return solution;

    if (_how_recursion_aux(n, addends, 0, solution))
        return solution;

    solution.clear();
    return solution;
}

// DP (memoization)

bool _how_memo_aux(int n, const Addends &addends, int running_total, Solution &solution, MemoSet &memo)
{
    for (auto add : addends)
    {
        int new_total = running_total + add;
        bool solution_found = false;

        // Check recursively for solution
        if (new_total == n)
            solution_found = true;
        else if (new_total < n && !memo.count(new_total))
        {
            if (_how_memo_aux(n, addends, new_total, solution, memo))
                solution_found = true;
        }

        if (solution_found)
        {
            solution.push_back(add);
            return true;
        }
    }

    memo.insert(running_total);
    return false;
}

Solution how_memo(int n, const Addends &addends)
{
    Solution solution;

    if (n == 0)
        return solution;

    MemoSet memo;

    if (_how_memo_aux(n, addends, 0, solution, memo))
        return solution;

    solution.clear();
    return solution;
}

// DP (tabulation)

Solution how_tab(int n, const Addends &addends)
{
    if (n == 0)
        return Solution();

    std::vector<std::pair<bool, Solution> > stacks(n + 1, std::make_pair(false, Solution()));
    stacks[0].first = true;

    for (int i = 0; i <= n; i++)
    {
        if (stacks[i].first)
        {
            // Look forward to indices achievable from current w/ addends
            for (const &add : addends)
            {
                int new_sum = i + add;

                if (new_sum <= n)
                {
                    // Mark new sum as valid and save list
                    stacks[new_sum].first = true;
                    stacks[new_sum].second = stacks[i].second;
                    stacks[new_sum].second.push_back(add);

                    if (new_sum == n)
                        return stacks[new_sum].second;
                }
            }
        }
    }

    return Solution();
}

// Tests

void test_val(int n, const Addends &addends, const std::string &fn_type)
{
    Solution output;

    if (fn_type == "recursion")
        output = how_recursion(n, addends);
    else if (fn_type == "memo")
        output = how_memo(n, addends);
    else if (fn_type == "tab")
        output = how_tab(n, addends);

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
}

void test_memo()
{
    std::string fn_type = "memo";

    test_val(7, {2, 3}, fn_type);
    test_val(7, {5, 3, 4, 7}, fn_type);
    test_val(7, {2, 4}, fn_type);
    test_val(8, {2, 3, 5}, fn_type);

    test_val(300, {7, 14}, fn_type);
}

void test_tab()
{
    std::string fn_type = "tab";

    test_val(7, {2, 3}, fn_type);
    test_val(7, {5, 3, 4, 7}, fn_type);
    test_val(7, {2, 4}, fn_type);
    test_val(8, {2, 3, 5}, fn_type);

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
