/* canSum

    Return bool indicating if possible to generate a given sum using numbers
    from a given array. Elements are nonnegative and can be used many times.

*/

#include <iostream>

#include <map>
#include <string>

#include <set>

using Addends = std::set<int>;
using MemoTable = std::map<int, int>;
using MemoPair = std::pair<int, int>;

// Recursion

bool can_recursion(int n, const Addends addends) {
    return 0;
}

// DP (memoization)

bool can_memo(int n, const Addends addends) {
    return 0;
}

// Tests

void test_val(int n, const Addends addends, const std::string& fn_type){
    bool output = false;

    if (fn_type == "recursion")
        output = can_recursion(n, addends);
    else if (fn_type == "memo")
        output = can_memo(n, addends);

    // Create string from set of addends
    std::string setStr;
    for (const int add : addends) {
        setStr += add;
        setStr += ",";
    }

    std::cout << fn_type <<  ": " << n << ",[" << setStr << "] --> " << output << std::endl;

}

void test_recursion() {
    std::string fn_type = "recursion";
}

void test_memo() {
    std::string fn_type = "memo";
}

int main(void) {
    test_recursion();

    std::cout << std::endl;

    test_memo();

    return 0;
}
