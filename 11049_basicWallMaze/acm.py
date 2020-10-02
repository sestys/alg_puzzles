import sys, math

def printMatrix(matrix):
    for line in matrix:
        print(line)
    print()




def main():
    
    while True:
        start = map(int, sys.stdin.readline().split())
        if start[0] == start[1] == 0:
            break
        end = map(int, sys.stdin.readline().split())

        w1 = map(int, sys.stdin.readline().split())
        w2 = map(int, sys.stdin.readline().split())
        w3 = map(int, sys.stdin.readline().split())

if __name__=="__main__":
    main()

