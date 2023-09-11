from typing import *

# fail数组(下标)
def get_fail(s: str) -> List[int]:
    n = len(s)
    fail = [-1] * n
    for i in range(1, n):
        j = fail[i - 1]
        while j != -1 and s[j + 1] != s[i]:
            j = fail[j]
        if s[j + 1] == s[i]:
            fail[i] = j + 1
    return fail

# KMP算法(下标)
def kmp(query: str, pattern: str) -> bool:
    n, m = len(query), len(pattern)
    fail = get_fail(pattern)
    j = -1
    for i in range(n):
        while j != -1 and pattern[j + 1] != query[i]:
            j = fail[j]
        if pattern[j + 1] == query[i]:
            j += 1
            if j == m - 1:
                return i - m + 1
    return -1

# KMP算法(下标)
def kmp_cnt(query: str, pattern: str) -> int:
    n, m = len(query), len(pattern)
    fail = get_fail(pattern)
    ans, j = 0, -1
    for i in range(n):
        while j != -1 and pattern[j + 1] != query[i]:
            j = fail[j]
        if pattern[j + 1] == query[i]:
            j += 1
            if j == m - 1:
                ans += 1
                j = fail[j]
    return ans

# Z函数(字符串s[i]开头的后缀与本字符串的最长公共前缀)
def z_func(s: str) -> List[int]:
    n = len(s)
    z = [0] * n
    l, r = 0, 0
    for i in range(1, n):
        if i <= r and z[i - l] < r - i + 1:
            z[i] = z[i - l]
        else:
            z[i] = max(0, r - i + 1)
            while i + z[i] < n and s[z[i]] == s[i + z[i]]:
                z[i] += 1
        if i + z[i] - 1 > r:
            l = i
            r = i + z[i] - 1
    return z

# Rabin-Karp算法
def rk(s: str):
    n = len(s)
    mod, base = 10 ** 9 + 7, 31
    pre, mul = [0] * (n + 1), [1] + [0] * n
    for i in range(1, n + 1):
        pre[i] = (pre[i - 1] * base + ord(s[i - 1])) % mod
        mul[i] = mul[i - 1] * base % mod

    def get_hash(l, r):
        return (pre[r + 1] - pre[l] * mul[r - l + 1] % mod + mod) % mod