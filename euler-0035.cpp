// ////////////////////////////////////////////////////////
// # Title
// Circular primes
//
// # URL
// https://projecteuler.net/problem=35
// http://euler.stephan-brumme.com/35/
//
// # Problem
// The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.
//
// There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
//
// How many circular primes are there below one million?
//
// # Solved by
// Stephan Brumme
// February 2017
//
// # Algorithm
// First, a a standard prime sieve finds all prime numbers up to our limit (1000000 by default) and keeps them in a ''std::set''.
//
// Then each prime ''x'' in ''std::set'' is rotated by one digit to the right:
// 1. get the right-most digit:
// ''auto digit = rotated % 10;''
// 2. move all digits by one digit to the right ("erasing" the right-most digit):
// ''rotated /= 10;''
// 3. prepend the right-most digit:
// '' rotated += digit * shift;''
// 4. check whether rotated is part of our ''std::set'', too
// 5. if ''rotated'' is equal to our initial value ''x'' then we checked all rotations
//
// The only point of interest is ''shift'' which is a power of 10 such that `10^a = shift <= x <= 10^{a+1}`.
// E.g., if `x = 3456` then `shift = 1000`.
//
// # Note
//
// There are a few options to speed up the code:
// 1. All prime numbers are odd (except for 2): if ''x != 2'' and any digit is even then this prime can't be circular.
// 2. We can simplify point 1 by noting that all single-digit primes are circular.
//
// # Hackerrank
// We have to find the sum of all such prime numbers, not their count.

#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <string>
#include <algorithm> // Include this header for std::rotate

// Function to generate all primes up to n using Sieve of Eratosthenes
std::set<unsigned int> generatePrimes(unsigned int n) {
    std::vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (unsigned int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (unsigned int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    std::set<unsigned int> primes;
    for (unsigned int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.insert(i);
        }
    }
    return primes;
}

// Function to check if all rotations of a number are prime
bool isCircularPrime(unsigned int num, const std::set<unsigned int>& primes) {
    std::string s = std::to_string(num);
    unsigned int len = s.length();

    for (unsigned int i = 0; i < len; i++) {
        std::rotate(s.begin(), s.begin() + 1, s.end()); // Rotate the digits
        if (primes.find(std::stoi(s)) == primes.end()) {
            return false; // Rotation is not prime
        }
    }
    return true;
}

int main() {
    // Read the upper limit
    unsigned int n;
    std::cin >> n;

    // Generate primes up to n
    std::set<unsigned int> primes = generatePrimes(n);

    unsigned int sum = 0;

    // Check for circular primes
    for (auto prime : primes) {
        if (isCircularPrime(prime, primes)) {
            sum += prime;
        }
    }

    // Output the sum of circular primes
    std::cout << sum << std::endl;

    return 0;
}
