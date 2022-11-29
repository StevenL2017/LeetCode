# 一般形式
# 无权图
# graph = defaultdict(set)
# for u, v in edges:
#     graph[u].add(v)
#     graph[v].add(u)

# graph = defaultdict(set)
# for u, v in edges:
#     graph[u].add(v)

# 有权图
# graph = defaultdict(dict)
# for u, v, w in edges:
#     graph[u][v] = w
#     graph[v][u] = w

# graph = defaultdict(dict)
# for u, v, w in edges:
#     graph[u][v] = w

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