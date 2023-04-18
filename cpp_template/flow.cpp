#include <vector>
#include <queue>

using namespace std;

const int MAXN = 2e2 + 3;

struct Edge {
    int from, to, cap, flow;
    Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
};

// Edmonds-Karp 算法
struct EK {
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

// Dinic 算法
struct Dinic {
    int n, m;
    vector<Edge> e;
    int fir[MAXN];
    int dep[MAXN];
    int cur[MAXN];

    void init(int n) {
        this->n = n;
        this->m = 0;
        memset(fir, -1, sizeof(int) * n);
        e.clear();
    }

    void add_edge(int from, int to, int cap) {
        e.push_back(Edge(to, fir[from], cap, 0));
        fir[from] = m++;
        e.push_back(Edge(from, fir[to], 0, 0));
        fir[to] = m++;
    }

    bool bfs(int s, int t) {
        queue<int> q;
        memset(dep, 0, sizeof(int) * n);
        dep[s] = 1;
        q.push(s);
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int i = fir[u]; ~i; i = e[i].to) {
                int v = e[i].from;
                if ((!dep[v]) && (e[i].cap > e[i].flow)) {
                    dep[v] = dep[u] + 1;
                    q.push(v);
                }
            }
        }
        return dep[t];
    }

    int dfs(int u, int t, int bound) {
        if ((u == t) || (!bound)) return bound;
        int ret = 0;
        for (int& i = cur[u]; ~i; i = e[i].to) {
            int v = e[i].from, d;
            if ((dep[v] == dep[u] + 1) && (d = dfs(v, t, min(bound - ret, e[i].cap - e[i].flow)))) {
                ret += d;
                e[i].flow += d;
                e[i ^ 1].flow -= d;
                if (ret == bound) return ret;
            }
        }
        return ret;
    }

    int max_flow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            memcpy(cur, fir, sizeof(int) * n);
            flow += dfs(s, t, INT_MAX);
        }
        return flow;
    }
};