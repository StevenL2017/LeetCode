#include <algorithm>

using namespace std;

const int MAXN = 2e7 + 3;

int primes[MAXN]; // list of primes
int is_prime[MAXN]; // if it is prime
int mn_prime[MAXN]; // min prime factor

int eratosthenes(int n) {
    int p = 0; // count of primes for less or equal than n
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i <= n; i++) {
        is_prime[i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes[p++] = i;
            if ((long long)i * i <= n) {
                for (int j = i * i; j <= n; j += i) {
                    is_prime[i] = 0;
                }
            }
        }
    }
    return p;
}

void eratosthenes_mn(int n) {
    mn_prime[0] = mn_prime[1] = 1;
    for (int i = 2; i <= n; i++) {
        mn_prime[i] = n + 1;
    }
    for (int i = 2; i <= n; i++) {
        if (mn_prime[i] == n + 1) {
            mn_prime[i] = 1;
            for (int j = i + i; j <= n; j += i) {
                mn_prime[j] = min(mn_prime[j], i);
            }
        }
    }
}

long long count_prime_factors(int x) {
    long long ans = 1, y = mn_prime[x];
    while (y != 1) {
        x /= y;
        y = mn_prime[x];
        ans++;
    }
    return ans;
}