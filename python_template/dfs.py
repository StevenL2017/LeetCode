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
def dfs_sub(n, graph):
    def dfs(node: int, fa: int) -> int:
        sz = 1
        for nxt in graph[node]:
            if nxt != fa:
                sz += dfs(nxt, node)
        return sz
    dfs(0, -1)

# 连通无向图找环
def dfs_loop(n, graph):
    # 编号 1 ~ n
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