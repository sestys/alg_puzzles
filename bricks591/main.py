import sys



def main():
    n = int(sys.stdin.readline())
    i = 1
    while n != 0:
        s = list(map(int, sys.stdin.readline().split()))
        h = int(sum(s)/n)
        ss = 0
        for x in s:
            if x > h:
               ss += x - h
        print("Set #{}".format(i))
        print("The minimum number of moves is {}.".format(ss))
        print()
        i += 1
        n = int(sys.stdin.readline())

if __name__=="__main__":
    main()
