import sys, math

def printMatrix(matrix):
    for line in matrix:
        print(line)
    print()



def main():
    humble = generate()
    print(humble)
    print(len(humble))

    while True:
        n = int(input())
        if n == 0:
            break
        print(humble[n-1])


if __name__=="__main__":
    main()

