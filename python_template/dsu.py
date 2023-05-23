# 路径压缩 + 启发式合并
class UnionFind:
    def __init__(self, n: int):
        self.f = list(range(n))
        self.sz = [1] * n
        self.count = n
        
    def find(self, x: int) -> int:
        if x != self.f[x]:
            self.f[x] = self.find(self.f[x])
        return self.f[x]

    def union(self, x: int, y: int) -> bool:
        x, y = self.find(x), self.find(y)
        if x == y:
            return False
        if self.sz[x] < self.sz[y]:
            x, y = y, x
        self.f[y] = x
        self.sz[x] += self.sz[y]
        self.count -= 1
        return True

    def same(self, x: int, y: int) -> bool:
        x, y = self.find(x), self.find(y)
        return x == y

# 带权可持久化并查集（仅启发式合并）
class UnionFind:
    def __init__(self, n: int):
        self.f = list(range(n))
        self.sz = [1] * n
        self.cost = [0] * n
        self.count = n
        
    def find(self, x: int, limit: int) -> int:
        while x != self.f[x] and self.cost[x] < limit:
            x = self.f[x]
        return x

    def union(self, x: int, y: int, w: int) -> bool:
        x, y = self.find(x, w + 1), self.find(y, w + 1)
        if x == y:
            return False
        if self.sz[x] < self.sz[y]:
            x, y = y, x
        self.f[y] = x
        self.sz[x] += self.sz[y]
        self.cost[y] = w
        self.count -= 1
        return True

    def same(self, x: int, y: int, limit: int) -> bool:
        x, y = self.find(x, limit), self.find(y, limit)
        return x == y