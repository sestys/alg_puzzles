import sys
from math import ceil

n = int(sys.stdin.readline())

for _ in range(n):
    n, m = map(int, sys.stdin.readline().split())
    n -= 2
    m -= 2
    row = ceil(n / 3)
    col = ceil(m / 3)
    print(row * col)
