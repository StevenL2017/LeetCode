#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2e5 + 3;

// 建图（树）
vector<int> graph[MAXN];
vector<int> weight[MAXN];

// 深度 depth，祖先 f，代价 cost
int depth[MAXN];
int f[MAXN][31];
int cost[MAXN][31];

// 用来为 lca 算法做准备，编号 1 ~ n
void dfs(int node, int fa) {
    // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1
    f[node][0] = fa;
    depth[node] = depth[f[node][0]] + 1;
    // 初始化：其他的祖先节点：第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第
    // 2^(i-1) 的祖先节点
    for (int i = 1; i < 31; i++) {
        f[node][i] = f[f[node][i - 1]][i - 1];
    }
    // 遍历子节点来进行 dfs
    int sz = graph[node].size();
    for (int i = 0; i < sz; i++) {
        if (graph[node][i] == fa) continue;
        dfs(graph[node][i], node);
    }
}

// 用倍增算法算 x 和 y 的 lca 节点
int lca(int x, int y) {
    // 令 y 比 x 深
    if (depth[x] > depth[y]) swap(x, y);
    // 令 y 和 x 在一个深度
    int tmp = depth[y] - depth[x];
    for (int j = 0; tmp; j++, tmp >>= 1) {
        if (tmp & 1) y = f[y][j];
    }
    // 如果这个时候 y = x，那么 x，y 就都是它们自己的祖先
    if (y == x) return y;
    // 不然的话，找到第一个不是它们祖先的两个点
    for (int j = 30; j >= 0 && y != x; j--) {
        if (f[x][j] != f[y][j]) {
            x = f[x][j];
            y = f[y][j];
        }
    }
    // 返回结果
    return y == x ? y : f[y][0];
}

int find_pth_parent(int x, int p) {
    for (int i = 0; i < 31; i++) {
        if (p >> i & 1) {
            x = f[x][i];
        }
    }
    return x;
}

// 用来为 lca_sum 算法做准备，编号 1 ~ n
void dfs_sum(int node, int fa) {
    // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1
    f[node][0] = fa;
    depth[node] = depth[f[node][0]] + 1;
    // 初始化：其他的祖先节点：第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第
    // 2^(i-1) 的祖先节点
    for (int i = 1; i < 31; i++) {
        f[node][i] = f[f[node][i - 1]][i - 1];
        cost[node][i] = cost[f[node][i - 1]][i - 1] + cost[node][i - 1];
    }
    // 遍历子节点来进行 dfs
    int sz = graph[node].size();
    for (int i = 0; i < sz; i++) {
        if (graph[node][i] == fa) continue;
        cost[graph[node][i]][0] = weight[node][i];
        dfs_sum(graph[node][i], node);
    }
}

// 用倍增算法算 x 和 y 之间的边权和
int lca_sum(int x, int y) {
    // 令 y 比 x 深
    if (depth[x] > depth[y]) swap(x, y);
    // 令 y 和 x 在一个深度
    int tmp = depth[y] - depth[x], ans = 0;
    for (int j = 0; tmp; j++, tmp >>= 1) {
        if (tmp & 1) ans += cost[y][j], y = f[y][j];
    }
    // 如果这个时候 y = x，那么 x，y 就都是它们自己的祖先
    if (y == x) return ans;
    // 不然的话，找到第一个不是它们祖先的两个点
    for (int j = 30; j >= 0 && y != x; j--) {
        if (f[x][j] != f[y][j]) {
            ans += cost[x][j] + cost[y][j];
            x = f[x][j];
            y = f[y][j];
        }
    }
    // 返回结果
    ans += cost[x][0] + cost[y][0];
    return ans;
}

// 用来为 lca_max 算法做准备，编号 1 ~ n
void dfs_max(int node, int fa) {
    // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1
    f[node][0] = fa;
    depth[node] = depth[f[node][0]] + 1;
    // 初始化：其他的祖先节点：第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第
    // 2^(i-1) 的祖先节点
    for (int i = 1; i < 31; i++) {
        f[node][i] = f[f[node][i - 1]][i - 1];
        cost[node][i] = max(cost[f[node][i - 1]][i - 1], cost[node][i - 1]);
    }
    // 遍历子节点来进行 dfs
    int sz = graph[node].size();
    for (int i = 0; i < sz; i++) {
        if (graph[node][i] == fa) continue;
        cost[graph[node][i]][0] = weight[node][i];
        dfs_max(graph[node][i], node);
    }
}

// 用倍增算法算 x 和 y 之间的边权最大值
int lca_max(int x, int y) {
    // 令 y 比 x 深
    if (depth[x] > depth[y]) swap(x, y);
    // 令 y 和 x 在一个深度
    int tmp = depth[y] - depth[x], ans = 0;
    for (int j = 0; tmp; j++, tmp >>= 1) {
        if (tmp & 1) ans = max(ans, cost[y][j]), y = f[y][j];
    }
    // 如果这个时候 y = x，那么 x，y 就都是它们自己的祖先
    if (y == x) return ans;
    // 不然的话，找到第一个不是它们祖先的两个点
    for (int j = 30; j >= 0 && y != x; j--) {
        if (f[x][j] != f[y][j]) {
            ans = max({ans, cost[x][j], cost[y][j]});
            x = f[x][j];
            y = f[y][j];
        }
    }
    // 返回结果
    ans = max({ans, cost[x][0], cost[y][0]});
    return ans;
}