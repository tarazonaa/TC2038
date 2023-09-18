#include <iostream>
#include <map>
#include <string>

using namespace std;

int fib(int n, map<int, int> &memo) {
  if (memo.find(n) != memo.end()) {
    return memo[n];
  }
  memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
  return memo[n];
}

int main() {
  map<int, int> memo;
  memo[0] = 0;
  memo[1] = 1;
  fib(30, memo);
  cout << memo[30] << endl;
  return 0;
}
