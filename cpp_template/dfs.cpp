#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int n;
vector<vector<int>> graph;

// check if a node is a parent (may not directly) of a target
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

// calculate diameter of tree
int d = 0;
vector<int> d1(n), d2(n);

function<void(int, int)> dfs_dia = [&] (int node, int fa) {
    d1[node] = d2[node] = 0;
    for (auto& nxt: graph[node]) {
        if (nxt == fa) continue;
        dfs_dia(nxt, node);
        int t = d1[nxt] + 1;
        if (t > d1[node]) {
            d2[node] = d1[node];
            d1[node] = t;
        }
        else if (t > d2[node]) {
            d2[node] = t;
        }
    }
    d = max(d, d1[node] + d2[node]);
};

// find loop for a connected undirected graph
vector<int> parent(n, -1), depth(n, -1), loop;
function<void(int, int)> dfs_loop = [&] (int node, int fa) {
    parent[node] = fa;
    depth[node] = fa >= 0 ? depth[fa] + 1 : 0;
    for (auto& nxt: graph[node]) {
        if (nxt == fa) continue;
        if (depth[nxt] == -1) dfs_loop(nxt, node);
        if (depth[node] > depth[nxt] && loop.empty()) {
            for (int i = node; i != parent[nxt]; i = parent[i]) {
                loop.push_back(i);
            }
        }
    }
};