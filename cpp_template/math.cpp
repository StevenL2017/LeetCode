const int MOD = 998244353;
const int MAXN = 1e5 + 7;

int factorial[MAXN];

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
    while (y)
    {
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

void get_factorial() {
	factorial[0] = 1;
	for(int i = 1; i < MAXN; i++) factorial[i] = mul(i, factorial[i - 1]);
}

int comb(int n, int k) {
	if (k > n) return 0;
	return divide(factorial[n], mul(factorial[n - k], factorial[k]));
}

bool is_prime(int x) {
    for (int i = 2; i * 1ll * i <= x; i++)
        if (x % i == 0)
            return false;
    return true;    
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