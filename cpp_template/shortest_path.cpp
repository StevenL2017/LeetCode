#include <vector>
#include <queue>

using namespace std;

const long long INF = 9e18 + 7;

// Dijkstra算法-堆
pair<vector<long long>, vector<long long>> dijkstra(int n, vector<vector<int>> edges) {
    vector<vector<pair<int, int>>> g(n);
    for (auto& edge: edges) {
        g[edge[0]].emplace_back(edge[1], edge[2]);
        g[edge[1]].emplace_back(edge[0], edge[2]);
    }

    vector<long long> dist(n, INF), path(n);
    int start = 0;
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, start);
    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        int cost = t.first, x = t.second;
        if (dist[x] < cost) continue;
        for (auto& [y, cost]: g[x]) {
            long long d = dist[x] + cost;
            if (d < dist[y]) {
                dist[y] = d;
                path[y] = x;
                pq.emplace(d, y);
            }
        }
    }
    return {dist, path};
}