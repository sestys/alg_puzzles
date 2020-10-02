import sys, math

def printMatrix(matrix):
    for line in matrix:
        print(line)
    print()

def solve(field, m, n):
    visited = [[False for _ in range(n)] for _ in range(m)]
    counter = 0
    for x in range(m):
        for y in range(n):
            if visited[x][y]:
                continue
            visited[x][y] = True
            if field[x][y] == '@':
                counter += 1
                bfs(field, m, n, visited, x, y)
    return counter

def checkCoor(x, y, m, n):
    return x >= 0 and y >= 0 and x < m and y < n

def bfs(field, m, n, visited, x, y):
    d = [[-1, -1], [-1, 0], [-1, 1], [0, -1],[0, 1],[1,-1],[1,0],[1,1]]
    for xx, yy in d:
        nx = x+xx
        ny = y+yy
        if checkCoor(nx, ny, m, n):
            if not visited[nx][ny] and field[nx][ny] == '@':
                visited[nx][ny] = True
                bfs(field, m, n, visited, nx, ny)

            


def main():
    while(True):
        m, n = map(int, sys.stdin.readline().split())
        if m == 0:
            break
        field = []
        for _ in range(m):
            field.append(list(sys.stdin.readline().rstrip()))
        print(solve(field, m, n))

if __name__=="__main__":
    main()

