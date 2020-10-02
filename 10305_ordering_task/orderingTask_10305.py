import sys

def topologicalOrdering(edges, n):
    ordering = []
    visited = [False for i in range(n+1)]
    for i in range(1, n+1):
        if not visited[i]:
            DFS(edges, i, visited, ordering)
    return ordering


def DFS(edges, from_node, visited, ordering):
    visited[from_node] = True
    for to_node in edges[from_node]:
        if not visited[to_node]:
            DFS(edges, to_node, visited, ordering)
    ordering.append(from_node)

def addEdge(edges, from_node, to_node):
    _addEdge(edges, from_node, to_node)
    _addEdge(edges, to_node, from_node)

def _addEdge(edges, from_node, to_node):
    edges[from_node].append(to_node)

if __name__ == '__main__':
    while True:
        inp = sys.stdin.readline().split()
        n = int(inp[0]) #number of tasks
        m = int(inp[1]) #number of precedence relations
        if n == 0 and m == 0: #end of input
            break
        edges = {}
        for i in range(n):
            edges.setdefault(i+1, [])
        for i in range(m):
            inp = sys.stdin.readline().split()
            _addEdge(edges, int(inp[0]), int(inp[1]))
        print(*list(reversed(topologicalOrdering(edges, n))), sep=' ')
