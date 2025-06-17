from typing import *
from collections import *

# 已知树结构，求N叉树K个节点的LCA
class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

def lca(root: TreeNode, nodes: List[TreeNode]) -> TreeNode:
    def dfs(root: Optional[TreeNode]) -> Generator[TreeNode, None, None]:
        if not root:
            return
        
        subtreeSum[root.val] += int(root in needs)
        
        for child in root.children:
            if not child:
                continue
            yield from dfs(child)
            subtreeSum[root.val] += subtreeSum[child.val]
                
        if subtreeSum[root.val] == len(nodes):
            yield root
                    
    needs = set(nodes)
    subtreeSum = defaultdict(int)
    return next(dfs(root))

# 倍增法求LCA
n = 10 ** 5
e = [[] for _ in range(n)]
depth = [0] * n
f = [[0] * 31 for _ in range(n)]
def dfs(u: int, p: int):
    if p != -1:
        depth[u] = depth[p] + 1
        f[u][0] = p
    for i in range(1, 31):
        f[u][i] = f[f[u][i - 1]][i - 1]
    for v, w in e[u]:
        if v == p:
            continue
        dfs(v, u)
dfs(0, -1)

def lca(x: int, y: int) -> int:
    if depth[x] > depth[y]:
        x, y = y, x
    temp = depth[y] - depth[x]
    i = 0
    while temp:
        if temp & 1:
            y = f[y][i]
        i += 1
        temp >>= 1
    if x == y:
        return y
    for j in range(30, -1, -1):
        if y == x:
            break
        if f[x][j] != f[y][j]:
            x = f[x][j]
            y = f[y][j]
    return y if y == x else f[y][0]

class LcaBinaryLifting:
    def __init__(self, edges: List[List[int]]):
        n = len(edges) + 1
        self.m = m = n.bit_length()
        g = [[] for _ in range(n)]
        for x, y, w in edges:
            g[x].append((y, w))
            g[y].append((x, w))

        depth = [0] * n
        dis = [0] * n
        pa = [[-1] * m for _ in range(n)]

        def dfs(x: int, fa: int) -> None:
            pa[x][0] = fa
            for y, w in g[x]:
                if y != fa:
                    depth[y] = depth[x] + 1
                    dis[y] = dis[x] + w
                    dfs(y, x)

        dfs(0, -1)

        for i in range(m - 1):
            for x in range(n):
                if (p := pa[x][i]) != -1:
                    pa[x][i + 1] = pa[p][i]

        self.depth = depth
        self.dis = dis
        self.pa = pa

    def get_kth_ancestor(self, node: int, k: int) -> int:
        for i in range(k.bit_length()):
            if k >> i & 1:
                node = self.pa[node][i]
        return node

    # 返回 x 和 y 的最近公共祖先
    def get_lca(self, x: int, y: int) -> int:
        if self.depth[x] > self.depth[y]:
            x, y = y, x
        # 使 y 和 x 在同一深度
        y = self.get_kth_ancestor(y, self.depth[y] - self.depth[x])
        if y == x:
            return x
        for i in range(self.m - 1, -1, -1):
            px, py = self.pa[x][i], self.pa[y][i]
            if px != py:
                x, y = px, py  # 同时往上跳 2**i 步
        return self.pa[x][0]

    # 返回 x 到 y 的距离（最短路长度）
    def get_dis(self, x: int, y: int) -> int:
        return self.dis[x] + self.dis[y] - self.dis[self.get_lca(x, y)] * 2

    # 从 x 往上跳【至多】d 距离，返回最远能到达的节点
    def upto_dis(self, x: int, d: int) -> int:
        dx = self.dis[x]
        for i in range(self.m - 1, -1, -1):
            p = self.pa[x][i]
            if p != -1 and dx - self.dis[p] <= d:  # 可以跳至多 d
                x = p
        return x