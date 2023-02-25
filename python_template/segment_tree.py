from functools import reduce

# 单点更新-区间元素和查询
class SegmentTree:
    def __init__(self, n: int):
        self.n = n
        self.sum = [0] * (n * 4)
    
    def update(self, root, l, r, idx, val):
        if l == r:
            self.sum[root] += val
            return
        m = (l + r) // 2
        if idx <= m:
            self.update(root * 2, l, m, idx, val)
        else:
            self.update(root * 2 + 1, m + 1, r, idx, val)
        self.sum[root] = self.sum[root * 2] + self.sum[root * 2 + 1]
    
    def query(self, root, l, r, L, R):
        if L <= l and r <= R:
            return self.sum[root]
        tot = 0
        m = (l + r) // 2
        if L <= m:
            tot += self.query(root * 2, l, m, L, R)
        if R > m:
            tot += self.query(root * 2 + 1, m + 1, r, L, R)
        return tot

# 单点更新-区间最大值查询
class SegmentTree:
    def __init__(self, n: int):
        self.n = n
        self.max = [float('-inf')] * (n * 4)
    
    def update(self, root, l, r, idx, val):
        if l == r:
            self.max[root] = val
            return
        m = (l + r) // 2
        if idx <= m:
            self.update(root * 2, l, m, idx, val)
        else:
            self.update(root * 2 + 1, m + 1, r, idx, val)
        self.max[root] = max(self.max[root * 2], self.max[root * 2 + 1])
    
    def query(self, root, l, r, L, R):
        if L <= l and r <= R:
            return self.max[root]
        ans = float('-inf')
        m = (l + r) // 2
        if L <= m:
            ans = self.query(root * 2, l, m, L, R)
        if R > m:
            ans = max(ans, self.query(root * 2 + 1, m + 1, r, L, R))
        return ans

# 单点更新-区间最小值查询
class SegmentTree:
    def __init__(self, n: int):
        self.n = n
        self.min = [float('inf')] * (n * 4)
    
    def update(self, root, l, r, idx, val):
        if l == r:
            self.min[root] = val
            return
        m = (l + r) // 2
        if idx <= m:
            self.update(root * 2, l, m, idx, val)
        else:
            self.update(root * 2 + 1, m + 1, r, idx, val)
        self.min[root] = min(self.min[root * 2], self.min[root * 2 + 1])
    
    def query(self, root, l, r, L, R):
        if L <= l and r <= R:
            return self.min[root]
        ans = float('inf')
        m = (l + r) // 2
        if L <= m:
            ans = self.query(root * 2, l, m, L, R)
        if R > m:
            ans = min(ans, self.query(root * 2 + 1, m + 1, r, L, R))
        return ans

# 动态开点-区间元素个数查询
class SegmentTree:
    def __init__(self, l=1, r=10 ** 9):
        self.left, self.right = None, None
        self.l, self.r = l, r
        self.cnt = 0

    def add(self, l: int, r: int) -> None:
        if self.cnt == self.r - self.l + 1:
            return
        if l <= self.l and r >= self.r:
            self.cnt = self.r - self.l + 1
            return
        mid = (self.l + self.r) // 2
        # 动态开点
        if self.left is None:
            self.left = SegmentTree(self.l, mid)
        if self.right is None:
            self.right = SegmentTree(mid + 1, self.r)
        if l <= mid:
            self.left.add(l, r)
        if r > mid:
            self.right.add(l, r)
        self.cnt = self.left.cnt + self.right.cnt

    def query_cnt(self) -> int:
        return self.cnt

# 区间加法-区间元素和查询
class SegmentTree:
    def __init__(self, n: int):
        self.n = n
        self.val = [0] * (n * 4)
        self.lazy = [0] * (n * 4)
    
    def push(self, root, l, r):
        if (l != r and self.lazy[root]):
            m = (l + r) // 2
            self.val[root * 2] += self.lazy[root] * (m - l + 1)
            self.lazy[root * 2] += self.lazy[root]
            self.val[root * 2 + 1] += self.lazy[root] * (r - m)
            self.lazy[root * 2 + 1] += self.lazy[root]
            self.lazy[root] = 0
    
    def merge(self, root):
        self.val[root] = self.val[root * 2] + self.val[root * 2 + 1]
    
    def update(self, root, l, r, L, R, val):
        self.push(root, l, r)
        if L <= l and r <= R:
            self.val[root] += val * (r - l + 1)
            self.lazy[root] += val
            return
        m = (l + r) // 2
        if L <= m:
            self.update(root * 2, l, m, L, R, val)
        if R > m:
            self.update(root * 2 + 1, m + 1, r, L, R, val)
        self.merge(root)
    
    def query(self, root, l, r, L, R):
        self.push(root, l, r)
        if L <= l and r <= R:
            return self.val[root]
        ans = 0
        m = (l + r) // 2
        if L <= m:
            ans += self.query(root * 2, l, m, L, R)
        if R > m:
            ans += self.query(root * 2 + 1, m + 1, r, L, R)
        return ans

# 区间更新-区间元素和查询
class SegmentTree:
    def __init__(self, n: int):
        self.n = n
        self.val = [0] * (n * 4)
        self.lazy = [0] * (n * 4)
    
    def push(self, root, l, r):
        if (l != r and self.lazy[root]):
            m = (l + r) // 2
            self.val[root * 2] = self.lazy[root] * (m - l + 1)
            self.lazy[root * 2] = self.lazy[root]
            self.val[root * 2 + 1] = self.lazy[root] * (r - m)
            self.lazy[root * 2 + 1] = self.lazy[root]
            self.lazy[root] = 0
    
    def merge(self, root):
        self.val[root] = self.val[root * 2] + self.val[root * 2 + 1]
    
    def update(self, root, l, r, L, R, val):
        self.push(root, l, r)
        if L <= l and r <= R:
            self.val[root] = val * (r - l + 1)
            self.lazy[root] = val
            return
        m = (l + r) // 2
        if L <= m:
            self.update(root * 2, l, m, L, R, val)
        if R > m:
            self.update(root * 2 + 1, m + 1, r, L, R, val)
        self.merge(root)
    
    def query(self, root, l, r, L, R):
        self.push(root, l, r)
        if L <= l and r <= R:
            return self.val[root]
        ans = 0
        m = (l + r) // 2
        if L <= m:
            ans += self.query(root * 2, l, m, L, R)
        if R > m:
            ans += self.query(root * 2 + 1, m + 1, r, L, R)
        return ans

# 区间反转-区间元素和查询
class SegmentTree:
    def __init__(self, n: int):
        self.n = n
        self.val = [0] * (n * 4)
        self.lazy = [0] * (n * 4)
    
    def push(self, root, l, r):
        if (l != r and self.lazy[root]):
            m = (l + r) // 2
            self.val[root * 2] = (m - l + 1) - self.val[root * 2]
            self.lazy[root * 2] ^= 1
            self.val[root * 2 + 1] = (r - m) - self.val[root * 2 + 1]
            self.lazy[root * 2 + 1] ^= 1
            self.lazy[root] = 0
    
    def merge(self, root):
        self.val[root] = self.val[root * 2] + self.val[root * 2 + 1]
    
    def update(self, root, l, r, L, R):
        self.push(root, l, r)
        if L <= l and r <= R:
            self.val[root] = (r - l + 1) - self.val[root]
            self.lazy[root] ^= 1
            return
        m = (l + r) // 2
        if L <= m:
            self.update(root * 2, l, m, L, R)
        if R > m:
            self.update(root * 2 + 1, m + 1, r, L, R)
        self.merge(root)
    
    def query(self, root, l, r, L, R):
        self.push(root, l, r)
        if L <= l and r <= R:
            return self.val[root]
        ans = 0
        m = (l + r) // 2
        if L <= m:
            ans += self.query(root * 2, l, m, L, R)
        if R > m:
            ans += self.query(root * 2 + 1, m + 1, r, L, R)
        return ans