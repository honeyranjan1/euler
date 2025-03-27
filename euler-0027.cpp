// ////////////////////////////////////////////////////////
// # Title
// Quadratic primes
//
// # URL
// https://projecteuler.net/problem=27
// http://euler.stephan-brumme.com/27/
//
// # Problem
// Euler discovered the remarkable quadratic formula: `n^2+n+41`
//
// It turns out that the formula will produce 40 primes for the consecutive integer values `0<=n<=39`.
// However, when `n=40`, `40^2+40+41=40(40+1)+41` is divisible by 41, and certainly when `n=41`, `41^2+41+41` is clearly divisible by 41.
//
// The incredible formula `n^2-79n+1601` was discovered, which produces 80 primes for the consecutive values `0<=n<=79`.
// The product of the coefficients, `-79` and `1601`, is `-126479`.
//
// Considering quadratics of the form:
// `n^2 + a * n + b`, where `|a|<1000` and `|b|<=1000` where `|n|` is the modulus/absolute value of `n` e.g. `|11|=11` and `|-4|=4`
//
// Find the product of the coefficients, `a` and `b`, for the quadratic expression that produces the maximum number of primes for consecutive values of `n`, starting with `n=0`.
//
// # Solved by
// Stephan Brumme
// February 2017
//
// # Algorithm
// Nothing fancy: ''isPrime'' determines whether its parameter is a prime number or not.
// And then two nested loops check every combination of ''a'' and ''b''.
//
// # Note
// ''isPrime'' can be optimized in various ways - but the basic algorithm is fast enough for the problem.

#include <iostream>

// Function to check if a number is prime
bool isPrime(int x)
{
    if (x <= 1) return false;
    for (int factor = 2; factor * factor <= x; factor++)
        if (x % factor == 0) return false;
    return true;
}

int main()
{
    int limit;
    std::cin >> limit;

    // Ensure limit is positive
    if (limit < 0) limit = -limit;

    int bestA = 0, bestB = 0;
    int maxConsecutivePrimes = 0;

    // Iterate over coefficients a and b
    for (int a = -limit; a <= limit; a++) {
        for (int b = 2; b <= limit; b++) { // Only check positive primes for b
            if (!isPrime(b)) continue; // Skip non-prime values of b

            int length = 0;

            // Count consecutive primes
            while (isPrime(length * length + a * length + b)) {
                length++;
            }

            // Update best coefficients if a longer sequence is found
            if (length > maxConsecutivePrimes) {
                maxConsecutivePrimes = length;
                bestA = a;
                bestB = b;
            }
        }
    }

    // Print best coefficients
    std::cout << bestA << " " << bestB << std::endl;

    return 0;
}

