const int MOD = 1e9 + 7;
const int MAXN = 1e3 + 3;

long long c[MAXN][MAXN];

void comb(int x) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j <= i; j++) {
            if (!j) c[i][j] = 1;
            else c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
        }
    }
}

int main() {
    comb(MAXN);
}