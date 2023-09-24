/* countConstruct

    Given a target word and some components, return the number of different
    ways the target can be constructed. Elements may be reused.

*/

#include <iostream>

#include <map>
#include <string>
#include <vector>
#include <set>

using String = std::string;
using Components = std::set<std::string>;
using MemoTable = std::map<std::string, int>;

bool _is_substring(const String &str1, const String &str2);

// Recursion

void _cc_recursion_aux(const String &target, const Components &comps, String &running_str, int &answers)
{
    for (const String &comp : comps)
    {
        String new_str = running_str + comp;

        if (new_str == target)
            answers++;
        else if (_is_substring(new_str, target))
            _cc_recursion_aux(target, comps, new_str, answers);
    }
}

int cc_recursion(const String &target, const Components &comps)
{
    if (target.empty())
        return 1;

    int answers = 0;
    String running_str;

    _cc_recursion_aux(target, comps, running_str, answers);

    return answers;
}

// DP (memoization)

int _cc_memo_aux(const String &target, const Components &comps, String &running_str, MemoTable &memo)
{
    int sub_answers = 0;

    for (const String &comp : comps)
    {
        String new_str = running_str + comp;

        if (new_str == target)
            sub_answers++;
        else if (_is_substring(new_str, target))
        {
            if (memo.count(new_str))
                sub_answers += memo[new_str];
            else
                sub_answers += _cc_memo_aux(target, comps, new_str, memo);
        }
    }

    memo.insert(std::make_pair(running_str, sub_answers));
    return sub_answers;
}

int cc_memo(const String &target, const Components &comps)
{
    if (target.empty())
        return 1;

    String running_str;
    MemoTable memo;

    int answers = _cc_memo_aux(target, comps, running_str, memo);

    return answers;
}

// DP (tabulation)

int cc_tab(const String &target, const Components &comps)
{
    if (target.empty())
        return 1;

    int n = target.size();
    std::vector<int> num_builds(n + 1, 0);
    num_builds[0] = 1;

    for (int i = 0; i < n; ++i)
    {
        if (num_builds[i] > 0)
        {
            for (auto &comp : comps)
            {
                String new_str = target.substr(0, i);
                new_str.append(comp);

                if (new_str == target.substr(0, new_str.size()))
                    num_builds[new_str.size()] += num_builds[i];
            }
        }
    }

    return num_builds[n];
}

// Helpers

bool _is_substring(const String &str1, const String &str2)
{
    return str1.size() < str2.size() && str1 == str2.substr(0, str1.size());
}

// Tests

void test_val(const String &target, const Components &comps, const std::string &fn_type)
{
    int output = false;

    if (fn_type == "recursion")
        output = cc_recursion(target, comps);
    else if (fn_type == "memo")
        output = cc_memo(target, comps);
    else if (fn_type == "tab")
        output = cc_tab(target, comps);

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

    test_val("purple", {"purp", "p", "ur", "le", "purpl"}, fn_type); // 2
    test_val("abcdef", {"ab", "abc", "cd", "def", "abcd"}, fn_type); // 1
    test_val("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}, fn_type); // 0
    test_val("", {"cat", "dog", "mouse"}, fn_type); // 1
    test_val("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, fn_type); // 4
}

void test_memo()
{
    std::string fn_type = "memo";

    test_val("purple", {"purp", "p", "ur", "le", "purpl"}, fn_type); // 2
    test_val("abcdef", {"ab", "abc", "cd", "def", "abcd"}, fn_type); // 1
    test_val("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}, fn_type); // 0
    test_val("", {"cat", "dog", "mouse"}, fn_type); // 1
    test_val("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, fn_type); // 4

    test_val("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
             {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}, fn_type); // 0
}

void test_tab()
{
    std::string fn_type = "tab";

    test_val("purple", {"purp", "p", "ur", "le", "purpl"}, fn_type); // 2
    test_val("abcdef", {"ab", "abc", "cd", "def", "abcd"}, fn_type); // 1
    test_val("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}, fn_type); // 0
    test_val("", {"cat", "dog", "mouse"}, fn_type); // 1
    test_val("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, fn_type); // 4

    test_val("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
             {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}, fn_type); // 0
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
