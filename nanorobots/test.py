
def addOne(m):
    m[0] += 1

r, c = input().split()
r = int(r)
c = int(c)
print(r,  c)

m = [5, 4]

for i in range(5,1,-1):
    print(i)

print("M before addOne: ", m)
addOne(m[:])
print("M after addOne: ", m)
