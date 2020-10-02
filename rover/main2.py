import sys, math, copy
from heapq import heappush, heappop, heapify

def readMatrix(rows, columns):
    return [[int(x) for x in sys.stdin.readline().split()] for y in range(rows)]

def printMatrix(matrix):
    for row in matrix:
        print(row)    
            
def read2ints():
    i, ii = sys.stdin.readline().split()
    return int(i), int(ii)

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

def bfs(matrix, rows, colums, start, dest):
    queue = []
    
    m =[[copy.deepcopy([0, float("inf"),[-1,-1], False]) for i in range(colums)] for j in range(rows)] #[reconfiguration, distance, [x,y], visited] 
    m[start[0]][start[1]][1] = 0
    m[start[0]][start[1]][2] = [start[0],start[1]]
    m[start[0]][start[1]][3] = True
    heappush(queue, m[start[0]][start[1]])
    i = 0
    while (len(queue) != 0):
        u = heappop(queue)
        i += 1
        x = u[2][0]
        y = u[2][1]
        for d in [[-1,0],[1,0],[0,-1],[0,1]]:
            xx = x+d[0]
            yy = y+d[1]
            if xx >= 0 and xx < rows and yy >= 0 and yy < colums:         
                if m[xx][yy][3] == False:
                    m[xx][yy][3] = True
                    m[xx][yy][1] = u[1] + 1
                    if reconfigure(matrix[x][y], matrix[xx][yy]):
                        m[xx][yy][0] = u[0] + 1
                    else:
                        m[xx][yy][0] = u[0]
                    m[xx][yy][2] = [xx,yy]
                    heappush(queue, m[xx][yy])
                else:
                    if reconfigure(matrix[x][y], matrix[xx][yy]):
                        a = 1
                    else:
                        a = 0
                    if m[xx][yy][0] > u[0]+a:
                        m[xx][yy][0] = u[0]+a
                        m[xx][yy][1] = u[1] + 1
                        heapify(queue)
                        
                    elif m[xx][yy][0] == u[0]+a:
                        if m[xx][yy][1] > u[1]+1:
                            m[xx][yy][1] = u[1]+1
                            heapify(queue)
                                            
                if xx == dest[0] and yy == dest[1]:
                    return m[xx][yy][0], m[xx][yy][1]

    return -1, -1


def main():

    rows, colums = read2ints()
    x1, y1 = read2ints()
    x2, y2 = read2ints()
    matrix = readMatrix(rows, colums)
    conf, moves = bfs(getSubSums(matrix, rows, colums), rows, colums, [x1-1,y1-1],[x2-1,y2-1])
    print("{} {}".format(conf, moves))

if __name__ == "__main__":
    main()

