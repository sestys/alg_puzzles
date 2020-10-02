import sys, math

def printMatrix(matrix):
    for line in matrix:
        print(line)
    print()


def isBalanced(lines):
    wl, dl, wr, dr = lines.pop(0)
    if wl == 0:
        wl, bl = isBalanced(lines)
        if not bl:
            return 0, False
    if wr == 0:
        wr, br = isBalanced(lines)
        if not br:
            return 0, False
    l = wl * dl
    r = wr * dr
    return wl+wr, l == r


def main():
    n = int(input())
    sys.stdin.readline()
    first = True
    for _ in range(n):
        lines = []
        while True:
            line = sys.stdin.readline().strip()
            if line == '':
                break
            else:
                lines.append(list(map(int, line.split())))
        _, bal = isBalanced(lines)
        if not first:

            print()
        if bal:
            print("YES")
        else:
            print("NO")
        first = False
        
          

if __name__=="__main__":
    main()

