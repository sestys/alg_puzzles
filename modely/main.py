import sys

class Node():
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def makeTree(planes, n):
    cr = 0
    cl = 0
    il = 0
    ir = n - 1
    if n > 1:
        for _ in range(n):
            if cl < cr:
                cl += planes[il]
                il += 1
            elif cl > cr:
                cr += planes[ir]
                ir -= 1
            else:
                cr += planes[ir]
                ir -= 1
        # print(cl, cr) 
        # print(il, ir)
        root = Node(cl-cr)
        makeTree.diff[makeTree.index] = abs(cl - cr)
        makeTree.root[makeTree.index] = il
        makeTree.index += 1
        root.left = makeTree(planes[:il], il)
        root.right = makeTree(planes[il:], n - il)
        return root
    elif n == 1:
        return Node(planes[0])
    else:
        return None

def addPilot(root, pilot):
    if not root:
        return
    if root.right and root.left:
        if root.value < 0:
            addPilot(root.left, pilot)
            root.value += pilot
        else:
            addPilot(root.right, pilot)
            root.value -= pilot
    else:
        root.value += pilot

def printTree(root):
    if not root:
        print("X")
    else:
        print(root.value)
        printTree(root.left)
        printTree(root.right)

def addTree(root):
    if not root or not root.right or not root.left:
        return 0
    return abs(root.value) + addTree(root.left) + addTree(root.right)

def main():
    n, pilot = map(int, sys.stdin.readline().split())
    planes = list(map(int, sys.stdin.readline().split()))
    # print(n, pilot)
    # print(planes)
    makeTree.diff = [0 for _ in range(n)]
    makeTree.root = [-1 for _ in range(n)]
    makeTree.index = 0
    root = makeTree(planes, n)
    printTree(root)
    print()
    addPilot(root, pilot)
    printTree(root)
    print(sum(makeTree.diff), addTree(root))

if __name__=="__main__":
    main()
