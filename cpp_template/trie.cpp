#include <string>
#include <vector>

using namespace std;

class Trie {
private:
    vector<Trie*> children;
    bool isEnd;

public:
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