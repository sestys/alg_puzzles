import sys

def printm(m):
    for l in m:
        print(l)
    print()

def knapsack(bush, m):
    k = [[0 for _ in range(m + 1)] for _ in range(len(bush)+1)]

    for i in range(len(bush)+1):
        for j in range(m + 1):
            if j == 0 or i == 0:
                k[i][j] = 0
            elif bush[i-1] <= j:
                k[i][j] = max(bush[i-1] + k[i-2][j-bush[i-1]], k[i-1][j])
            else:
                k[i][j] = k[i-1][j]
    return k[len(bush)][m]


def main():
    t = int(sys.stdin.readline())
    for i in range(t):
        n, k = map(int, sys.stdin.readline().split())
        bushes = list(map(int, sys.stdin.readline().split()))
        print("Scenario #{}: {}".format(i+1, knapsack(bushes, k)))
if __name__=="__main__":
    main()
