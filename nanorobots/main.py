from util import printMatrix
from copy import deepcopy

#make integer sum matrix for given matrix
def integerSum(matrix):
    r = len(matrix)
    c = len(matrix[0])
    intsum = [[0]*(c+1) for i in range(r+1)]
    #count first row and column
    intsum[1][1]=matrix[0][0]
    for i in range(1,r):
        intsum[i+1][1] = matrix[i][0]+intsum[i][1]
    for i in range(1,c):
        intsum[1][i+1] = matrix[0][i] + intsum[1][i]
    #count the rest of the matrix
    for i in range(1,r):
        for j in range(1,c):
            intsum[i+1][j+1] = matrix[i][j] + intsum[i+1][j] + intsum[i][j+1] - intsum[i][j]
    return intsum

def moveRobot(matrix, coor, subSum):
    print(coor[0])
    x1 = coor[0]
    y1 = coor[1]
    x2 = coor[2]
    y2 = coor[3]
    if x1 == x2: #going horizontaly
        if y1 < y2: #left to right
            for i in range(y1, y2 + 1):
                if matrix[x1][i] != -1:
                    subSum += matrix[x1][i]
                    matrix[x1][i] = -1
                else:
                    break
        else: #right to left
            for i in range(y1, y2 - 1, -1):
                if matrix[x1][i] != -1:
                    subSum += matrix[x1][i]
                    matrix[x1][i] = -1
                else:
                    break
    else: #going verticaly
        if x1 < x2: #top to bottom
            for i in range(x1, x2 + 1):
                if matrix[i][y1] != -1:
                    subSum += matrix[i][y1]
                    matrix[i][y1] = -1
                else:
                    break
        else: #bottom to top
            for i in range(x1, x2 - 1, -1):
                if matrix[i][y1] != -1:
                    subSum += matrix[i][y1]
                    matrix[i][y1] = -1
                else:
                    break
    return subSum

def robotRecursion(matrix, robots, maxSum, subSum, level):
    print("level: ", level, "len(robots): ", len(robots))
    if len(robots) == 0:
        if subSum > maxSum[0]:
            maxSum[0] = subSum
        print("returning")
        return

    for i in range(len(robots)):
        m = deepcopy(matrix)
        nextSum = moveRobot(m, robots[i], subSum)
        r = deepcopy(robots[i])
        del robots[i]
        print(r)
        robotRecursion(m, robots, maxSum, nextSum, level +1)
        robots = robots[:i] + r + robots[i:]
        print(robots, "level:  ", level)

def main():
    r, c = input().split()
    r=int(r)
    c=int(c)
    matrix = []
    for i in range(r):
        matrix.append([int(x) for x in input().split()])
    numR = int(input())
    robots = []
    for i in range(numR):
        robots.append([int(x) for x in input().split()])
    maxSum = [0]
    robotRecursion(matrix, robots, maxSum, 0, 0)
    print(maxSum[0])


if __name__=="__main__":
    main()

'''
matrix=[[-1, -1,  1,  1, -1, -1],
            [ 1,  1,  1, -1, -1,  1],
            [-1,  1, -1, -1, -1, -1],
            [-1, -1, -1,  1,  2, -1],
            [-2,  1, -1, -1, -1,  1]]
printMatrix(integerSum(matrix))
'''
