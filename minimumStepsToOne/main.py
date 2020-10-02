import sys, math

l = [0, 0]
m = 1
n = int(sys.stdin.readline())
for i in range(1, n+1):
    num = int(sys.stdin.readline())
    while m < num:
        m += 1
        l.append(float("inf"))
        if m % 3 == 0:
            ii = int(m / 3)
            l[m] = min(l[ii] + 1, l[m])
        if m % 2 == 0:
            ii = int(m / 2)
            l[m] = min(l[ii] + 1, l[m])
        l[m] = min(l[m], l[m-1] + 1)
    print("Case {}: {}".format(i, l[num]))
