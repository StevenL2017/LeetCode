# 数组实现字母字典树
class Trie:
    def __init__(self):
        self.children = [None] * 26
        self.isEnd = False
        
    def insert(self, word: str) -> None:
        node = self
        for ch in word:
            ch = ord(ch) - ord("a")
            if not node.children[ch]:
                node.children[ch] = Trie()
            node = node.children[ch]
        node.isEnd = True
    
    def query(self, word: str) -> bool:
        node = self.query_prefix(word)
        return node is not None and node.isEnd
        
    def query_prefix(self, prefix: str) -> "Trie":
        node = self
        for ch in prefix:
            ch = ord(ch) - ord("a")
            if not node.children[ch]:
                return None
            node = node.children[ch]
        return node

# 0-1字典树
HIGH_BIT = 31

class Trie:
    def __init__(self):
        self.children = [None] * 2
        self.cnt = 0
    
    def insert(self, val: int) -> None:
        node = self
        for i in range(HIGH_BIT, -1, -1):
            bit = val >> i & 1
            if not node.children[bit]:
                node.children[bit] = Trie()
            node = node.children[bit]
            node.cnt += 1
    
    def query_maxor(self, val: int) -> int:
        ans = 0
        node = self
        for i in range(HIGH_BIT, -1, -1):
            bit = val >> i & 1
            if node.children[bit ^ 1]:
                ans |= 1 << i
                bit ^= 1
            if not node.children[bit]:
                return ans
            node = node.children[bit]
        return ans
    
    # 小于等于limit的数对异或值数量
    def query_le(self, val: int, limit: int) -> int:
        ans = 0
        node = self
        for i in range(HIGH_BIT, -1, -1):
            bit = val >> i & 1
            if limit >> i & 1:
                if node.children[bit]:
                    ans += node.children[bit].cnt
                if not node.children[bit ^ 1]:
                    return ans
                node = node.children[bit ^ 1]
            else:
                if not node.children[bit]:
                    return ans
                node = node.children[bit]
        ans += node.cnt # 等于的情况
        return ans
    
    def remove(self, val: int) -> None:
        node = self
        for i in range(HIGH_BIT, -1, -1):
            bit = val >> i & 1
            node.children[bit].cnt -= 1
            if node.children[bit].cnt == 0:
                node.children[bit] = None
                break
            node = node.children[bit]