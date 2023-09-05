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