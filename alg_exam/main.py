import sys, math, timeit
from heapq import heappush, heappop

def readMatrix(rows, columns):
    return [[int(x) for x in sys.stdin.readline().split()] for y in range(rows)]

def printMatrix(matrix):
    for row in matrix:
        print(row)    
    print()


def calcMove(i1, i2, e, dmov, denv):
    if i1 < i2:
        e += dmov
    elif i1 > i2:
        if e < dmov:
            e = 0
        else:
            e -= dmov
    if e >= denv + i2:
        e -= denv
    elif denv + i2 > e and e > i2:
        e = i2
    return e

def runDron(matrix, r, c, e, dmov, denv):
    moves = [x[:] for x in [[float("inf")] * c] * r]
    iont = [x[:] for x in [[0] * c] * r]

    iont[0][0] = e
    moves[0][0] = 0
    queue = []
    heappush(queue, [0, 0-e, 0, 0]) #[moves, iont, x, y]

    while(queue):
        u = heappop(queue)
        print(u)
        m = u[0]
        e = abs(u[1])
        x = u[2]
        y = u[3]
        if y - 1 >= 0:
            ee = calcMove(matrix[y][x], matrix[y-1][x], e, dmov, denv)
            if ee > 0:
                if moves[y-1][x] > m+1:
                    moves[y-1][x] = m+1
                    heappush(queue, [m+1, 0-ee, x, y-1])
                elif iont[y-1][x] < ee:
                    iont[y-1][x] = ee
                    heappush(queue, [m+1, 0-ee, x, y-1])

        if y + 1 < r:
            if y+1 == r-1 and x == c-1:
                return m+1
            ee = calcMove(matrix[y][x], matrix[y+1][x], e, dmov, denv)
            if ee > 0:
                if moves[y+1][x] > m+1:
                    moves[y+1][x] = m+1
                    heappush(queue, [m+1, 0-ee, x, y+1])
                elif iont[y+1][x] < ee:
                    iont[y+1][x] = ee
                    heappush(queue, [m+1, 0-ee, x, y+1])

        if x - 1 >= 0:
            ee = calcMove(matrix[y][x], matrix[y][x-1], e, dmov, denv)
            if ee > 0:
                if moves[y][x-1] > m+1:
                    moves[y][x-1] = m+1
                    heappush(queue, [m+1, 0-ee, x-1, y])
                elif iont[y][x-1] < ee:
                    iont[y][x-1] = ee
                    heappush(queue, [m+1, 0-ee, x-1, y])

        if x + 1 < c:
            if x+1 == c-1 and y  == r-1:
                return m+1
            ee = calcMove(matrix[y][x], matrix[y][x+1], e, dmov, denv)
            if ee > 0:
                if moves[y][x+1] > m+1:
                    moves[y][x+1] = m+1
                    heappush(queue, [m+1, 0-ee, x+1, y])
                elif iont[y][x+1] < ee:
                    iont[y][x+1] = ee
                    heappush(queue, [m+1, 0-ee, x+1, y])
            



def main():
    M, N, E, Dmov, Denv = map(int, sys.stdin.readline().split())
    matrix = readMatrix(M, N)
    print(runDron(matrix, M, N, E, Dmov, Denv))

if __name__=="__main__":
    main()
