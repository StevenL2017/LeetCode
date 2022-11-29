from typing import *
from collections import *

# 已知树结构，求N叉树K个节点的LCA
class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

def lca(root: TreeNode, nodes: List[TreeNode]) -> TreeNode:
    def dfs(root: Optional[TreeNode]) -> Generator[TreeNode, None, None]:
        if not root:
            return
        
        subtreeSum[root.val] += int(root in needs)
        
        for child in root.children:
            if not child:
                continue
            yield from dfs(child)
            subtreeSum[root.val] += subtreeSum[child.val]
                
        if subtreeSum[root.val] == len(nodes):
            yield root
                    
    needs = set(nodes)
    subtreeSum = defaultdict(int)
    return next(dfs(root))