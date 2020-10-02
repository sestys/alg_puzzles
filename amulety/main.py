import sys
import math

def findMaxSumPath(tree, node, n):
    if node >= n:
        return [], 0
    #node was removed from tree
    if tree[node] == -1:
        return [], 0
    #node is leaf
    if 2*node+1 >= n:
        Lpath = []
        Rpath = []
        LChMax = 0
        RChMax = 0
    else:
        #get max path in childs
        Lpath, LChMax = findMaxSumPath(tree, 2*node+1, n)
        Rpath, RChMax = findMaxSumPath(tree, 2*node+2, n)
    
    if findMaxSumPath.result < LChMax + RChMax + tree[node]:
        findMaxSumPath.result = LChMax + RChMax + tree[node]
        findMaxSumPath.path = Lpath + [node] + Rpath

    if LChMax >= RChMax:
        return Lpath + [node], LChMax + tree[node]
    else:
        return Rpath + [node], RChMax + tree[node]

def main():
    n=int(input())
    tree=[]
    for x in sys.stdin.readline().split():
        tree.append(int(x))
    i = 0
    count = 0
    while i < n:
        if tree[i] != -1:
            findMaxSumPath.result = float("-inf")
            findMaxSumPath.path = []
            findMaxSumPath(tree, i, n)
            for x in findMaxSumPath.path:
                tree[x] = -1
            count += 1
        else:
            i += 1
    print(count)

if __name__=="__main__":
    main()
