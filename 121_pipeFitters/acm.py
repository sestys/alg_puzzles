import sys, math

def printMatrix(matrix):
    for line in matrix:
        print(line)
    print()


grid = 'grid'
skew = 'skew'

def countGrid(a, b):
    return int(math.floor(a) * math.floor(b))


def countSkew(a, b):
    if b < 1:
        return 0
    h = 1 + math.floor((b-1) / math.sqrt(3)*2)
    return int(h/2 * math.floor(a) + h / 2 * math.floor(a-0.5))
    

def main():
    for line in sys.stdin.readlines():
        a, b = map(float, line.split())
        sk = max(countSkew(a, b), countSkew(b, a))
        gr = countGrid(a, b)
        if sk > gr:
            print(sk, skew)
        else:
            print(gr, grid)

if __name__=="__main__":
    main()

