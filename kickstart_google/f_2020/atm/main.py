import os
from sys import stdin
import math
from queue import PriorityQueue

def solution(n, x, q):
    x = float(x)
    q = [(math.ceil(c / x), i+1) for i, c in enumerate(q)]
    q.sort()
    ret = ''
    ret = str(q[0][1])
    for i in range(1, n):
        ret += ' ' + str(q[i][1])
    return ret


t = int(input())

for i in range(1, t+1):
    n, x = map(int, stdin.readline().rstrip().split())
    q = map(int, stdin.readline().rstrip().split())
    print("Case #{}: {}".format(i, solution(n, x, q)))
