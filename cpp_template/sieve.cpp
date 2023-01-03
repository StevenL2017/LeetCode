#include <set>
#include <algorithm>

using namespace std;

const int MAXN = 2e7 + 3;

int primes[MAXN]; // list of primes
int is_prime[MAXN]; // if it is prime
int mn_prime[MAXN]; // min prime factor
int nxt_prime[MAXN]; // next prime factor, can be used to iterate all prime factors of positive integers
int cnt_prime[MAXN]; // count of different prime factors
int mx_divisor[MAXN]; // max factor

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
                    is_prime[j] = 0;
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
            mn_prime[i] = i; // mn_prime[i] = 1; // if consider 1 as min prime
            if (i > 10000) continue;
            for (int j = i * i; j <= n; j += i) {
                mn_prime[j] = min(mn_prime[j], i);
            }
        }
    }
}

void eratosthenes_nxt(int n) {
    for (int i = 2; i < n; i++) {
        if (nxt_prime[i] == 0) {
            nxt_prime[i] = i;
            if (i > 10000) continue;
            for (int j = i * i; j < n; j += i) {
                if (nxt_prime[j] == 0) {
                    nxt_prime[j] = i;
                }
            }
        }
    }
}

int count_prime_factors(int x) {
    int ans = 1, y = mn_prime[x];
    while (y != 1) {
        x /= y;
        y = mn_prime[x];
        ans++;
    }
    return ans;
}

void count_different_prime_factors(int x) {
    for (int i = 2; i < x; i++) {
        int j = i / mn_prime[i];
        cnt_prime[i] = cnt_prime[j] + (mn_prime[j] != mn_prime[i]);
    }
}

set<int> get_prime_factors(int x) {
    set<int> ans;
    while (x > 1) {
        auto y = mn_prime[x]; // auto y = nxt_prime[x];
        x /= y;
        ans.insert(y);
    }
    return ans;
}

void eratosthenes_mx(int n) {
    mx_divisor[0] = n + 1;
    mx_divisor[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (mx_divisor[i]) continue;
        for (int j = i; j <= n; j += i) {
            if (mx_divisor[j]) continue;
            mx_divisor[j] = j / i;
        }
    }
}