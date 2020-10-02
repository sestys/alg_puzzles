import sys

n = int(sys.stdin.readline())
l = [-1 for _ in range(1000)]
l[0] = 0
l[1] = 1
m = 1
for i in range(1,n+1):
    num = int(sys.stdin.readline())
    while m < num:
        m += 1
        l[m] = m + 2 * l[m-1] - l[m-2]
    print("{}: {} {}".format(i, num, l[num]))
