/* canConstruct

    Given a target word and some components, return whether the word can
    be constructed.

*/

#include <iostream>

#include <map>
#include <string>

#include <set>

using String = std::string;
using Components = std::set<std::string>;
using MemoSet = std::set<std::string>;

bool _is_substring(const String &str1, const String &str2);

// Recursion

bool _cc_recursion_aux(const String &target, const Components &comps, String &running_str)
{
    for (const String &comp : comps)
    {
        String new_str = running_str + comp;

        if (new_str == target)
            return true;
        else if (_is_substring(new_str, target))
        {
            if (_cc_recursion_aux(target, comps, new_str))
                return true;
        }
    }

    return false;
}

bool cc_recursion(const String &target, const Components &comps)
{
    if (target.empty())
        return true;

    String running_str;

    return _cc_recursion_aux(target, comps, running_str);
}

// DP (memoization)

bool _cc_memo_aux(const String &target, const Components &comps, String &running_str, MemoSet &memo)
{
    for (const String &comp : comps)
    {
        String new_str = running_str + comp;

        if (new_str == target)
            return true;
        else if (_is_substring(new_str, target) && !memo.count(new_str))
        {
            if (_cc_memo_aux(target, comps, new_str, memo))
                return true;
        }
    }

    memo.insert(running_str);
    return false;
}

bool cc_memo(const String &target, const Components &comps)
{
    if (target.empty())
        return true;

    String running_str;

    MemoSet memo;

    return _cc_memo_aux(target, comps, running_str, memo);
}

// Helpers

bool _is_substring(const String &str1, const String &str2)
{
    return str1.size() < str2.size() && str1 == str2.substr(0, str1.size());
}

// Tests

void test_val(const String &target, const Components &comps, const std::string &fn_type)
{
    bool output = false;

    if (fn_type == "recursion")
        output = cc_recursion(target, comps);
    else if (fn_type == "memo")
        output = cc_memo(target, comps);

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

    test_val("abcdef", {"ab", "abc", "cd", "def", "abcd"}, fn_type); // true
    test_val("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}, fn_type); // false
    test_val("", {"cat", "dog", "mouse"}, fn_type); // true
    test_val("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, fn_type); // true
}

void test_memo()
{
    std::string fn_type = "memo";

    test_val("abcdef", {"ab", "abc", "cd", "def", "abcd"}, fn_type); // true
    test_val("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}, fn_type); // false
    test_val("", {"cat", "dog", "mouse"}, fn_type); // true
    test_val("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}, fn_type); // true
    
    test_val("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", 
             {"e", "ee", "eee", "eeee", "eeeee", "eeeeee"}, fn_type); // false
}

int main(void)
{
    test_recursion();

    std::cout << std::endl;

    test_memo();

    return 0;
}
