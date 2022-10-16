import heapq

# Floyd算法
def floyd(n, edges):
    dist = [[float('inf')] * n for _ in range(n)]
    for u, v in edges:
        dist[u][v] = 1
        dist[v][u] = 1

    for k in range(n):
        for i in range(n):
            for j in range(n):
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
    return dist

# Dijkstra算法-朴素
def dijkstra_1(n, edges):
    g = [[] for _ in range(n)]
    for x, y, cost in edges:
        g[x].append((y, cost))

    dist = [float('inf')] * n
    start = 0
    dist[start] = 0
    used = [False] * n
    for _ in range(n):
        x = -1
        for y, u in enumerate(used):
            if not u and (x == -1 or dist[y] < dist[x]):
                x = y
        used[x] = True
        for y, cost in enumerate(g[x]):
            dist[y] = min(dist[y], dist[x] + cost)

# Dijkstra算法-堆
def dijkstra_2(n, edges):
    g = [[] for _ in range(n)]
    for x, y, cost in edges:
        g[x].append((y, cost))

    dist = [float('inf')] * n
    start = 0
    dist[start] = 0
    q = [(0, start)]
    while q:
        cost, x = heapq.heappop(q)
        if dist[x] < cost:
            continue
        for y, cost in g[x]:
            d = dist[x] + cost
            if d < dist[y]:
                dist[y] = d
                heapq.heappush(q, (d, y))