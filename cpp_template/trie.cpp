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
class Trie {
public:
    int L;
    Trie* left;
    Trie* right;
    long long cnt;

    Trie() : L(31), left(nullptr), right(nullptr), cnt(0) {}

    void insert(long long val) {
        Trie* node = this;
        for (int i = L; i >= 0; i--) {
            if (!(val >> i & 1)) {
                if (node->left == nullptr) {
                    node->left = new Trie();
                }
                node = node->left;
            } else {
                if (node->right == nullptr) {
                    node->right = new Trie();
                }
                node = node->right;
            }
            node->cnt++;
        }
    }

    long long query_maxor(long long val) {
        Trie* node = this;
        long long ans = 0;
        for (int i = L; i >= 0; i--) {
            if (node == nullptr) {
                return ans;
            }
            if (val >> i & 1) {
                if (node->left != nullptr) {
                    ans |= 1ll << i;
                    node = node->left;
                } else {
                    node = node->right;
                }
            } else {
                if (node->right != nullptr) {
                    ans |= 1ll << i;
                    node = node->right;
                } else {
                    node = node->left;
                }
            }
        }
        return ans;
    }

    long long query_cnt(long long val, long long limit) {
        // 严格小于limit的数对异或值数量
        Trie* node = this;
        long long ans = 0;
        for (int i = L; i >= 0; i--) {
            if (node == nullptr) {
                break;
            }
            auto cur = val >> i & 1;
            if (limit >> i & 1) {
                if (!cur && node->left != nullptr) {
                    ans += node->left->cnt;
                }
                if (cur && node->right != nullptr) {
                    ans += node->right->cnt;
                }
                if (cur) node = node->left;
                else node = node->right;
            } else {
                if (!cur) node = node->left;
                else node = node->right;
            }
        }
        return ans;
    }

    void remove(long long val) {
        Trie* node = this;
        for (int i = L; i >= 0; i--) {
            if (val >> i & 1) {
                node = node->right;
            } else {
                node = node->left;
            }
            node->cnt--;
        }
    }
};