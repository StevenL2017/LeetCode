#include <vector>
#include <set>

using namespace std;

const int MAXN = 1e5 + 3;

vector<int> e[MAXN];
// dfn：记录每个点的时间戳
// low：能不经过父亲到达最小的编号
// tt：时间戳
int dfn[MAXN], low[MAXN], tt;
// bridge: 割边答案
set<pair<int, int>> bridge;
// node: 割点答案
set<int> node;

// 因为 Tarjan 图不一定连通
// 遍历所有节点，所有未访问过的节点跑Tarjan
// tt = 0; 时间戳初始为 0
// tarjan_edge(i, -1); 从第 i 个点开始
void tarjan_edge(int u, int p) {
    low[u] = dfn[u] = ++tt;
    for (auto v: e[u]) {
        if (v == p) continue;
        if (dfn[v] == 0) {
            tarjan_edge(v, u);
            low[u] = min(low[u], low[v]); // 更新能到的最小节点编号
            if (low[v] > dfn[u]) {
                bridge.emplace(u, v);
            }
        } else {
            low[u] = min(low[u], dfn[v]); // 更新能到的最小节点编号
        }
    }
}

// 因为 Tarjan 图不一定连通
// 遍历所有节点，所有未访问过的节点跑Tarjan
// tt = 0; 时间戳初始为 0
// tarjan_node(i, -1); 从第 i 个点开始
void tarjan_node(int u, int p) {
    low[u] = dfn[u] = ++tt;
    int child = 0;
    for (auto v: e[u]) {
        if (v == p) continue;
        if (dfn[v] == 0) {
            child++;
            tarjan_node(v, u);
            low[u] = min(low[u], low[v]); // 更新能到的最小节点编号
            if (p == -1 && child > 1) {
                node.insert(u);
            }
            else if (p != -1 && low[v] >= dfn[u]) {
                node.insert(u);
            }
        } else {
            low[u] = min(low[u], dfn[v]); // 更新能到的最小节点编号
        }
    }
}

const int N = 1e5 + 3;

int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp;
int scc[N], sc;  // 结点 i 所在 SCC 的编号
int sz[N];       // 强连通 i 的大小

void tarjan_scc(int u) {
    if (dfn[u]) return;
    low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
    for (auto v : e[u]) {
        if (!dfn[v]) {
            tarjan_scc(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        ++sc;
        while (s[tp] != u) {
            scc[s[tp]] = sc;
            sz[sc]++;
            in_stack[s[tp]] = 0;
            --tp;
        }
        scc[s[tp]] = sc;
        sz[sc]++;
        in_stack[s[tp]] = 0;
        --tp;
    }
}