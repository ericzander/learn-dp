/* Fibonacci sequence */

#include <iostream>

#include <map>
#include <string>

using MemoTable = std::map<int, long long>;
using MemoPair = std::pair<int, long long>;

// Recursion

long long fib_recursion(int n) {
    if (n <= 2)
        return 1;
    
    return fib_recursion(n - 2) + fib_recursion(n - 1);
}


// DP (memoization)

long long _fib_memo_aux(int n, MemoTable& memo) {
    if (n <= 2)
        return 1;

    if (memo.count(n))
        return memo[n];

    int left = n - 2;
    int right = n - 1;

    // Calculate components and store in results in map
    memo.insert(MemoPair(left, _fib_memo_aux(left, memo)));
    memo.insert(MemoPair(right, _fib_memo_aux(right, memo)));
    
    return memo[left] + memo[right];
}

long long fib_memo(int n) {
    MemoTable memo;

    return _fib_memo_aux(n, memo);
}

// Driver

void test_val(int n, const std::string& fn_type){
    long long output = 0;

    if (fn_type == "recursion")
        output = fib_recursion(n);
    else if (fn_type == "memo")
        output = fib_memo(n);

    std::cout << fn_type <<  ": " << n << " --> " << output << std::endl;

}

void test_recursion() {
    std::string fn_type = "recursion";

    test_val(1, fn_type);
    test_val(2, fn_type);
    test_val(3, fn_type);
    test_val(7, fn_type);
    test_val(10, fn_type);
}

void test_memo() {
    std::string fn_type = "memo";
    
    test_val(10, fn_type);
    test_val(20, fn_type);
    test_val(30, fn_type);
    test_val(40, fn_type);
    test_val(50, fn_type);
}

int main(void) {
    test_recursion();

    std::cout << std::endl;

    test_memo();

    return 0;
}
