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
class Trie:
    def __init__(self):
        self.L = 31
        self.left = None
        self.right = None
        self.cnt = 0
        
    def insert(self, val: int) -> None:
        node = self
        for i in range(self.L, -1, -1):
            if not val & (1 << i):
                if not node.left:
                    node.left = Trie()
                node = node.left
            else:
                if not node.right:
                    node.right = Trie()
                node = node.right
            node.cnt += 1
    
    def query_maxor(self, val: int) -> int:
        node = self
        ans = 0
        for i in range(self.L, -1, -1):
            if val & (1 << i):
                if node.left and node.left.cnt:
                    ans |= (1 << i)
                    node = node.left
                else:
                    node = node.right
            else:
                if node.right and node.right.cnt:
                    ans |= (1 << i)
                    node = node.right
                else:
                    node = node.left
        return ans
    
    def query_cnt(self, val: int, limit: int) -> int:
        # 严格小于limit的数对异或值数量
        node = self
        ans = 0
        for i in range(self.L, -1, -1):
            if node is None:
                break
            cur = val & (1 << i)
            if limit & (1 << i):
                if not cur and node.left:
                    ans += node.left.cnt
                if cur and node.right:
                    ans += node.right.cnt
                node = node.left if cur else node.right
            else:
                node = node.left if not cur else node.right
        return ans
    
    def remove(self, val: int) -> None:
        node = self
        for i in range(self.L, -1, -1):
            if not val & (1 << i):
                node = node.left
            else:
                node = node.right
            node.cnt -= 1