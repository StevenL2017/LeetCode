#include <vector>

using namespace std;

// 单点更新-区间元素和查询
class SegmentTree {
private:
    vector<int> sum;

public:
    SegmentTree(int n) {
        sum.resize(n * 4);
    }
    
    void update(int root, int l, int r, int idx, int val) {
        if (l == r) {
            sum[root] += val;
            return;
        }
        int m = (l + r) / 2;
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
        int m = (l + r) / 2;
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
        mx.resize(n * 4);
    }
    
    void update(int root, int l, int r, int idx, int val) {
        if (l == r) {
            mx[root] = val;
            return;
        }
        int m = (l + r) / 2;
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
        int ans = 0;
        int m = (l + r) / 2;
        if (L <= m) {
            ans = query(root * 2, l, m, L, R);
        }
        if (R > m) {
            ans = max(ans, query(root * 2 + 1, m + 1, r, L, R));
        }
        return ans;
    }
};