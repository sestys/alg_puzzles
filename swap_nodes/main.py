import os
import sys
from collections import deque
#
# Complete the swapNodes function below.
#

class Node():
    def __init__(self, val, l=None, r=None, d=-1):
        self.v = val
        self.l = l
        self.r = r
        self.d = d

def grow_tree(indexes):
    i = 0
    nodeQ = deque()
    valQ = deque(indexes)
    root = Node(1, d=1)
    nodeQ.append(root)
    while len(valQ) > 0:
        values = valQ.popleft()
        l = None if values[0] == -1 else values[0]
        r = None if values[1] == -1 else values[1]
        curr = nodeQ.popleft()
        if l is not None:
            left = Node(l, d=curr.d+1)
            curr.l = left
            nodeQ.append(left)
        if r is not None:
            right = Node(r, d=curr.d+1)
            curr.r = right
            nodeQ.append(right)
    return root

def lo_print(node, s):
    if node.l:
        s = lo_print(node.l, s)
    s.append(node.v)
    if node.r:
        s = lo_print(node.r, s)
    return s

def swap(node, q):
    if node.d % q == 0:
        tmp = node.r
        node.r = node.l
        node.l = tmp
    if node.l:
        swap(node.l, q)
    if node.r:
        swap(node.r, q)

def swapNodes(indexes, queries):
    root = grow_tree(indexes)
    ret = []
    for q in queries:
        swap(root, q)
        l = lo_print(root, [])
        ret.append(l)
    return ret

if __name__ == '__main__':
    fptr = sys.stdout 

    n = int(input())

    indexes = []

    for _ in range(n):
        indexes.append(list(map(int, input().rstrip().split())))

    queries_count = int(input())

    queries = []

    for _ in range(queries_count):
        queries_item = int(input())
        queries.append(queries_item)

    result = swapNodes(indexes, queries)

    fptr.write('\n'.join([' '.join(map(str, x)) for x in result]))
    fptr.write('\n')

    fptr.close()

