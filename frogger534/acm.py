import sys, math

def printMatrix(matrix):
    for line in matrix:
        print(line)
    print()



class Edge():
    def __init__(self, v1, v2, w):
        self.v1 = v1
        self.v2 = v2
        self.w = w

    def __str__(self):
        return str(self.v1) + "-" + str(self.v2) + " == " + str(self.w) 

def euclid(coor1, coor2):
    return math.sqrt(((coor1[0] - coor2[0])**2) + ((coor1[1] - coor2[1])**2))

def kruskalMST(graph, n):
    result = []
    i = 0
    e = 0

    graph = sorted(graph,key=lambda item: item[2])
    parent = [x for x in range(n)]
    rank = [0 for x in range(n)]

    while e < n-1:
        u, v, w = graph[i]
        i+=1
        x = find(parent, u)
        y = find(parent, v)
        if x != y:
            e += 1
            union(parent, rank, x, y)
            if find(parent, 0) == find(parent, 1):
                return w
    return result

def union(parent, rank, x, y):
    xroot = find(parent, x)
    yroot = find(parent, y)
    if rank[xroot] < rank[yroot]:
        parent[xroot] = yroot
    elif rank[xroot] > rank[yroot]:
        parent[yroot] = xroot
    else:
        parent[yroot] = xroot
        rank[xroot] += 1

def find(parent, i):
    if parent[i] == i:
        return i
    return find(parent, parent[i])

def bfs(graph, n):
    graph = sorted(graph, key=lambda item: item[0])
    path = [float("-inf") for _ in range(n)]
    queue = [0]
    while queue:
        node = queue.pop(0)
        for v in graph:
            if v[0] == node:
                if v[1] == 1:
                    return max(v[2], path[node])
                path[v[1]] = max(v[2], path[v[1]], path[node])
                queue.append(v[1])
                graph.remove(v)
    return -1



def main():
    counter = 0
    while(True):
        n = int(input()) 
        if n == 0:
            break
        counter += 1
        stones = []
        graph = []
        for _ in range(n):
            stones.append(list(map(int, sys.stdin.readline().split())))
        maxDist = euclid(stones[0],stones[1])

        for i in range(n):
            for j in range(i+1,n):
                dist = euclid(stones[i], stones[j])
                if dist <= maxDist:
                    graph.append([i,j,dist])
        g = kruskalMST(graph, n)
        print("Scenario #{}".format(counter))
        print("Frog Distance = {0:.3f}".format(g))
        print()
        sys.stdin.readline()

if __name__=="__main__":
    main()

