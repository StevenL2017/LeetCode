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