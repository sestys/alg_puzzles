import sys, math

def printMatrix(matrix):
    for line in matrix:
        print(line)
    print()



def main():
    n = int(input())
    cases = []
    for _ in range(n):
        num = int(input())
        cases.append(num)
    m = max(cases)
    fact = [1, 1]
    for i in range(2, m+1):
        ap = int((fact[-1] * i)%1000000007)
        fact.append(ap)
    counter = 1
    for x in cases:
        s = 0
        for k in range(1, x+1):
            s += (fact[x]/(fact[k-1]*fact[x-k]))
            s = s % 1000000007
        print("Case #{}: {}".format(counter, int(s)))
        counter += 1

if __name__=="__main__":
    main()

