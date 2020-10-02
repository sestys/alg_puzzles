
class Node:

    def __init__(self, id):
        self.id = id
        self.edges = []

    def getEdges(self):
        return

    def __str__(self):
        id = str(self.id)
        edges = str(self.edges)
        return id + ": " + edges

def main():
    nodes = []
    while True:
        n = int(input()) #number of nodes
        if(n == 0): #end of input
            break
        nodes.clear() #init nodes
        for i in range(n):
            nodes.append(Node(i))
        loadEdges(nodes)
        if bicolor(nodes):
            print("BICOLORABLE.")
        else:
            print("NOT BICOLORABLE.")

def loadEdges(nodes):
    edges = int(input())
    for i in range(edges):
        x, y = map(int, input().split())
        nodes[x].edges.append(y)
        nodes[y].edges.append(x)

def bicolor(nodes):
    n = len(nodes)
    currentLayer = {nodes[0]}
    nextLayer = set()
    while n > 0:
        for node in currentLayer:
            n -= 1 # done working with one node
            for e in node.edges: #e is index
#if there is edge between two nodes in the same layer, graph is not biparit
                if nodes[e] in currentLayer:
                    return False
#add end node of edge e to next layer
                else:
                    nextLayer.add(nodes[e])
        currentLayer = nextLayer.copy()
        nextLayer.clear()
    return True


if __name__ == '__main__':
    main()
