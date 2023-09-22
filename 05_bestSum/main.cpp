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

using Addends = std::set<int>;
using MemoSet = std::set<int>;

class Solution
{
public:
    std::vector<int> stack;
    std::vector<int> best;
    bool found = false;
};

// Recursion

void _best_recursion_aux(int n, const Addends &addends, int running_total, Solution &solution)
{
    for (auto add : addends)
    {
        int new_total = running_total + add;

        solution.stack.push_back(add);

        if (new_total == n)
        {
            // Replace if first or better
            if (solution.best.empty() || solution.stack.size() < solution.best.size())
            {
                solution.best = solution.stack;
                solution.found = true;
            }
        }
        else if (new_total < n)
            _best_recursion_aux(n, addends, new_total, solution);

        solution.stack.pop_back();
    }
}

std::vector<int> best_recursion(int n, const Addends &addends)
{
    Solution solution;

    if (n == 0)
        return solution.best;

    // Recursively find best solution
    _best_recursion_aux(n, addends, 0, solution);

    if (solution.found)
        return solution.best;

    solution.best.clear();
    return solution.best;
}

// DP (memoization)

void _best_memo_aux(int n, const Addends &addends, int running_total, Solution &solution, MemoSet &memo)
{
    for (auto add : addends)
    {
        int new_total = running_total + add;

        if (memo.count(new_total))
            continue;

        memo.insert(running_total);
        solution.stack.push_back(add);

        if (new_total == n)
        {
            // Replace if first or better
            if (solution.best.empty() || solution.stack.size() < solution.best.size())
            {
                solution.best = solution.stack;
                solution.found = true;
            }
        }
        else if (new_total < n)
            _best_memo_aux(n, addends, new_total, solution, memo);

        solution.stack.pop_back();
    }
}

std::vector<int> best_memo(int n, const Addends &addends)
{
    Solution solution;

    if (n == 0)
        return solution.best;

    MemoSet memo;

    _best_memo_aux(n, addends, 0, solution, memo);

    if (solution.found)
        return solution.best;

    solution.best.clear();
    return solution.best;
}

// Tests

void test_val(int n, const Addends &addends, const std::string &fn_type)
{
    std::vector<int> output;

    if (fn_type == "recursion")
        output = best_recursion(n, addends);
    else if (fn_type == "memo")
        output = best_memo(n, addends);

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

int main(void)
{
    test_recursion();

    std::cout << std::endl;

    test_memo();

    return 0;
}
