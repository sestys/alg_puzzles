import math
import sys

def getBranchesRight(matrix, c, r):
    branches=[[0]*c for i in range(r)]
    for i in range(r):
        for j in range(c-1):
            if j == 0:
                branches[i][c-1] = matrix[i][c-1]
            elif matrix[i][c-1-j]+branches[i][c-j] > matrix[i][c-j-1]:
                branches[i][c-1-j] = matrix[i][c-1-j] + branches[i][c-j]
            else:
                branches[i][c-j-1]= matrix[i][c-j-1]
    return branches

def getBranchesLeft(matrix, c, r):
    branches=[[0]*c for i in range(r)]
    for i in range(r):
        for j in range(c-1):
            if j == 0:
                branches[i][j] = matrix[i][j]
            elif matrix[i][j]+branches[i][j-1] > matrix[i][j]:
                branches[i][j] = matrix[i][j] + branches[i][j-1]
            else:
                branches[i][j]= matrix[i][j]
    return branches

def getBranchesTop(matrix, c, r):
    branches=[[0]*c for i in range(r)]
    for j in range(c):
        for i in range(r-1):
            if i == 0:
                branches[i][j] = matrix[i][j]
            elif matrix[i][j]+branches[i-1][j] > matrix[i][j]:
                branches[i][j] = matrix[i][j] + branches[i-1][j]
            else:
                branches[i][j]= matrix[i][j]
    return branches

def getBranchesBottom(matrix, c, r):
    branches=[[0]*c for i in range(r)]
    for j in range(c):
        for i in range(r-1):
            if i == 0:
                branches[r-1][j] = matrix[r-1][j]
            elif matrix[r-i-1][j]+branches[r-i][j] > matrix[r-i-1][j]:
                branches[r-i-1][j] = matrix[r-i-1][j] + branches[r-i][j]
            else:
                branches[r-i-1][j]= matrix[r-i-1][j]
    return branches


def kadaneRight(matrix, c, r, maxSum):
    branches = getBranchesRight(matrix, c, r)
    for i in range(c-1): #dont do the last column
        for offset in range(r-2): #offset on the begining from top

            b=[branches[offset][i+1], branches[offset+1][i+1], branches[offset+2][i+1]]
            msum = matrix[offset][i] + matrix[offset+1][i] + matrix[offset+2][i] + branches[offset][i+1]+branches[offset+1][i+1] + branches[offset+2][i+1]
            minBranche = min(b) 
            if msum > maxSum:
                maxSum = msum
            for j in range(offset + 3, r): #adding to the bottom
                msum = msum + matrix[j][i]
                if minBranche < branches[j][i+1]:
                    b.remove(minBranche)
                    msum = msum - minBranche + branches[j][i+1]
                    b.append(branches[j][i+1])
                    minBranche = min(b)
                if msum > maxSum:
                    maxSum = msum
    return maxSum

def kadaneLeft(matrix, c, r, maxSum):
    branches = getBranchesLeft(matrix, c, r)
    for i in range(1, c): #dont do the first column
        for offset in range(r-2): #offset on the begining from top

            b=[branches[offset][i-1], branches[offset+1][i-1], branches[offset+2][i-1]]
            msum = matrix[offset][i] + matrix[offset+1][i] + matrix[offset+2][i] + branches[offset][i-1]+branches[offset+1][i-1] + branches[offset+2][i-1]
            minBranche = min(b) 
            if msum > maxSum:
                maxSum = msum
            for j in range(offset + 3, r): #adding to the bottom
                msum = msum + matrix[j][i]
                if minBranche < branches[j][i-1]:
                    b.remove(minBranche)
                    msum = msum - minBranche + branches[j][i-1]
                    b.append(branches[j][i-1])
                    minBranche = min(b)
                if msum > maxSum:
                    maxSum = msum
    return maxSum

def kadaneTop(matrix, c, r, maxSum):
    branches = getBranchesTop(matrix, c, r)
    for j in range(1,r): #dont do the top row
        for offset in range(c-2): #offset on the begining from left
            b=[branches[j-1][offset], branches[j-1][offset+1], branches[j-1][offset+2]]
            msum = matrix[j][offset] + matrix[j][offset+1] + matrix[j][offset+2] + branches[j-1][offset]+branches[j-1][offset+1] + branches[j-1][offset+2]
            minBranche = min(b) 
            if msum > maxSum:
                maxSum = msum
            for i in range(offset + 3, c): #adding to the right
                msum = msum + matrix[j][i]
                if minBranche < branches[j-1][i]:
                    b.remove(minBranche)
                    msum = msum - minBranche + branches[j-1][i]
                    b.append(branches[j-1][i])
                    minBranche = min(b)
                if msum > maxSum:
                    maxSum = msum
    return maxSum


def kadaneBottom(matrix, c, r, maxSum):
    branches = getBranchesBottom(matrix, c, r)
    for j in range(r-1): #dont do the bottom row
        for offset in range(c-2): #offset on the begining from left
            b=[branches[j+1][offset], branches[j+1][offset+1], branches[j+1][offset+2]]
            msum = matrix[j][offset] + matrix[j][offset+1] + matrix[j][offset+2] + branches[j+1][offset]+branches[j+1][offset+1] + branches[j+1][offset+2]
            minBranche = min(b) 
            if msum > maxSum:
                maxSum = msum
            for i in range(offset + 3, c): #adding to the right
                msum = msum + matrix[j][i]
                if minBranche < branches[j+1][i]:
                    b.remove(minBranche)
                    msum = msum - minBranche + branches[j+1][i]
                    b.append(branches[j+1][i])
                    minBranche = min(b)
                if msum > maxSum:
                    maxSum = msum
    return maxSum

def main():
    r, c = [int(x) for x in sys.stdin.readline().split()]

    matrix = []
    for i in range(r):
        matrix.append([int(x) for x in input().split()])
    
    maxSum = float("-inf")
    maxSum = kadaneTop(matrix, c,  r, maxSum)
    maxSum = kadaneBottom(matrix, c, r, maxSum)
    maxSum = kadaneLeft(matrix, c, r, maxSum)
    maxSum = kadaneRight(matrix, c, r, maxSum)
    print(maxSum)

def printMatrix(matrix):
    for i in range(len(matrix)):
        print(matrix[i])
    print()

if __name__=="__main__":
    main()

'''
matice=[[-1, -1,  1,  1, -1, -1],
            [ 1,  1,  1, -1, -1,  1],
            [-1,  1, -1, -1, -1, -1],
            [-1, -1, -1,  1,  2, -1],
            [-2,  1, -1, -1, -1,  1]]

matice2 = [[ 0,  0,  5, -1, -7, -2,  3,  3],
            [-1,  0, -2, -1,  0,  5, -3,  5],
            [-3, -4,  4, -8,  4,  5,  4,  5],
            [-5,  5, -1, -4, -4, -8, -1,  1],
            [-1,  4,  4, -6,  4,  0, -1,  2],
            [-3,  4, -3,  2,  1, -8,  3, -5]]

matice3 = [[-3,-1,-3,-6,2,-6,0,-4],
            [-2,3,-6,-3,0,-5,-5,3],
            [-5,2,-5,2,-6,1,1,-6],
            [1,-5,-2,-3,-1,-5,-1,-5],
            [-1,-1,0,1,-4,2,-2,1],
            [-2,-1,3,-6,3,1,-3,-5],
            [-3,3,-1,-3,-1,3,1,-6],
            [0,-2,-1,-6,0,-2,1,-5]]

print(kadaneTop(matice3, 8, 8, 0))
'''

