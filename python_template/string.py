from typing import *

# fail数组
def get_fail(self, s: str) -> List[int]:
    n = len(s)
    fail = [-1] * n
    for i in range(1, n):
        j = fail[i - 1]
        while j != -1 and s[j + 1] != s[i]:
            j = fail[j]
        if s[j + 1] == s[i]:
            fail[i] = j + 1
    return fail

# KMP
def kmp(query: str, pattern: str) -> bool:
	n, m = len(query), len(pattern)
	
	fail = [-1] * m
	for i in range(1, m):
		j = fail[i - 1]
		while j != -1 and pattern[j + 1] != pattern[i]:
			j = fail[j]
		if pattern[j + 1] == pattern[i]:
			fail[i] = j + 1
			
	match = -1
	for i in range(1, n - 1):
		while match != -1 and pattern[match + 1] != query[i]:
			match = fail[match]
		if pattern[match + 1] == query[i]:
			match += 1
			if match == m - 1:
				return True
	return False

# Z算法
def z_function(s):
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