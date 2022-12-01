#include <vector>

using namespace std;

const long long INF_LL = (1ll << 60);

long long n_div(long long a, long long b) {
    long long r = (a % b + b) % b;
    return (a - r) / b;
}

long long c_div(long long a, long long b) {
    return n_div(a + b - 1, b);
}

// 求最小值：直线按斜率降序添加，二分求最小值
struct CHT {
private:
    struct line {
        long long k, b;

        long long operator() (long long x) const {
            return k * x + b;
        }

        long long operator& (const line& o) const {
            long long v1 = b - o.b, v2 = o.k - k;
            if (v2 < 0) {
                v1 *= -1;
                v2 *= -1;
            }
            return c_div(v1, v2);
        }
    };

    vector<line> f;
    vector<long long> g;

public:
    void add_line(const line& l) {
        while (!f.empty() && (f.back() & l) <= g.back()) {
            f.pop_back();
            g.pop_back();
        }
        if (f.empty()) g.push_back(-INF_LL);
        else g.push_back(f.back() & l);
        f.push_back(l);
    }

    long long get_min(long long x) {
        int l = 0, r = (int)g.size();
        while (l + 1 < r) {
            int m = l + (r - l) / 2;
            if (g[m] <= x) {
                l = m;
            } else {
                r = m;
            }
        }
        return f[l](x);
    }
};