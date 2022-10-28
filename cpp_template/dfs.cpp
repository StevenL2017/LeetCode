#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int n;
vector<vector<int>> graph;

int t = 0;
vector<int> parent(n), depth(n);
vector<int> tin(n), tout(n);

function<void(int, int, int)> dfs = [&] (int node, int fa, int d) {
    parent[node] = fa;
    depth[node] = d;
    tin[node] = t++;
    for (auto& nxt: graph[node]) {
        if (nxt == fa) continue;
        dfs(nxt, node, d + 1);
    }
    tout[node] = t++;
};

function<bool(int, int)> is_parent = [&] (int node, int target) -> bool {
    return tin[node] <= tin[target] && tout[target] <= tout[node];
};