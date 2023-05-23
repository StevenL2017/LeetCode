#include <string>
#include <vector>

using namespace std;

// 数组实现字母字典树
class Trie {
public:
    vector<Trie*> children;
    bool isEnd;

    Trie() : children(26), isEnd(false) {}

    void insert(string word) {
        Trie* node = this;
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    bool query(string word) {
        Trie* node = this->query_prefix(word);
        return node != nullptr && node->isEnd;
    }

    Trie* query_prefix(string prefix) {
        Trie* node = this;
        for (char ch : prefix) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                return nullptr;
            }
            node = node->children[ch];
        }
        return node;
    }
};

// 0-1字典树
const int K = 31;

class Trie {
public:
    vector<Trie*> children;
    int cnt;

    Trie() : children(2), cnt(0) {}

    void insert(int val) {
        Trie* node = this;
        for (int i = K; i >= 0; i--) {
            int bit = val >> i & 1;
            if (node->children[bit] == nullptr) {
                node->children[bit] = new Trie();
            }
            node = node->children[bit];
            node->cnt++;
        }
    }

    int query_maxor(int val) {
        int ans = 0;
        Trie* node = this;
        for (int i = K; i >= 0; i--) {
            int bit = val >> i & 1;
            if (node->children[bit ^ 1] != nullptr) {
                ans |= 1 << i;
                bit ^= 1;
            }
            if (node->children[bit] == nullptr) {
                return ans;
            }
            node = node->children[bit];
        }
        return ans;
    }

    // 小于等于limit的数对异或值数量
    int query_le(int val, int limit) {
        int ans = 0;
        Trie* node = this;
        for (int i = K; i >= 0; i--) {
            int bit = val >> i & 1;
            if (limit >> i & 1) {
                if (node->children[bit] != nullptr) {
                    ans += node->children[bit]->cnt;
                }
                if (node->children[bit ^ 1] == nullptr) {
                    return ans;
                }
                node = node->children[bit ^ 1];
            } else {
                if (node->children[bit] == nullptr) {
                    return ans;
                }
                node = node->children[bit];
            }
        }
        ans += node->cnt; // 等于的情况
        return ans;
    }

    void remove(int val) {
        Trie* node = this;
        for (int i = K; i >= 0; i--) {
            int bit = val >> i & 1;
            node->children[bit]->cnt--;
            if (node->children[bit]->cnt == 0) {
                node->children[bit] = nullptr;
                break;
            }
            node = node->children[bit];
        }
    }
};