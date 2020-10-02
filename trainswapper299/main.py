import sys


def bubble(trains):
    swaps = 0
    for i in range(len(trains)):
        for j in range(1,len(trains)-i):
            if trains[j] < trains[j-1]:
                swaps += 1
                tmp = trains[j]
                trains[j] = trains[j-1]
                trains[j-1] = tmp
    return swaps

def main():
    n = int(sys.stdin.readline())
    for _ in range(n):
        num = int(sys.stdin.readline())
        trains = list(map(int, sys.stdin.readline().split()))
        print("Optimal train swapping takes {} swaps.".format(bubble(trains)))

if __name__=="__main__":
    main()
