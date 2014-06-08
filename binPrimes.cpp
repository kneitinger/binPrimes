// binPrimes (stylized binary-prime-number-generator)/
// Kyle tattoo replicator
// Copyright (C) 2014 Kyle J. Kneitinger

#include <iostream>
#include <cmath>

const int MAXLEVEL = 16;
const int BITS = 6;

void toBin(int n, bool* bit);
bool isPrime(int n);

using namespace std;

int main() {
    // Create 2D array of booleans to hold binary values of primes
    bool chart[MAXLEVEL][BITS];
    // Initialize the array
    for(int i =0; i<MAXLEVEL;i++) {
        for (int j = 0; j<BITS; j++) {
            chart[i][j] = 0;
        }
    }

    // Populate the array with the binary values of the first MAXLEVEL primes
    for (int n=2,p=0; p < MAXLEVEL; n++) {
        if(isPrime(n)){
            toBin( n, &chart[p][BITS-1] );
            p++;

        }
    }

    for (int i = 0; i < MAXLEVEL; i++) {
        for (int j = 0, k = 0;  j < 2; k=(k+1)%BITS) {
            if (chart[i][k] == 1) {
                if (j == 0)
                    cout << (chart[i-1][k] == 0 ? "╔═╗" : "║ ║");
                else
                    cout << (chart[i+1][k] == 0 ? "╚═╝" : "║ ║");
            } else {
                cout << "   ";
            }
            if (k==(BITS-1)) {
                j++;
                cout << endl;
            }
        }
    }
}

void toBin(int n, bool* bit) {
    int remain;

    if(n <= 1) {
        *bit = n;
        return;
    }

    remain = n%2;
    toBin(n >> 1, (bit-1));
    *bit = remain;
}

bool isPrime(int n) {
    if (n == 2)
        return true;

    if (n%2 == 0)
        return false;

    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0)    // Test odd divisors from 3 to sqrt(n)
            return false;   // If no remainder, then composite.

    }
    return true;        // Otherwise prime
}
