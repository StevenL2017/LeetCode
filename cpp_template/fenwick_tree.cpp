#include <iostream>
#include <algorithm>

using namespace std;

class BIT {
private:
    int minv, maxv, N;
    long long all;
    long long *tr;
    
public:
    // 给定定义域 [minv, maxv], 初始化一个树状数组
    BIT(int minv, int maxv) :
        minv(minv), maxv(maxv), N(maxv - minv + 2), all(0) {
        if (minv > maxv) {
            cout << "BIT Init: Value Range Invalid!" << endl;
        } else {
            tr = new long long[N]();
        }
    }
    
    ~BIT() {
        delete[] tr;
    }
    
    void add(int x, long long v) {
        if (x < minv || x > maxv) {
            cout << "Add: Index Invalid!" << endl;
        } else {
            all += v;
            x = x - minv + 1;
            while (x < N) {
                tr[x] += v;
                x += x & -x;
            }
        }
    }
    
    // 求小于等于 x 的值的和
    // 如果求小于，那么用 query_LE(x - 1)
    long long query_LE(int x) {
        x = max(0, min(x - minv + 1, N - 1));
        long long ret = 0;
        while (x) {
            ret += tr[x];
            x -= x & -x;
        }
        return ret;
    }

    // 求大于等于 x 的值的和
    // 如果求大于，那么用 query_BE(x + 1)
    long long query_BE(int x) {
        x = max(0, min(x - minv + 1, N - 1));
        return all - query_LE(x - 1);
    }
};