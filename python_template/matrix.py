from typing import *

# for nr, nc in ((r + 1, c), (r, c + 1)):
# 	if 0 <= nr < m and 0 <= nc < n:
# 		pass
	
# for nr, nc in ((r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)):
# 	if 0 <= nr < m and 0 <= nc < n:
# 		pass
		
# for nr, nc in ((r - 1, c - 1), (r + 1, c - 1), (r - 1, c + 1), (r + 1, c + 1)):
# 	if 0 <= nr < m and 0 <= nc < n:
# 		pass

MOD = 10 ** 9 + 7

# 矩阵乘法
def multiply(a: List[List[int]], b: List[List[int]]) -> List[List[int]]:
    n, p, m = len(a), len(a[0]), len(b[0])
    c = [[0] * m for _ in range(n)]
    for i in range(n):
        for k in range(p):
            for j in range(m):
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD
    return c

# 矩阵快速幂
def pow(base: List[List[int]], a: List[List[int]], n: int) -> List[List[int]]:
    while n:
        if n % 2:
            base = multiply(base, a)
        a = multiply(a, a)
        n //= 2
    return base