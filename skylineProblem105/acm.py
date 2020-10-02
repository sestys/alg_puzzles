import sys, math

def printMatrix(matrix):
    for line in matrix:
        print(line)
    print()



def main():
    h = []
    w = 0
    s = 1000000
    lines = sys.stdin.readlines()
    for line in lines:
        l = list(map(int, line.split()))
        if l[0] < s:
            s = l[0]
        if l[2] > w:
            w = l[2]
        h.append(l)
    x = 0
    high = 0
    end = 1000000
    f = True
    ret = []
    count = len(h)
    for i in range(s, w+1):
        cur_h = high
        if end == i:
            cur_h = 0

        for j in range(x, count):
            if j == x and h[j][2] < i:
                x += 1
                continue
            cur_house = h[j]
            if cur_house[0] > i:
                break
            if cur_house[0] <= i and cur_house[2] > i:
                if cur_h < cur_house[1]:
                    cur_h = cur_house[1]
                    end = cur_house[2]
        if cur_h != high:
            high = cur_h
            ret.append(i)
            ret.append(high)
    print(*ret)

if __name__=="__main__":
    main()

