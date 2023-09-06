#include <climits>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

struct Flow {
    static constexpr int INF = 1e9;
    int n;
    struct Edge {
        int to, cap;
        Edge(int to, int cap) : to(to), cap(cap) {}
    };
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
    Flow(int n) : n(n), g(n) {}
    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t)
                        return true;
                    que.push(v);
                }
            }
        }
        return false;
    }
    int dfs(int u, int t, int f) {
        if (u == t)
            return f;
        int r = f;
        for (int &i = cur[u]; i < int(g[u].size()); ++i) {
            int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                int a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0)
                    return f;
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, int c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    int maxFlow(int s, int t) {
        int ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, INF);
        }
        return ans;
    }
};

const int MAXN = 200 + 10;
const int INF = 1 << 30;

// Dinic 算法
template <typename T> class Dinic {
    private:
        int n, s, t, cnt, level[MAXN];
        T w[MAXN][MAXN];
        bool bfs() {
            memset(level, -1, sizeof(level));
            queue<int> que; que.push(s);
            level[s] = 0;
            while (que.size()) {
                int tmp = que.front(); que.pop();
                for (int i = 0; i < n; ++i) if (w[tmp][i] > 0) {
                    if (level[i] == -1) {
                        level[i] = level[tmp] + 1;
                        que.push(i);
                    }
                }
            }
            return level[t] != -1;
        }
        T flow(int now, T low) {
            T res = 0;
            if (now == t) return low;
            for (int i = 0; i < n && res < low; ++i) if (w[now][i] > 0) {
                if (level[i] == level[now] + 1) {
                    T tmp = flow(i, min(w[now][i], low - res));
                    w[now][i] -= tmp; w[i][now] += tmp;
                    res += tmp;
                }
            }
            if (!res) level[now] = -1;
            return res;
        }
    public:
        Dinic(int _n, int _s, int _t): n(_n), s(_s), t(_t) {
            memset(w, 0, sizeof(w));
        }
        void add_edge(int a, int b, T flow) {
            w[a][b] = flow;
        }
        T max_flow() {
            long long ans = 0;
            while (bfs()) ans += flow(s, INF);
            return ans;
        }
        vector<vector<T>> get_w() {
            vector<vector<T>> ret;
            for (int i = 0; i < n; ++i) {
                ret.push_back(vector<T>());
                for (int j = 0; j < n; ++j) ret[i].push_back(w[i][j]);
            }
            return ret;
        }
};

// Edmonds-Karp 算法
struct EK {
    struct Edge {
        int from, to, cap, flow;
        Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
    };

    int n, m;             // n：点数，m：边数
    vector<Edge> edges;   // edges：所有边的集合
    vector<int> G[MAXN];  // G：点 x -> x 的所有边在 edges 中的下标
    int a[MAXN];          // a：点 x -> BFS 过程中最近接近点 x 的边给它的最大流
    int p[MAXN];          // p：点 x -> BFS 过程中最近接近点 x 的边

    void init(int n) {
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void add_edge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    int max_flow(int s, int t) {
        int flow = 0;
        while (true) {
            memset(a, 0, sizeof(a));
            queue<int> Q;
            Q.push(s);
            a[s] = INT_MAX;
            while (!Q.empty()) {
                int x = Q.front();
                Q.pop();
                for (int i = 0; i < G[x].size(); i++) {  // 遍历以 x 作为起点的边
                    Edge& e = edges[G[x][i]];
                    if (!a[e.to] && e.cap > e.flow) {
                        p[e.to] = G[x][i];  // G[x][i] 是最近接近点 e.to 的边
                        a[e.to] = min(a[x], e.cap - e.flow);  // 最近接近点 e.to 的边赋给它的流
                        Q.push(e.to);
                    }
                }
                if (a[t]) break;  // 如果汇点接受到了流，就退出 BFS
            }
            if (!a[t])
                break;  // 如果汇点没有接受到流，说明源点和汇点不在同一个连通分量上
            for (int u = t; u != s; u = edges[p[u]].from) {  // 通过 u 追寻 BFS 过程中 s -> t 的路径
                edges[p[u]].flow += a[t];  // 增加路径上边的 flow 值
                edges[p[u] ^ 1].flow -= a[t];  // 减小反向路径的 flow 值
            }
            flow += a[t];
        }
        return flow;
    }
};