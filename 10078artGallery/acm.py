import sys, math

def printMatrix(matrix):
    for line in matrix:
        print(line)
    print()

def crossproduct(x, y, z):
    dx1 = y[0] - x[0]
    dy1 = y[1] - x[1]
    dx2 = z[0] - y[0]
    dy2 = z[1] - y[1]
    return dx1 * dy2 - dy1 * dx2

def solve(points):
    l = crossproduct(points[-2], points[-1], points[0])
    for i in range(-1, len(points)-2):
        p = crossproduct(points[i], points[i+1], points[i+2])
        if p * l < 0:
            print("Yes")
            return
    print("No")



def main():
    points = int(sys.stdin.readline())
    while points > 0:
        p = []
        for _ in range(points):
            p.append(list(map(int, sys.stdin.readline().split())))
        solve(p)
        points = int(sys.stdin.readline())



if __name__=="__main__":
    main()

