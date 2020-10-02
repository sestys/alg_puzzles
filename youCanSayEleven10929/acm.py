import sys, math

def printMatrix(matrix):
    for line in matrix:
        print(line)
    print()



def main():
    n = input()
    m = int(n)
    while (m != 0):
        n = n.strip()
        if m % 11 == 0:
            print("{} is a multiple of 11.".format(n))
        else:
            print("{} is not a multiple of 11.".format(n))
        n = input()
        m = int(n)

if __name__=="__main__":
    main()

