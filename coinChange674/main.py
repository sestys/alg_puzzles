import sys



def main():
    val = [50, 25, 10, 5 ]
    
    x = list(map(int, sys.stdin.readlines()))
    m = max(x)
    t = [1 for _ in range(m+1)]
    for v in val:
        for i in range(1,m+1):
            if i >= v:
                t[i] += t[i-v]

    for j in x: 
        print(t[j])

def rek(value):
    if value < 0:
        return 0
    if value == 0:
        return 1
    return rek(value-50) + rek(value-25) + rek(value-10) + rek(value-5) 

if __name__=="__main__":
    main()
