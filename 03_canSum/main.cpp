/* canSum

    Return bool indicating if possible to generate a given sum using numbers
    from a given array. Elements are nonnegative and can be used many times.

*/

#include <iostream>

#include <map>
#include <string>
#include <vector>
#include <set>

using Addends = std::set<int>;
using MemoSet = std::set<int>;

// Recursion

bool _can_recursion_aux(int n, const Addends &addends, int running_total)
{
    for (auto add : addends)
    {
        int new_total = running_total + add;

        if (new_total == n)
            return true;
        else if (new_total < n)
        {
            if (_can_recursion_aux(n, addends, new_total))
                return true;
        }
    }

    return false;
}

bool can_recursion(int n, const Addends &addends)
{
    if (n == 0)
        return true;

    return _can_recursion_aux(n, addends, 0);
}

// DP (memoization)

bool _can_memo_aux(int n, const Addends &addends, int running_total, MemoSet &memo)
{
    for (auto add : addends)
    {
        int new_total = running_total + add;

        if (new_total == n)
            return true;
        else if (new_total < n && !memo.count(new_total))
        {
            if (_can_memo_aux(n, addends, new_total, memo))
                return true;
        }
    }

    memo.insert(running_total);
    return false;
}

bool can_memo(int n, const Addends &addends)
{
    if (n == 0)
        return true;

    MemoSet memo;

    return _can_memo_aux(n, addends, 0, memo);
}

// DP (tabulation)

bool can_tab(int n, const Addends &addends)
{
    std::vector<bool> can_build(n + 1, false);
    can_build[0] = true;

    for (int i = 0; i <= n; i++)
    {
        if (can_build[i])
        {
            // Look forward to indices achievable from current w/ addends
            for (const &add : addends)
            {
                int new_sum = i + add;

                if (new_sum == n)
                    return true;
                else if (new_sum < n)
                    can_build[new_sum] = true;
            }
        }
    }

    return false;
}

// Tests

void test_val(int n, const Addends &addends, const std::string &fn_type)
{
    bool output = false;

    if (fn_type == "recursion")
        output = can_recursion(n, addends);
    else if (fn_type == "memo")
        output = can_memo(n, addends);
    else if (fn_type == "tab")
        output = can_tab(n, addends);

    // Create string from set of addends
    std::string setStr;
    for (const int add : addends)
    {
        setStr += std::to_string(add);
        setStr += ",";
    }

    std::cout << fn_type << ": " << n << ", [" << setStr << "] --> " << output << std::endl;
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
