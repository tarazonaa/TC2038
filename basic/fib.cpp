#include <iostream>

using namespace std;

int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}

int fibSuma(int n) {
    int F[n];
    F[0] = 0;
    F[1] = 1;
    for (int i = 2; i <= n; i++) {
        F[i] = F[i-1] + F[i-2];
    }
    return F[n];
}

int main() {
    int fib1 = fib(3);
    int fib2 = fibSuma(0);
    std::cout << fib1 << std::endl;
    std::cout << fib2 << std::endl;
    return 0;
}
