// binPrimes (stylized binary-prime-number-generator)/
// Kyle tattoo replicator
// Copyright (C) 2014 Kyle J. Kneitinger

#include <iostream>
#include <cmath>
#include <cstdlib>

void toBin(int n, bool* bit);
bool isPrime(int n);
void calcNprimes(int n, int* primes);
void buildArr(int rows, int columns);

bool ** binChart;
using namespace std;

int main(int argc, char *argv[]) {

	int MAXLEVEL = 16;
	if (argc == 2)
		MAXLEVEL = atoi(argv[1]);

    int* primes = new int[MAXLEVEL];
    calcNprimes(MAXLEVEL, primes);

    // Calculate how many bits wide the largest number is:
    int BITS = 1;
    for (int test = 2; test < primes[MAXLEVEL-1]; BITS++) {
        test*=2;
    }

    // Create 2D array of booleans to hold binary values of primes

    // Initialize the array
    buildArr(MAXLEVEL,BITS);
	for (int i = 0; i < MAXLEVEL; i++) {
		toBin(primes[i], &binChart[i][BITS-1]);
	}


    for (int i = 0; i < MAXLEVEL; i++) {
        for (int j = 0, k = 0;  j < 2; k=(k+1)%BITS) {
            if (binChart[i][k] == 1) {
                if (j == 0)
                    cout << (i == 0 || binChart[i-1][k] == 0 ? "╔═╗" : "║ ║");
                else
                    cout << (i == MAXLEVEL || binChart[i+1][k] == 0 ? "╚═╝" : "║ ║");
            } else {
                cout << "   ";
            }
            if (k==(BITS-1)) {
                j++;
                cout << endl;
            }
        }
    }

    delete [] primes;
    for (int i = 0; i < MAXLEVEL; i++) {
        delete binChart[i];
    }
    delete [] binChart;
}

void calcNprimes(int level, int* primes) {
    for (int n=2,p=0; p < level; n++) {
        if(isPrime(n)){
            primes[p] = n;
            p++;
        }
    }
}

void buildArr(int rows, int columns) {
    binChart = new bool*[rows+1];
    for(int i =0; i<=rows;i++) {
        binChart[i] = new bool[columns];
        for (int j =0; j<columns; j++) {
            binChart[i][j] = 0;
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
