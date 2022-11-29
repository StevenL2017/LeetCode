#include <vector>
#include <set>
#include <algorithm>
#include "unionfind.cpp"

using namespace std;

const int MAXN = 2e5 + 3;

struct Edge {
    int u, v, w, i;
    bool operator < (const Edge& e) const {
        return w < e.w;
    }
};

// Kruskal算法
int mst_edges[MAXN];
long long kruskal(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end());

    UnionFind uf(n);
    long long value = 0;
    for (auto& [u, v, w, i]: edges) {
        if (!uf.same(u, v)) {
            uf.merge(u, v);
            value += w;
            mst_edges[i] = 1;
        }
    }
    return value;
}