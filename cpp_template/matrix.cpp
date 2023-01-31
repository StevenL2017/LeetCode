#include <string>

const int dirs2[2][2] = {{1, 0}, {0, 1}};
const int dirs4[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const int dirs8[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}};

// for (int i = 0; i < 2; i++) {
//     int nr = r + dirs2[i][0], nc = c + dirs2[i][1];
//     if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
        
//     }
// }

// for (int i = 0; i < 4; i++) {
//     int nr = r + dirs4[i][0], nc = c + dirs4[i][1];
//     if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
        
//     }
// }

// for (int i = 0; i < 8; i++) {
//     int nr = r + dirs8[i][0], nc = c + dirs8[i][1];
//     if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
        
//     }
// }

const int MOD = 1e9 + 7;
const int N = 100;

struct Matrix {
    long long a[N + 3][N + 3];

    Matrix() { memset(a, 0, sizeof(a)); }

    Matrix operator*(const Matrix& b) const {
        Matrix res;
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                for (int k = 1; k <= N; ++k)
                    res.a[i][j] = (res.a[i][j] + a[i][k] * b.a[k][j]) % MOD;
        return res;
    }
} ans, base;

// this is an example of f[n] = f[n - 1] + f[n - 2] (Fibonacci dp)
// answer f[n] = ans.a[1][1]
void init() {
    base.a[1][1] = base.a[1][2] = base.a[2][1] = 1;
    ans.a[1][1] = ans.a[1][2] = 1;
}

// n is count of matrix multiplications
void qpow(long long n) {
    while (n) {
        if (n & 1) ans = ans * base;
        base = base * base;
        n >>= 1;
    }
}

// this is an example of f[n] = f[n - 1] + f[n - m]
// answer f[n] = sum(ans.a[1][i])
void init(int m) {
    base.a[1][1] = base.a[m][1] = 1;
    ans.a[1][1] = ans.a[m][1] = 1;
    for (int i = 2; i <= m; i++) {
        base.a[i - 1][i] = 1;
        ans.a[i - 1][i] = 1;
    }
}

// i k j could be faster than i j k
Matrix mmul(int m, const Matrix& a, const Matrix& b) {
    Matrix res;
    for (int i = 1; i <= m; ++i) {
        for (int k = 1; k <= m; ++k) {
            for (int j = 1; j <= m; ++j) {
                res.a[i][j] = (res.a[i][j] + a.a[i][k] * b.a[k][j]) % MOD;
            }
        }
    }
    return res;
}

// n is count of matrix multiplications, m is size of matrix
void mpow(int m, long long n) {
    while (n) {
        if (n & 1) ans = mmul(m, ans, base);
        base = mmul(m, base, base);
        n >>= 1;
    }
}