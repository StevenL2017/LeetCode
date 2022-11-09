#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int n;
vector<vector<int>> graph;

// check if there is a loop for a directed graph
vector<int> order, visited(n, 0), pos(n, 0);

function<void(int)> dfs = [&] (int node) {
    visited[node] = 1;
    for (auto& nxt: graph[node]) {
        if (visited[nxt]) continue;
        dfs(nxt);
    }
    order.push_back(node);
};

function<bool()> find_loop = [&] () -> bool {
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    reverse(order.begin(), order.end());

    for (int i = 0; i < n; i++) {
        pos[order[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        for (auto& j: graph[i]) {
            if (pos[i] > pos[j]) {
                return true;
            }
        }
    }
    return false;
};