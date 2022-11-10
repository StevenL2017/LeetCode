#include <string>
#include <vector>

using namespace std;

// fail数组
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

// 字符串最长公共前缀后缀的长度
int get_maxlen(string s) {
    int n = s.size();
    vector<int> fail(n + 1, -1);
    for (int i = 1, j = -1; i <= n; i++) {
        while (j >= 0 && s[j] != s[i - 1]) {
            j = fail[j];
        }
        fail[i] = ++j;
    }
    return fail[n];
}