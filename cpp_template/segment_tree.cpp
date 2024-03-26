#include <climits>
#include <vector>
#include <numeric>

using namespace std;

// 单点更新-区间元素和查询
class SegmentTree {
private:
    vector<int> sum;

public:
    SegmentTree(int n) {
        sum.resize(n * 4, 0);
    }
    
    void update(int root, int l, int r, int idx, int val) {
        if (l == r) {
            sum[root] += val;
            return;
        }
        int m = l + (r - l) / 2;
        if (idx <= m) {
            update(root * 2, l, m, idx, val);
        } else {
            update(root * 2 + 1, m + 1, r, idx, val);
        }
        sum[root] = sum[root * 2] + sum[root * 2 + 1];
    }
    
    long long query(int root, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return sum[root];
        }
        long long tot = 0LL;
        int m = l + (r - l) / 2;
        if (L <= m) {
            tot += query(root * 2, l, m, L, R);
        }
        if (R > m) {
            tot += query(root * 2 + 1, m + 1, r, L, R);
        }
        return tot;
    }
};

// 单点更新-区间最大值查询
class SegmentTree {
private:
    vector<int> mx;

public:
    SegmentTree(int n) {
        mx.resize(n * 4, -2e9);
    }
    
    void update(int root, int l, int r, int idx, int val) {
        if (l == r) {
            mx[root] = val;
            return;
        }
        int m = l + (r - l) / 2;
        if (idx <= m) {
            update(root * 2, l, m, idx, val);
        } else {
            update(root * 2 + 1, m + 1, r, idx, val);
        }
        mx[root] = max(mx[root * 2], mx[root * 2 + 1]);
    }
    
    int query(int root, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return mx[root];
        }
        int ans = -2e9;
        int m = l + (r - l) / 2;
        if (L <= m) {
            ans = query(root * 2, l, m, L, R);
        }
        if (R > m) {
            ans = max(ans, query(root * 2 + 1, m + 1, r, L, R));
        }
        return ans;
    }
};

// 单点更新-区间最小值查询
class SegmentTree {
private:
    vector<int> mn;

public:
    SegmentTree(int n) {
        mn.resize(n * 4, 2e9);
    }
    
    void update(int root, int l, int r, int idx, int val) {
        if (l == r) {
            mn[root] = val;
            return;
        }
        int m = l + (r - l) / 2;
        if (idx <= m) {
            update(root * 2, l, m, idx, val);
        } else {
            update(root * 2 + 1, m + 1, r, idx, val);
        }
        mn[root] = min(mn[root * 2], mn[root * 2 + 1]);
    }
    
    int query(int root, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return mn[root];
        }
        int ans = 2e9;
        int m = l + (r - l) / 2;
        if (L <= m) {
            ans = query(root * 2, l, m, L, R);
        }
        if (R > m) {
            ans = min(ans, query(root * 2 + 1, m + 1, r, L, R));
        }
        return ans;
    }
};

// 单点更新-区间GCD查询
class SegmentTree {
private:
    vector<int> g;

public:
    SegmentTree(int n) {
        g.resize(n * 4, 0);
    }
    
    void update(int root, int l, int r, int idx, int val) {
        if (l == r) {
            g[root] = val;
            return;
        }
        int m = l + (r - l) / 2;
        if (idx <= m) {
            update(root * 2, l, m, idx, val);
        } else {
            update(root * 2 + 1, m + 1, r, idx, val);
        }
        g[root] = gcd(g[root * 2], g[root * 2 + 1]);
    }
    
    int query(int root, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return g[root];
        }
        int ans = 0;
        int m = l + (r - l) / 2;
        if (L <= m) {
            ans = gcd(ans, query(root * 2, l, m, L, R));
        }
        if (R > m) {
            ans = gcd(ans, query(root * 2 + 1, m + 1, r, L, R));
        }
        return ans;
    }
};

// 单点更新-自定义结点

// 单个元素修改为某值 + 区间求和
const int N = 2e5 + 3;

int a[N];

struct Node {
    int val = 0;
};

class SegmentTree {
private:
    vector<Node> s;

public:
    SegmentTree() {}

    SegmentTree(int n) {
        s.resize(n * 4);
        build(1, 1, n);
    }

    Node merge(const Node& u, const Node& v) {
        Node p;
        p.val = u.val + v.val;
        return p;
    }

    void build(int root, int l, int r) {
        if (l == r) {
            s[root].val = a[l];
            return;
        }
        int m = l + (r - l) / 2;
        build(root * 2, l, m);
        build(root * 2 + 1, m + 1, r);
        s[root] = merge(s[root * 2], s[root * 2 + 1]);
    }
    
    void update(int root, int l, int r, int idx, int val) {
        if (l == r) {
            s[root].val = val;
            return;
        }
        int m = l + (r - l) / 2;
        if (idx <= m) {
            update(root * 2, l, m, idx, val);
        } else {
            update(root * 2 + 1, m + 1, r, idx, val);
        }
        s[root] = merge(s[root * 2], s[root * 2 + 1]);
    }
    
    Node query(int root, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return s[root];
        }
        int m = l + (r - l) / 2;
        if (R <= m) {
            return query(root * 2, l, m, L, R);
        }
        if (L > m) {
            return query(root * 2 + 1, m + 1, r, L, R);
        }
        return merge(query(root * 2, l, m, L, R), query(root * 2 + 1, m + 1, r, L, R));
    }
};

// 区间更新-自定义结点
// 范围为左闭右闭区间

// 区间每个元素加上某值 + 区间求和
const int N = 2e5 + 3;

int a[N];

struct Node {
    int l = 0, r = 0;
    long long val = 0, lazy = 0;
};

class SegmentTree {
private:
    vector<Node> s;

public:
    SegmentTree() {}

    SegmentTree(int n) {
        s.resize(n * 4);
        build(1, 1, n);
    }

    void push(int root) {
        auto l = s[root].l, r = s[root].r;
        if (l != r && s[root].lazy) {
            auto m = l + (r - l) / 2;
            s[root * 2].val += s[root].lazy * (m - l + 1);
            s[root * 2].lazy += s[root].lazy;
            s[root * 2 + 1].val += s[root].lazy * (r - m);
            s[root * 2 + 1].lazy += s[root].lazy;
            s[root].lazy = 0;
        }
    }

    void merge(int root) {
        s[root].val = s[root * 2].val + s[root * 2 + 1].val;
    }

    void build(int root, int l, int r) {
        s[root].l = l, s[root].r = r;
        if (l == r) {
            s[root].val = a[l];
            return;
        }
        int m = l + (r - l) / 2;
        build(root * 2, l, m);
        build(root * 2 + 1, m + 1, r);
        merge(root);
    }
    
    void update(int root, int L, int R, int val) {
        auto l = s[root].l, r = s[root].r;
        if (L <= l && r <= R) {
            s[root].val += val * (r - l + 1);
            s[root].lazy += val;
            return;
        }
        push(root);
        int m = l + (r - l) / 2;
        if (L <= m) update(root * 2, L, R, val);
        if (R > m) update(root * 2 + 1, L, R, val);
        merge(root);
    }
    
    long long query(int root, int L, int R) {
        auto l = s[root].l, r = s[root].r;
        if (L <= l && r <= R) {
            return s[root].val;
        }
        push(root);
        long long ans = 0;
        int m = l + (r - l) / 2;
        if (L <= m) ans += query(root * 2, L, R);
        if (R > m) ans += query(root * 2 + 1, L, R);
        return ans;
    }
};

// 区间每个元素修改为某值 + 区间求和
const int N = 2e5 + 3;

int a[N];

struct Node {
    int l = 0, r = 0;
    long long val = 0, lazy = 0;
};

class SegmentTree {
private:
    vector<Node> s;

public:
    SegmentTree() {}

    SegmentTree(int n) {
        s.resize(n * 4);
        build(1, 1, n);
    }

    void push(int root) {
        auto l = s[root].l, r = s[root].r;
        if (l != r && s[root].lazy) {
            auto m = l + (r - l) / 2;
            s[root * 2].val = s[root].lazy * (m - l + 1);
            s[root * 2].lazy = s[root].lazy;
            s[root * 2 + 1].val = s[root].lazy * (r - m);
            s[root * 2 + 1].lazy = s[root].lazy;
            s[root].lazy = 0;
        }
    }

    void merge(int root) {
        s[root].val = s[root * 2].val + s[root * 2 + 1].val;
    }

    void build(int root, int l, int r) {
        s[root].l = l, s[root].r = r;
        if (l == r) {
            s[root].val = a[l];
            return;
        }
        int m = l + (r - l) / 2;
        build(root * 2, l, m);
        build(root * 2 + 1, m + 1, r);
        merge(root);
    }
    
    void update(int root, int L, int R, int val) {
        auto l = s[root].l, r = s[root].r;
        if (L <= l && r <= R) {
            s[root].val = val * (r - l + 1);
            s[root].lazy = val;
            return;
        }
        push(root);
        int m = l + (r - l) / 2;
        if (L <= m) update(root * 2, L, R, val);
        if (R > m) update(root * 2 + 1, L, R, val);
        merge(root);
    }
    
    long long query(int root, int L, int R) {
        auto l = s[root].l, r = s[root].r;
        if (L <= l && r <= R) {
            return s[root].val;
        }
        push(root);
        long long ans = 0;
        int m = l + (r - l) / 2;
        if (L <= m) ans += query(root * 2, L, R);
        if (R > m) ans += query(root * 2 + 1, L, R);
        return ans;
    }
};

// 区间每个元素0/1反转 + 区间求和
struct Node {
    int l = 0, r = 0;
    int val = 0, lazy = 0;
};

class SegmentTree {
private:
    vector<Node> s;

public:
    SegmentTree() {}

    SegmentTree(int n) {
        s.resize(n * 4);
        build(1, 1, n);
    }

    void push(int root) {
        auto l = s[root].l, r = s[root].r;
        if (l != r && s[root].lazy) {
            auto m = l + (r - l) / 2;
            s[root * 2].val = (m - l + 1) - s[root * 2].val;
            s[root * 2].lazy ^= 1;
            s[root * 2 + 1].val = (r - m) - s[root * 2 + 1].val;
            s[root * 2 + 1].lazy ^= 1;
            s[root].lazy = 0;
        }
    }

    void merge(int root) {
        s[root].val = s[root * 2].val + s[root * 2 + 1].val;
    }

    void build(int root, int l, int r) {
        s[root].l = l, s[root].r = r;
        if (l == r) {
            s[root].val = 0;
            return;
        }
        int m = l + (r - l) / 2;
        build(root * 2, l, m);
        build(root * 2 + 1, m + 1, r);
        merge(root);
    }
    
    void update(int root, int L, int R) {
        auto l = s[root].l, r = s[root].r;
        if (L <= l && r <= R) {
            s[root].val = (r - l + 1) - s[root].val;
            s[root].lazy ^= 1;
            return;
        }
        push(root);
        int m = l + (r - l) / 2;
        if (L <= m) update(root * 2, L, R);
        if (R > m) update(root * 2 + 1, L, R);
        merge(root);
    }
    
    int query(int root, int L, int R) {
        auto l = s[root].l, r = s[root].r;
        if (L <= l && r <= R) {
            return s[root].val;
        }
        push(root);
        int ans = 0;
        int m = l + (r - l) / 2;
        if (L <= m) ans += query(root * 2, L, R);
        if (R > m) ans += query(root * 2 + 1, L, R);
        return ans;
    }
};

// 区间每个元素修改为某值（不等于0） + 区间求最小值
const int N = 2e5 + 3;

int a[N];

struct Node {
    int l = 0, r = 0;
    long long val = LLONG_MAX, lazy = 0;
};

class SegmentTree {
private:
    vector<Node> s;

public:
    SegmentTree() {}

    SegmentTree(int n) {
        s.resize(n * 4);
        build(1, 1, n);
    }

    void push(int root) {
        auto l = s[root].l, r = s[root].r;
        if (l != r && s[root].lazy != 0) {
            auto m = l + (r - l) / 2;
            s[root * 2].val = s[root].lazy;
            s[root * 2].lazy = s[root].lazy;
            s[root * 2 + 1].val = s[root].lazy;
            s[root * 2 + 1].lazy = s[root].lazy;
            s[root].lazy = 0;
        }
    }

    void merge(int root) {
        s[root].val = min(s[root * 2].val, s[root * 2 + 1].val);
    }

    void build(int root, int l, int r) {
        s[root].l = l, s[root].r = r;
        if (l == r) {
            s[root].val = a[l];
            return;
        }
        int m = l + (r - l) / 2;
        build(root * 2, l, m);
        build(root * 2 + 1, m + 1, r);
        merge(root);
    }
    
    void update(int root, int L, int R, int val) {
        auto l = s[root].l, r = s[root].r;
        if (L <= l && r <= R) {
            s[root].val = val;
            s[root].lazy = val;
            return;
        }
        push(root);
        int m = l + (r - l) / 2;
        if (L <= m) update(root * 2, L, R, val);
        if (R > m) update(root * 2 + 1, L, R, val);
        merge(root);
    }
    
    long long query(int root, int L, int R) {
        auto l = s[root].l, r = s[root].r;
        if (L <= l && r <= R) {
            return s[root].val;
        }
        push(root);
        long long ans = LLONG_MAX;
        int m = l + (r - l) / 2;
        if (L <= m) ans = min(ans, query(root * 2, L, R));
        if (R > m) ans = min(ans, query(root * 2 + 1, L, R));
        return ans;
    }
};

// 子树更新-子树状态查询
const int N = 5e5 + 3;

vector<int> graph[N];
int status[N], pos[N], tin[N], tout[N];
int tt = 1;

// tin[node] 和 tout[node] 为左闭右开区间
// tt 初始化为 1 使得线段树根节点为 1
void dfs(int node, int fa) {
    pos[tt] = node;
    tin[node] = tt++;
    for (auto& nxt: graph[node]) {
        if (nxt == fa) continue;
        dfs(nxt, node);
    }
    tout[node] = tt;
}

// 区间每个元素修改为某值 + 区间求状态值
class SegmentTree {
private:
    vector<long long> s; // 存储节点所代表的子树的状态值，从下到上merge状态
    vector<long long> lazy; // 存储节点所代表的子树的懒更新值，从上到下push更新值

public:
    SegmentTree() {}
    
    SegmentTree(int n) {
        s.resize(n * 4);
        lazy.resize(n * 4);
    }

    void push(int root) {
        if (lazy[root] == -1) return;
        for (int i = 0; i < 2; i++) {
            s[root * 2 + i] = lazy[root * 2 + i] = lazy[root];
        }
        lazy[root] = -1;
    }

    void merge(int root) {
        s[root] = s[root * 2] | s[root * 2 + 1];
    }

    void build(int root, int l, int r) {
        lazy[root] = -1;
        if (l + 1 == r) {
            s[root] = 1ll << status[pos[l]];
            return;
        }
        int m = l + (r - l) / 2;
        build(root * 2, l, m);
        build(root * 2 + 1, m, r);
        merge(root);
    }
    
    void update(int root, int l, int r, int L, int R, int val) {
        if (L >= R) return;
        if (L == l && r == R) {
            s[root] = 1ll << val;
            lazy[root] = 1ll << val;
            return;
        }
        push(root);
        int m = l + (r - l) / 2;
        update(root * 2, l, m, L, min(m, R), val);
        update(root * 2 + 1, m, r, max(m, L), R, val);
        merge(root);
    }
    
    long long query(int root, int l, int r, int L, int R) {
        if (L >= R) return 0;
        if (L == l && r == R) {
            return s[root];
        }
        push(root);
        long long ans = 0;
        int m = l + (r - l) / 2;
        ans |= query(root * 2, l, m, L, min(m, R));
        ans |= query(root * 2 + 1, m, r, max(m, L), R);
        return ans;
    }
};