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

# Manacher算法
def manacher(s: str) -> list[int]:
    # 将 s 改造为 t，这样就不需要讨论 n 的奇偶性，因为新串 t 的每个回文子串都是奇回文串（都有回文中心）
    # s 和 t 的下标转换关系：
    # (si+1)*2 = ti
    # ti/2-1 = si
    # ti 为偶数，对应奇回文串（从 2 开始）
    # ti 为奇数，对应偶回文串（从 3 开始）
    t = '#'.join(['^'] + list(s) + ['$'])
    # 定义一个奇回文串的回文半径=(长度+1)/2，即保留回文中心，去掉一侧后的剩余字符串的长度
    # halfLen[i] 表示在 t 上的以 t[i] 为回文中心的最长回文子串的回文半径
    # 即 [i-halfLen[i]+1,i+halfLen[i]-1] 是 t 上的一个回文子串
    halfLen = [0] * (len(t) - 2)
    halfLen[1] = 1
    # boxR 表示当前右边界下标最大的回文子串的右边界下标+1
    # boxM 为该回文子串的中心位置，二者的关系为 r=mid+halfLen[mid]
    boxM = boxR = 0
    for i in range(2, len(halfLen)):
        hl = 1
        if i < boxR:
            # 记 i 关于 boxM 的对称位置 i'=boxM*2-i
            # 若以 i' 为中心的最长回文子串范围超出了以 boxM 为中心的回文串的范围（即 i+halfLen[i'] >= boxR）
            # 则 halfLen[i] 应先初始化为已知的回文半径 boxR-i，然后再继续暴力匹配
            # 否则 halfLen[i] 与 halfLen[i'] 相等
            hl = min(halfLen[boxM * 2 - i], boxR - i)
        # 暴力扩展
        # 算法的复杂度取决于这部分执行的次数
        # 由于扩展之后 boxR 必然会更新（右移），且扩展的的次数就是 boxR 右移的次数
        # 因此算法的复杂度 = O(len(t)) = O(n)
        while t[i - hl] == t[i + hl]:
            hl += 1
            boxM, boxR = i, i + hl
        halfLen[i] = hl
    return halfLen

# t 中回文子串的长度为 hl*2-1
# 由于其中 # 的数量总是比字母的数量多 1
# 因此其在 s 中对应的回文子串的长度为 hl-1
# 这一结论可用在 isPalindrome 中
# 判断左闭右开区间 [l,r) 是否为回文串  0<=l<r<=n
# 根据下标转换关系得到 s 的 [l,r) 子串在 t 中对应的回文中心下标为 l+r+1
# 需要满足 halfLen[l + r + 1] - 1 >= r - l，即 halfLen[l + r + 1] > r - l
def isPalindrome(halfLen: list[int], l: int, r: int) -> bool:
    return halfLen[l + r + 1] > r - l