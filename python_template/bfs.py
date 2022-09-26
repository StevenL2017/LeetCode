from typing import *
from collections import *

# 一般形式
# q = deque()
# visited = set()
# q.append((node, cost))
# visited.add(node)
# step = 0
# while q:
# 	step += 1
# 	for _ in range(len(q)):
# 		node, cost = q.popleft()
# 		for nxt in adj[node]:
# 			if nxt not in visited:
# 				q.append((nxt, cost + 1))
# 				visited.add(nxt)

# 矩阵移动
# for nr, nc in ((r + 1, c), (r, c + 1)):
# 	if 0 <= nr < m and 0 <= nc < n:
# 		pass
	
# for nr, nc in ((r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)):
# 	if 0 <= nr < m and 0 <= nc < n:
# 		pass
		
# for nr, nc in ((r - 1, c - 1), (r + 1, c - 1), (r - 1, c + 1), (r + 1, c + 1)):
# 	if 0 <= nr < m and 0 <= nc < n:
# 		pass

# 0-1 BFS
def bfs_01(grid):
    m, n = len(grid), len(grid[0])
    dis = [[float('inf')] * n for _ in range(m)]
    dis[0][0] = 0
    q = deque([(0, 0)])
    while q:
        x, y = q.popleft()
        for nx, ny in (x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1):
            if 0 <= nx < m and 0 <= ny < n:
                g = grid[x][y]
                if dis[x][y] + g < dis[nx][ny]:
                    dis[nx][ny] = dis[x][y] + g
                    if g == 0: q.appendleft((nx, ny))
                    else: q.append((nx, ny))
    return dis[m - 1][n - 1]