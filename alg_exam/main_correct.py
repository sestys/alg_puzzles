import sys, math, timeit
from heapq import heappush, heappop

def readMatrix(rows, columns):
    return [[int(x) for x in sys.stdin.readline().split()] for y in range(rows)]

def printMatrix(matrix):
    for row in matrix:
        print(row)    
    print()
            
def read2ints():
    i, ii = sys.stdin.readline().split()
    return int(i), int(ii)

def subSum2(matrix, sumMatrix, x, y, rows, colums):
    sumMatrix[x][y] = -1
    queue = [[x,y]]
    while queue:
        u = queue.pop()
        x = u[0]
        y = u[1]
        subSum2.m.append(u)
        subSum2.count += 1
        if y > 0 and sumMatrix[x][y-1] == 0 and matrix[x][y] == matrix[x][y-1]:
            sumMatrix[x][y-1]=-1
            queue.append([x,y-1])
        if y+1 < colums and sumMatrix[x][y+1] == 0 and matrix[x][y] == matrix[x][y+1]:
            sumMatrix[x][y+1]=-1
            queue.append([x,y+1])
        if x+1 < rows and sumMatrix[x+1][y] == 0 and matrix[x][y] == matrix[x+1][y]:
            sumMatrix[x+1][y]=-1
            queue.append([x+1, y])
        if x > 0 and sumMatrix[x-1][y] == 0 and matrix[x][y] == matrix[x-1][y]:
            sumMatrix[x-1][y]=-1
            queue.append([x-1, y])


def subSum(matrix, sumMatrix, x, y, rows, colums):
    subSum.m.append([x, y])
    subSum.count += 1
    sumMatrix[x][y] = -1
    if y > 0 and sumMatrix[x][y-1] == 0 and matrix[x][y] == matrix[x][y-1]:
        subSum(matrix, sumMatrix, x, y-1, rows, colums)
    if y+1 < colums and sumMatrix[x][y+1] == 0 and matrix[x][y] == matrix[x][y+1]:
        subSum(matrix,sumMatrix, x, y+1, rows, colums)
    if x+1 < rows and sumMatrix[x+1][y] == 0 and matrix[x][y] == matrix[x+1][y]:
        subSum(matrix,sumMatrix, x+1, y, rows, colums)
    if x > 0 and sumMatrix[x-1][y] == 0 and matrix[x][y] == matrix[x-1][y]:
        subSum(matrix, sumMatrix, x-1, y, rows, colums)

def getSubSums(matrix, rows, colums):
    sumMatrix = [x[:] for x in [[0] * colums] * rows]
    for i in range(rows):
        for j in range(colums):
            if sumMatrix[i][j] == 0:
                subSum2.m = []
                subSum2.count = 0
                subSum2(matrix,sumMatrix, i, j, rows, colums)
                for x, y in subSum2.m:
                    sumMatrix[x][y] = subSum2.count
    return sumMatrix

def reconfigure(x, y):
    return abs(x-y) > min(x, y)

def reconfigure2(x, y):
    if reconfigure(x, y):
        return 1 
    else:
        return 0

def bfs_reconfiguration(matrix, rows, colums, start, dest):
    queue = []
    i = 0

    best_r = float("inf")
    visited = [x[:] for x in [[False] * colums] * rows]
    reconfiguration = [x[:] for x in [[float("inf")] * colums] * rows]

    visited[start[0]][start[1]] = True
    reconfiguration[start[0]][start[1]] = 0
    heappush(queue, [0, start[0], start[1]]) #[reconfiguration, x,y]
   

    while (len(queue) != 0):
        u = heappop(queue)
        if best_r < u[0]:
            continue
        x = u[1]
        y = u[2]
        for d in [[-1,0],[1,0],[0,-1],[0,1]]:
            xx = x+d[0]
            yy = y+d[1]
            if xx >= 0 and xx < rows and yy >= 0 and yy < colums:         
                if visited[xx][yy] == False:
                    visited[xx][yy] = True
                    if reconfigure(matrix[x][y], matrix[xx][yy]):
                        reconfiguration[xx][yy] = u[0] + 1
                    else:
                        reconfiguration[xx][yy] = u[0]
                    heappush(queue, [reconfiguration[xx][yy], xx, yy])
                else:
                    if reconfigure(matrix[x][y], matrix[xx][yy]):
                        a = 1
                    else:
                        a = 0
                    if reconfiguration[xx][yy] > u[0]+a:
                        reconfiguration[xx][yy] = u[0]+a
                        heappush(queue, [reconfiguration[xx][yy], xx, yy])
                
                if xx == dest[0] and yy == dest[1]:
                    best_r = reconfiguration[xx][yy]

    return reconfiguration

def bfs_distance(matrix, reconfiguration, rows, colums, start, dest):
    distance = [x[:] for x in [[float("inf")] * colums] * rows]
    visited = [x[:] for x in [[False] * colums] * rows]

    distance[start[0]][start[1]] = 0
    visited[start[0]][start[1]] = True
    best_r = reconfiguration[dest[0]][dest[1]]
    best_d = float("inf")
    queue = [[distance[start[0]][start[1]], start[0], start[1]]]

    while queue:
        u = heappop(queue)
        x = u[1]
        y = u[2]
        if best_r < reconfiguration[x][y]:
            continue

        if y > 0 and reconfiguration[x][y-1] == reconfiguration[x][y] + reconfigure2(matrix[x][y], matrix[x][y-1]):
            if not visited[x][y-1]:
                visited[x][y-1] = True
                distance[x][y-1] = distance[x][y] + 1
                heappush(queue, [distance[x][y-1], x, y-1])
            elif distance[x][y-1] > distance[x][y] + 1:
                distance[x][y-1] = distance[x][y] + 1
                heappush(queue,[distance[x][y-1],x, y-1])
                
        if y+1 < colums and reconfiguration[x][y+1] == reconfiguration[x][y] + reconfigure2(matrix[x][y], matrix[x][y+1]):
            if not visited[x][y+1]:
                visited[x][y+1] = True
                distance[x][y+1] = distance[x][y] + 1
                heappush(queue,[distance[x][y+1],x, y+1])
            elif distance[x][y+1] > distance[x][y] + 1:
                distance[x][y+1] = distance[x][y] + 1
                heappush(queue,[distance[x][y+1],x, y+1])

        if x+1 < rows and reconfiguration[x+1][y] == reconfiguration[x][y] + reconfigure2(matrix[x][y], matrix[x+1][y]):
            if not visited[x+1][y]:
                visited[x+1][y] = True
                distance[x+1][y] = distance[x][y] + 1
                heappush(queue, [distance[x+1][y], x+1, y])
            elif distance[x+1][y] > distance[x][y] + 1:
                distance[x+1][y] = distance[x][y] + 1
                heappush(queue,[distance[x+1][y],x+1,y])

        if x > 0 and reconfiguration[x-1][y] == reconfiguration[x][y] + reconfigure2(matrix[x][y], matrix[x-1][y]):
            if not visited[x-1][y]:
                visited[x-1][y] = True
                distance[x-1][y] = distance[x][y] + 1
                heappush(queue,[distance[x-1][y],x-1, y])
            elif distance[x-1][y] > distance[x][y] + 1:
                distance[x-1][y] = distance[x][y] + 1
                heappush(queue,[distance[x-1][y],x-1, y])
        if [x-1, y] == dest:
            return distance[dest[0]][dest[1]]

    return distance[dest[0]][dest[1]]



def main():
    start = timeit.default_timer()
    rows, colums = read2ints()
    x1, y1 = read2ints()
    x2, y2 = read2ints()
    matrix = readMatrix(rows, colums)
    sub = getSubSums(matrix, rows, colums)
    r = bfs_reconfiguration(sub, rows, colums, [x1-1,y1-1],[x2-1,y2-1])
    d = bfs_distance(sub, r, rows, colums,[x1-1,y1-1],[x2-1,y2-1])
    print("{} {}".format(r[x2-1][y2-1], d))
    stop = timeit.default_timer()
    print(stop - start)

if __name__ == "__main__":
    main()

