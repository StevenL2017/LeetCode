# 组合数模板
MOD = 10 ** 9 + 7
MX = 10 ** 5

fac = [0] * MX
fac[0] = 1
for i in range(1, MX):
    fac[i] = fac[i - 1] * i % MOD

inv_fac = [0] * MX
inv_fac[MX - 1] = pow(fac[MX - 1], -1, MOD)
for i in range(MX - 1, 0, -1):
    inv_fac[i - 1] = inv_fac[i] * i % MOD

def comb(n: int, k: int) -> int:
    return fac[n] * inv_fac[k] % MOD * inv_fac[n - k] % MOD


# 模10组合数
MOD = 10
MX = 100_000

f = [0] * (MX + 1)
inv_f = [0] * (MX + 1)
p2 = [0] * (MX + 1)
p5 = [0] * (MX + 1)

f[0] = 1
for i in range(1, MX + 1):
    x = i
    # 计算 2 的幂次
    e2 = (x & -x).bit_length() - 1
    x >>= e2
    # 计算 5 的幂次
    e5 = 0
    while x % 5 == 0:
        e5 += 1
        x //= 5
    f[i] = f[i - 1] * x % MOD
    p2[i] = p2[i - 1] + e2
    p5[i] = p5[i - 1] + e5

inv_f[MX] = pow(f[MX], 3, MOD)  # 欧拉定理求逆元
for i in range(MX, 0, -1):
    x = i
    x >>= (x & -x).bit_length() - 1
    while x % 5 == 0:
        x //= 5
    inv_f[i - 1] = inv_f[i] * x % MOD

def comb(n: int, k: int) -> int:
    return f[n] * inv_f[k] * inv_f[n - k] * \
        pow(2, p2[n] - p2[k] - p2[n - k], MOD) * \
        pow(5, p5[n] - p5[k] - p5[n - k], MOD) % MOD


# Lucas定理
def comb_mod(n, k, p):
    ans = 1
    while n > 0 or k > 0:
        nr, kr = n % p, k % p
        if nr < kr:
            return 0
        ans = ans * comb(nr, kr) % p
        n //= p
        k //= p
    return ans