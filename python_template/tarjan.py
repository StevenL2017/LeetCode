from typing import *
from collections import *

# Tarjan算法割边
def tarjan_edge(n, edges):
    graph = defaultdict(set)
    for a, b in edges:
        graph[a].add(b)
        graph[b].add(a)

    dfn = [0] * n
    low = [0] * n
    t = 1
    res = []
    def tarjan(x: int, parent: int) -> None:
        nonlocal t
        dfn[x] = t
        low[x] = t
        t += 1

        for y in graph[x]:
            if y == parent:
                continue
            if dfn[y] == 0:
                tarjan(y, x)
                low[x] = min(low[x], low[y])
                if low[y] > dfn[x]:
                    res.append([x, y])
            else:
                low[x] = min(low[x], dfn[y])
                
    tarjan(0, -1)
    return res

# Tarjan算法割点
def tarjan_node(n, edges):
    graph = defaultdict(set)
    for a, b in edges:
        graph[a].add(b)
        graph[b].add(a)

    dfn = [0] * n
    low = [0] * n
    t = 1
    res = set()
    def tarjan(x: int, parent: int) -> None:
        nonlocal t
        dfn[x] = t
        low[x] = t
        t += 1
        child = 0
        for y in graph[x]:
            if y == parent:
                continue
            if dfn[y] == 0:
                child += 1
                tarjan(y, x)
                low[x] = min(low[x], low[y])
                if parent == -1 and child > 1:
                    res.add(x)
                elif parent != -1 and low[y] >= dfn[x]:
                    res.add(x)
            else:
                low[x] = min(low[x], dfn[y])
                
    tarjan(0, -1)
    return res

# Tarjan算法综合
class Tarjan:
    INF = int(1e20)

    @staticmethod
    def getSCC(
        n: int, adj: dict[int, set[int]]
    ) -> tuple[int, dict[int, set[int]], list[int]]:
        """Tarjan求解有向图的强连通分量

        Args:
            n (int): 结点0-n-1
            adj (dict[int, set[int]]): 图

        Returns:
            tuple[int, dict[int, set[int]], list[int]]: SCC的数量、分组、每个结点对应的SCC编号
        """

        def dfs(cur: int) -> None:
            nonlocal dfsId, SCCId
            if visited[cur]:
                return
            visited[cur] = True

            dfn[cur] = low[cur] = dfsId
            dfsId += 1
            stack.append(cur)
            inStack[cur] = True

            for nxt in adj[cur]:
                if not visited[nxt]:
                    dfs(nxt)
                    low[cur] = min(low[cur], low[nxt])
                elif inStack[nxt]:
                    low[cur] = min(low[cur], dfn[nxt])

            if dfn[cur] == low[cur]:
                while stack:
                    top = stack.pop()
                    inStack[top] = False
                    SCCGroupById[SCCId].add(top)
                    SCCIdByNode[top] = SCCId
                    if top == cur:
                        break
                SCCId += 1

        dfsId = 0
        dfn, low = [Tarjan.INF] * n, [Tarjan.INF] * n

        visited = [False] * n
        stack = []
        inStack = [False] * n

        SCCId = 0
        SCCGroupById = defaultdict(set)
        SCCIdByNode = [-1] * n

        for cur in range(n):
            if not visited[cur] and not inStack[cur]:
                dfs(cur)

        return SCCId, SCCGroupById, SCCIdByNode

    @staticmethod
    def getCuttingPointAndCuttingEdge(
        n: int, adjMap: DefaultDict[int, Set[int]]
    ) -> Tuple[Set[int], Set[Tuple[int, int]]]:
        """Tarjan求解无向图的割点和割边(桥)

        Args:
            n (int): 结点0-n-1
            adjMap (DefaultDict[int, Set[int]]): 图

        Returns:
            Tuple[Set[int], Set[Tuple[int, int]]]: 割点、桥

        - 边对 (u,v) 中 u < v
        """

        def dfs(cur: int, parent: int) -> None:
            nonlocal dfsId
            if visited[cur]:
                return
            visited[cur] = True

            order[cur] = low[cur] = dfsId
            dfsId += 1

            dfsChild = 0
            for next in adjMap[cur]:
                if next == parent:
                    continue
                if not visited[next]:
                    dfsChild += 1
                    dfs(next, cur)
                    low[cur] = min(low[cur], low[next])
                    if low[next] > order[cur]:
                        cuttingEdge.add(tuple(sorted([cur, next])))
                    if parent != -1 and low[next] >= order[cur]:
                        cuttingPoint.add(cur)
                    elif parent == -1 and dfsChild > 1:  # 出发点没有祖先啊，所以特判一下
                        cuttingPoint.add(cur)
                else:
                    low[cur] = min(low[cur], order[next])  # 注意这里是order

        dfsId = 0
        order, low = [Tarjan.INF] * n, [Tarjan.INF] * n
        visited = [False] * n

        cuttingPoint = set()
        cuttingEdge = set()

        for i in range(n):
            if not visited[i]:
                dfs(i, -1)

        return cuttingPoint, cuttingEdge

    @staticmethod
    def getVBCC(
        n: int, adjMap: DefaultDict[int, Set[int]]
    ) -> Tuple[int, DefaultDict[int, Set[int]], List[Set[int]]]:
        """Tarjan求解无向图的点双连通分量

        Args:
            n (int): 结点0-n-1
            adjMap (DefaultDict[int, Set[int]]): 图

        Returns:
            Tuple[int, DefaultDict[int, Set[int]], List[Set[int]]]: VBCC的数量、分组、每个结点对应的VBCC编号

        - 我们将深搜时遇到的所有边加入到栈里面，
        当找到一个割点的时候，
        就将这个割点往下走到的所有边弹出，
        而这些边所连接的点就是一个点双了

        - 两个点和一条边构成的图也称为(V)BCC,因为两个点均不为割点

        - VBCC编号多余1个的都是割点
        """

        def dfs(cur: int, parent: int) -> None:
            nonlocal dfsId, VBCCId
            if visited[cur]:
                return
            visited[cur] = True

            order[cur] = low[cur] = dfsId
            dfsId += 1

            dfsChild = 0
            for next in adjMap[cur]:
                if next == parent:
                    continue

                if not visited[next]:
                    dfsChild += 1
                    stack.append((cur, next))
                    dfs(next, cur)
                    low[cur] = min(low[cur], low[next])

                    # 遇到了割点(根和非根两种)
                    if (parent == -1 and dfsChild > 1) or (
                        parent != -1 and low[next] >= order[cur]
                    ):
                        while stack:
                            top = stack.pop()
                            VBCCGroupById[VBCCId].add(top[0])
                            VBCCGroupById[VBCCId].add(top[1])
                            VBCCIdByNode[top[0]].add(VBCCId)
                            VBCCIdByNode[top[1]].add(VBCCId)
                            if top == (cur, next):
                                break
                        VBCCId += 1

                elif low[cur] > order[next]:
                    low[cur] = min(low[cur], order[next])
                    stack.append((cur, next))

        dfsId = 0
        order, low = [Tarjan.INF] * n, [Tarjan.INF] * n

        visited = [False] * n
        stack = []

        VBCCId = 0  # 点双个数
        VBCCGroupById = defaultdict(set)  # 每个点双包含哪些点
        VBCCIdByNode = [set() for _ in range(n)]  # 每个点属于哪一(几)个点双，属于多个点双的点就是割点

        for cur in range(n):
            if not visited[cur]:
                dfs(cur, -1)

            if stack:
                while stack:
                    top = stack.pop()
                    VBCCGroupById[VBCCId].add(top[0])
                    VBCCGroupById[VBCCId].add(top[1])
                    VBCCIdByNode[top[0]].add(VBCCId)
                    VBCCIdByNode[top[1]].add(VBCCId)
                VBCCId += 1

        return VBCCId, VBCCGroupById, VBCCIdByNode

    @staticmethod
    def getEBCC(
        n: int, adjMap: DefaultDict[int, Set[int]]
    ) -> Tuple[int, DefaultDict[int, Set[Tuple[int, int]]], DefaultDict[Tuple[int, int], int]]:
        """Tarjan求解无向图的边双连通分量

        Args:
            n (int): 结点0-n-1
            adjMap (DefaultDict[int, Set[int]]): 图

        Returns:
            Tuple[int, DefaultDict[int, Set[Tuple[int, int]]], DefaultDict[Tuple[int, int], int]]]: EBCC的数量、分组、每条边对应的EBCC编号

        - 边对 (u,v) 中 u < v

        - 实现思路：
          - 将所有的割边删掉剩下的都是边连通分量了(其实可以用并查集做)
          - 处理出割边,再对整个无向图进行一次DFS,对于节点cur的出边(cur,next),如果它是割边,则跳过这条边不沿着它往下走
        """

        def dfs(cur: int, parent: int) -> None:
            nonlocal EBCCId
            if visited[cur]:
                return
            visited[cur] = True

            for next in adjMap[cur]:
                if next == parent:
                    continue

                edge = tuple(sorted([cur, next]))
                if edge in cuttingEdges:
                    continue

                EBCCGroupById[EBCCId].add(edge)
                EBCCIdByEdge[edge] = EBCCId
                dfs(next, cur)

        _, cuttingEdges = Tarjan.getCuttingPointAndCuttingEdge(n, adjMap)

        visited = [False] * n

        EBCCId = 0  # 边双个数
        EBCCGroupById = defaultdict(set)  # 每个边双包含哪些边
        EBCCIdByEdge = defaultdict(int)  # 每条边属于哪一个边双

        for cur in range(n):
            if not visited[cur]:
                dfs(cur, -1)
                EBCCId += 1

        for edge in cuttingEdges:
            EBCCGroupById[EBCCId].add(edge)
            EBCCIdByEdge[edge] = EBCCId
            EBCCId += 1

        return EBCCId, EBCCGroupById, EBCCIdByEdge