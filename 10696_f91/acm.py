import sys, math

def printMatrix(matrix):
    for line in matrix:
        print(line)
    print()


def f91(n):
    if n <= 100:
        return f91(f91(n+11))
    else:
        return n - 10


def main():
    for line in sys.stdin.readlines():
        n = int(line)
        if n == 0:
            return
        if n >= 101:
            print("f91({}) = {}".format(n, n-10))
        else:
            print("f91({}) = {}".format(n, 91))
        


if __name__=="__main__":
    main()

