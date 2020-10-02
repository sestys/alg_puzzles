import sys, math

def printMatrix(matrix):
    for line in matrix:
        print(line)
    print()



def main():
    while(True):
        n = int(input())
        if n == 0:
            break
        if n % 2 == 1 or n < 4:
            print("Impossible")
        else:
            print(str(n+n//2))
            print("{} {}".format(1, n))
            for i in range(1, n):
                print("{} {}".format(i, i+1))
            for i in range(1, n//2+1):
                print("{} {}".format(i, n//2+i))

if __name__=="__main__":
    main()

