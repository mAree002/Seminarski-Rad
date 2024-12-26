#include <iostream>

using namespace std;

int EuclideanGCD(int a, int b);

int main() {
    int a = 1701, b = 3768;
    int gcd = EuclideanGCD(a, b);
    cout << "GCD(" << a << "," << b << ") = " << gcd << endl;
    return 0;
}

int EuclideanGCD(int a, int b) {
    if (b == 0) {
        return a; // Kada je drugi broj 0, prvi broj je GCD
    }
    return EuclideanGCD(b, a % b); // Rekurzivni poziv
}
