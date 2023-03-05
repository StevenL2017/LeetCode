const int MOD = 998244353;
const int MAXN = 1e6 + 3;

int add(int x, int y) {
    x += y;
    while (x >= MOD) x -= MOD;
    while (x < 0) x += MOD;
    return x;
}

int sub(int x, int y) {
    return add(x, -y);
}

int mul(int x, int y) {
    return (x * 1ll * y) % MOD;
}

int binpow(int x, int y) {
    int z = 1;
    while (y) {
        if (y & 1) z = mul(z, x);
        x = mul(x, x);
        y >>= 1;
    }
    return z;
}

int inv(int x) {
    return binpow(x, MOD - 2);
}

int divide(int x, int y) {
    return mul(x, inv(y));
}

int factorial[MAXN];

void get_factorial() {
    factorial[0] = 1;
    for (int i = 1; i < MAXN; i++) factorial[i] = mul(i, factorial[i - 1]);
}

int comb(int n, int k) {
    if (k > n) return 0;
    return divide(factorial[n], mul(factorial[n - k], factorial[k]));
}

int inverse[MAXN];

void get_inverse() {
    inverse[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        inverse[i] = inv(i);
    }
}

int comb(long long n, int k) {
    if (k > n) return 0;
    if (n - k < k) k = n - k;
    n %= MOD;
    int ans = 1;
    for (int i = 0; i < k; i++) {
        ans = mul(ans, n - i);
        ans = mul(ans, inverse[i + 1]);
    } 
    return ans;
}

int fact[MAXN];
int inv_[MAXN];
int pow2[MAXN];
int c[MAXN][MAXN];

int add(int x, int y) {
    x += y;
    while (x >= MOD) x -= MOD;
    while (x < 0) x += MOD;
    return x;
}

int mul(int x, int y) {
    return (x * 1ll * y) % MOD;
}

int fastexp(int b, int exp) {
    if (exp == 0) return 1;
    int temp = fastexp(b, exp / 2);
    temp = mul(temp, temp);
    if (exp % 2 == 1) temp = mul(temp, b);
    return temp;
}

void precompute(int n) {
    fact[0] = 1;
    inv_[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = mul(fact[i - 1], i);
        inv_[i] = fastexp(fact[i], MOD - 2);
    }
    for (int i = 0; i <= n; i++)
        pow2[i] = fastexp(2, i);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= i; j++)
            c[i][j] = mul(mul(fact[i], inv_[j]), inv_[i - j]);
}

bool is_prime(int x) {
    for (int i = 2; i * 1ll * i <= x; i++)
        if (x % i == 0)
            return false;
    return true;    
}

long long euler_phi(long long n) {
    long long ans = n;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}

long long ap_an(int a1, int d, int n) {
    return (long long)(1ll * a1 + 1ll * (n - 1) * d);
}

long long ap_sum(int a1, int d, int n) {
    return (long long)(1ll * n * a1 + 1ll * n * (n - 1) * d / 2);
}

long long ap_an_sum(int a1, int an, int n) {
    return (long long)(1ll * n * (a1 + an) / 2);
}