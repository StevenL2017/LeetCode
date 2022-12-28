#include <string>
#include <vector>

using namespace std;

// fail数组(下标)
vector<int> get_fail(string s) {
    int n = s.size();
    vector<int> fail(n, -1);
    for (int i = 1; i < n; i++) {
        auto j = fail[i - 1];
        while (j != -1 && s[j + 1] != s[i]) {
            j = fail[j];
        }
        if (s[j + 1] == s[i]) {
            fail[i] = j + 1;
        }
    }
    return fail;
}

// KMP算法(下标)
int kmp(string query, string pattern) {
    int n = query.size(), m = pattern.size();
    auto fail = get_fail(pattern);
    int j = -1;
    for (int i = 0; i < n; i++) {
        while (j != -1 && pattern[j + 1] != query[i]) {
            j = fail[j];
        }
        if (pattern[j + 1] == query[i]) {
            j++;
            if (j == m - 1) {
                return i - m + 1;
            }
        }
    }
    return -1;
}

// fail数组(字符串最长公共前缀后缀的长度)
vector<int> get_fail(string s) {
    int n = s.size();
    vector<int> fail(n + 1, -1);
    for (int i = 1, j = -1; i <= n; i++) {
        while (j >= 0 && s[j] != s[i - 1]) {
            j = fail[j];
        }
        fail[i] = ++j;
    }
    return fail;
}

// KMP算法(字符串最长公共前缀后缀的长度)
int kmp(string query, string pattern) {
    int n = query.size(), m = pattern.size();
    auto fail = get_fail(pattern);
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && pattern[j] != query[i]) {
            j = fail[j];
        }
        if (pattern[j] == query[i]) {
            j++;
            if (j == m) {
                return i - m + 1;
            }
        }
    }
    return -1;
}

// Z函数(字符串s[i]开头的后缀与本字符串的最长公共前缀)
vector<int> z_func(string& s) {
    int n = s.size(), L = -1, R = -1;
    vector<int> z(n);
    z[0] = n;
    for(int i = 1; i < n; i++) {
        if(i <= R)
            z[i] = min(z[i - L], R - i + 1);
        while(i + z[i] < n && s[i + z[i]] == s[z[i]])
            z[i]++;
        if(i + z[i] - 1 > R) {
            L = i;
            R = i + z[i] - 1;
        }
    }
    return z;
}