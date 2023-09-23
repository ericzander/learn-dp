/* allConstruct

    Given a target word and some components, return a 2D array containing
    all of the ways a target can be constructed by concatenating elements
    of the components. Elements may be reused.

    ie. "purple", [purp, p, ur, le, purple] ->

        [
            [purp, le],
            [p, ur, p, le]
        ]

*/

#include <iostream>

#include <map>
#include <string>
#include <vector>
#include <set>

// Setup

using String = std::string;
using Components = std::set<std::string>;
using StrStack = std::vector<std::string>;
using StrArray = std::vector<std::vector<std::string>>; // 2D array of strings

class Solution
{
public:
    StrArray arr;
    std::vector<String> stack;

    void add(const Solution &rhs)
    {
        for (auto &sol : rhs.arr)
            this->arr.push_back(sol);
    }

    friend std::ostream &operator<<(std::ostream &os, const Solution &m);
};

using MemoTable = std::map<std::string, Solution>;

bool _is_substring(const String &str1, const String &str2)
{
    return str1.size() < str2.size() && str1 == str2.substr(0, str1.size());
}

std::ostream &operator<<(std::ostream &os, const Solution &solution)
{
    // If no solution or empty target, just print brackets
    if (!solution.arr.size())
        return os << "[]";

    os << "[" << std::endl;

    for (const auto &answer : solution.arr)
    {
        os << "    [";
        for (const String &comp : answer)
        {
            os << comp << ",";
        }
        os << "]," << std::endl;
    }

    os << "]";

    return os;
}

// Recursion

Solution _ac_recursion_aux(const String &target, const Components &comps, StrStack &stack)
{
    if (target.empty())
    {
        Solution sol;
        sol.arr.push_back(stack);
        return sol;
    }

    Solution solution;

    for (auto &comp : comps)
    {
        size_t csize = comp.size();

        // If valid prefix
        if (csize <= target.size() && comp == target.substr(0, csize))
        {
            // Remove prefix
            String remainder = target;
            remainder.erase(0, csize);

            stack.push_back(comp);
            solution.add(_ac_recursion_aux(remainder, comps, stack));
            stack.pop_back();
        }
    }

    return solution;
}

Solution ac_recursion(const String &target, const Components &comps)
{
    StrStack stack;

    Solution solution = _ac_recursion_aux(target, comps, stack);

    return solution;
}

// DP (memoization)

Solution _ac_memo_aux(const String &target, const Components &comps, StrStack &stack, MemoTable &memo)
{
    if (target.empty())
    {
        Solution sol;
        sol.arr.push_back(stack);
        return sol;
    }
    if (memo.count(target))
        return memo[target];

    Solution solution;

    for (auto &comp : comps)
    {
        size_t csize = comp.size();

        // If valid prefix
        if (csize <= target.size() && comp == target.substr(0, csize))
        {
            // Remove prefix
            String remainder = target;
            remainder.erase(0, csize);

            stack.push_back(comp);
            solution.add(_ac_memo_aux(remainder, comps, stack, memo));
            stack.pop_back();
        }
    }

    memo[target] = solution;
    return solution;
}

Solution ac_memo(const String &target, const Components &comps)
{
    StrStack stack;
    MemoTable memo;

    Solution solution = _ac_memo_aux(target, comps, stack, memo);

    return solution;
}

// Tests

void test_val(const String &target, const Components &comps, const std::string &fn_type)
{
    Solution output;

    if (fn_type == "recursion")
        output = ac_recursion(target, comps);
    else if (fn_type == "memo")
        output = ac_memo(target, comps);

    // Create string from set of addends
    std::string setStr;
    for (const String &comp : comps)
    {
        setStr += comp;
        setStr += ",";
    }

    std::cout << fn_type << ": " << target << ", [" << setStr << "] --> " << output << std::endl;
}

void test_recursion()
{
    std::string fn_type = "recursion";

    test_val("purple", {"purp", "p", "ur", "le", "purpl"}, fn_type);                  // 2
    test_val("abcdef", {"ab", "abc", "cd", "def", "abcd"}, fn_type);                  // 1
    test_val("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}, fn_type);   // 0
    test_val("", {"cat", "dog", "mouse"}, fn_type);                                   // 1
    test_val("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, fn_type); // 4
}

void test_memo()
{
    std::string fn_type = "memo";

    test_val("purple", {"purp", "p", "ur", "le", "purpl"}, fn_type);                  // 2
    test_val("abcdef", {"ab", "abc", "cd", "def", "abcd"}, fn_type);                  // 1
    test_val("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}, fn_type);   // 0
    test_val("", {"cat", "dog", "mouse"}, fn_type);                                   // 1
    test_val("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, fn_type); // 4

    test_val("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
             {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}, fn_type); // 0
}

int main(void)
{
    test_recursion();

    std::cout << std::endl;

    test_memo();

    return 0;
}
