// ////////////////////////////////////////////////////////
// # Title
// Pandigital multiples
//
// # URL
// https://projecteuler.net/problem=38
// http://euler.stephan-brumme.com/38/
//
// # Problem
// Take the number 192 and multiply it by each of 1, 2, and 3:
//
// `192 * 1 = 192`
// `192 * 2 = 384`
// `192 * 3 = 576`
//
// By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)
// The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).
//
// What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2, ... , n) where n > 1?
//
// # Solved by
// Stephan Brumme
// February 2017
//
// # Algorithm
// A bitmask tracks whether a number is pandigital (or not): if the n-th bit of ''bitsUsed'' is 1 then n is a digit of ''pandigital''.
// A truly pandigital number has a bitmask of ''bitsAll = (1 << 9) | (1 << 8) | ... | (1 << 2) | (1 << 1)''.
// According to the problem statement, a digit must not be zero. That means the lowest bit is always 0:
// `bitsAll_9=1022` (and `bitsAll_8=510` for alternate Hackerrank input).
//
// My program process all numbers ''i'' from 2 to ''maxFactor'' and multiplies them with 1, 2, ... until the concatenated result's ''bitsUsed == bitsAll''.
//
// Each ''product = i * multiplier'' (where ''multiplier = 1, 2, ...'') is split into its digits and each digit added to the bitmask ''bitsUsed''.
// When a collision occurs (that digit was already used before), then ''bitsUsed'' is set to an invalid value and the next number ''i'' can be processed.
//
// # Note
// ''maxFactor'' cannot exceed 10000 because then ''i*1''+''i*2'' will have more than 9 digits.
// A few things are probably much easier when converting all numbers to ''std::string'' - at the cost of speed.
//
// # Hackerrank
// The result may have either 8 or 9 digits and there is an upper limit for the start value.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool isPandigital(const std::string& s, int K) {
    if (s.length() != K) return false;
    std::vector<bool> seen(K + 1, false); // index 0 to K

    for (char c : s) {
        int d = c - '0';
        if (d == 0 || d > K || seen[d]) return false;
        seen[d] = true;
    }
    return true;
}

int main() {
    int N, K;
    std::cin >> N >> K;

    std::vector<int> results;

    for (int M = 2; M < N; ++M) {
        std::string concat = "";
        int multiplier = 1;

        while ((int)concat.length() < K) {
            concat += std::to_string(M * multiplier);
            ++multiplier;
        }

        if (isPandigital(concat, K)) {
            results.push_back(M);
        }
    }

    for (int r : results) {
        std::cout << r << std::endl;
    }

    return 0;
}

