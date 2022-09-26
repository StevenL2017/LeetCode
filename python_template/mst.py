from unionfind import *

# Kruskal算法
def kruskal(n, edges):
    m = len(edges)
    edges.sort(key=lambda x: x[2])

    uf = UnionFind(n)
    value = 0
    for u, v, w in edges:
        if not uf.same(u, v):
            uf.union(u, v)
            value += w
    return value