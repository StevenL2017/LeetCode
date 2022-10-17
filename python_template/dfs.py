from typing import *
from collections import *

# 一般形式
# visited = set()
# visited.add(node)
# def dfs(node):
#     if condition:
#         return
#     for nxt in adj[node]:
#         if nxt not in visited:
#             visited.add(nxt)
#             dfs(nxt)

# 统计子树大小/点权和问题
# def dfs(node: int, fa: int) -> int:
#     sz = 1
#     for nxt in graph[node]:
#         if nxt != fa:
#             sz += dfs(nxt, node)
#     return sz
# dfs(0, -1)

# DFS找唯一环
# 编号 1 ~ n
def dfs_loop(n, graph):
    father = [0] * (n + 1)
    depth = [0] * (n + 1)
    in_loop = [False] * (n + 1)
    loop = 0
    def dfs(node: int, pre: int) -> None:
        nonlocal loop
        father[node] = pre
        depth[node] = depth[pre] + 1
        for nxt in graph[node]:
            if nxt == pre: continue
            if depth[nxt] == 0: dfs(nxt, node)
            if depth[node] > depth[nxt]:
                temp = node
                while temp != nxt:
                    in_loop[temp] = True
                    loop += 1
                    temp = father[temp]
                in_loop[nxt] = True
                loop += 1
    dfs(1, 0)

# N叉树K个节点的LCA
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

# 欧拉回路：Hierholzer算法
def hierholzer(adj):
    ans = []
    def dfs(node):
        while adj[node]:
            # 平常我们都是直接顺序枚举每个点的邻居，但这里我们倒着枚举
            # 仅是为了方便删掉枚举过的点，不影响结果
            # 重点理解：DFS的调用其实是一个拆边的过程
            v = adj[node].pop()
            dfs(v)
            ans.append(node)
    return ans[::-1]