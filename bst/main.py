import sys
import random


class Node():
    def __init__(self, k_min, k_max):
        self.Left_child = None
        self.Right_child = None
        self.k_min = k_min
        self.k_max = k_max

def printTree(root):
    if root is None:
        print("x")
    else:
        print("[{}...{}]".format(root.k_min, root.k_max))
        printTree(root.Left_child)
        printTree(root.Right_child)

def insert(root, k_min, k_max):
    if root is None:
        return Node(k_min, k_max)
    
    if k_min >= root.k_min and k_max <= root.k_max: #do nothing
        return root

    if k_max < root.k_min - 1: #insert to left
        root.Left_child = insert(root.Left_child, k_min, k_max)

    elif k_min > root.k_max + 1: #insert to right
        root.Right_child = insert(root.Right_child, k_min, k_max)

    else:
        if k_min < root.k_min:
            root.Left_child = delete(root.Left_child, k_min, root.k_min - 1)
            root.k_min = k_min
            if root.Left_child is not None:
                root.Left_child, root.k_min = leftMerge(root.Left_child, k_min)
        
        if k_max > root.k_max:
            root.Right_child = delete(root.Right_child, root.k_max + 1, k_max)
            root.k_max = k_max
            if root.Right_child is not None:
                root.Right_child, root.k_max = rightMerge(root.Right_child, k_max)
    return root

#returns Node and k_min value
def leftMerge(root, k_min): 
    
    if k_min >= root.k_min and k_min <= root.k_max + 1: #delete root and all right childs
        return root.Left_child, root.k_min

    if k_min > root.k_max + 1:
        if root.Right_child is not None: #look right
            root.Right_child, k_min = leftMerge(root.Right_child, k_min)
        return root, k_min

    if k_min < root.k_min:
        if root.Left_child is not None: #delete root and all right, look more left
            return leftMerge(root.Left_child, k_min)
        return None, k_min

def rightMerge(root, k_max):
    if k_max >= root.k_min - 1 and k_max <= root.k_max:
        return root.Right_child, root.k_max

    if k_max < root.k_min - 1:
        if root.Left_child is not None:
            root.Left_child, k_max = rightMerge(root.Left_child, k_max)
        return root, k_max

    if k_max > root.k_max:
        if root.Right_child is not None:
            return rightMerge(root.Right_child, k_max)
        return None, k_max


def delete(root, k_min, k_max):
    if root is None:
        return root
    #1L
    if k_max < root.k_min:
        root.Left_child = delete(root.Left_child, k_min, k_max)
    #1R
    elif k_min > root.k_max:
        root.Right_child = delete(root.Right_child, k_min, k_max)
    #2L
    elif k_max < root.k_max and (k_min == root.k_min or k_min == root.k_min - 1):
        root.k_min = k_max + 1
    #2R
    elif k_min > root.k_min and (k_max == root.k_max or k_max == root.k_max + 1):
        root.k_max = k_min - 1
    #3L
    elif k_min < root.k_min - 1 and k_max < root.k_max:
        root.Left_child = delete(root.Left_child, k_min, root.k_min - 2)
        root.k_min = k_max + 1
    #3R
    elif root.k_min < k_min and root.k_max + 1 < k_max:
        root.Right_child = delete(root.Right_child, root.k_max + 2, k_max)
        root.k_max = k_min - 1

    #4
    elif root.k_min < k_min and k_max < root.k_max:
        if k_min - root.k_min <= root.k_max - k_max:
            root.Left_child = insert(root.Left_child, root.k_min, k_min - 1)
            root.k_min = k_max + 1
        else:
            root.Right_child = insert(root.Right_child, k_max + 1, root.k_max)
            root.k_max = k_min - 1
    #5-7
    else:
        tree_min = findMin(root)
        tree_max = findMax(root)
        #5 delete root
        if k_min <= tree_min and k_max >= tree_max:
            return None
        #6L
        if k_min <= tree_min and tree_max > k_max:
            return delete(root.Right_child, root.k_max + 2, k_max)
        #6R
        if tree_min < k_min and tree_max <= k_max:
            return delete(root.Left_child, k_min, root.k_min - 2)
        #7
        if tree_min < k_min and k_max < tree_max:
            popMaxKeys2.k_min = -1
            popMaxKeys2.k_max = -1
            root.Left_child =  leftTrim(root.Left_child, k_min)
            root.Right_child = rightTrim(root.Right_child, k_max)
            root.Left_child = popMaxKeys2(root.Left_child)
            root.k_min = popMaxKeys2.k_min
            root.k_max = popMaxKeys2.k_max
    return root

def popMaxKeys2(root):
    if root is None:
        return None
    if root.Right_child is not None:
        root.Right_child = popMaxKeys2(root.Right_child)
        return root
    else:
        popMaxKeys2.k_max = root.k_max
        popMaxKeys2.k_min = root.k_min
        return root.Left_child

def popMaxKeys(root):
    if root is None:
        return -1, -1
    last = root
    run = False
    while root.Right_child is not None:
        run = True
        last = root
        root = root.Right_child
    last.Right_child = root.Left_child
    k_min = root.k_min
    k_max = root.k_max
    root = None
    if not run:
        last = None
    return k_min, k_max


def leftTrim(root, k_min):
    if root is None:
        return None 

    if root.k_min == k_min or root.k_min - 1 == k_min:
        return root.Left_child
    
    if root.k_min > k_min:
        return leftTrim(root.Left_child, k_min)
    
    if root.k_max + 1 == k_min:
        root.Right_child = None
        return root
    
    if root.k_max < k_min:
        root.Right_child = leftTrim(root.Right_child, k_min)
        return root
    else:
        root.k_max = k_min - 1
        root.Right_child = None
        return root

def rightTrim(root, k_max):
    if root is None:
        return None 
    
    if k_max == root.k_max or k_max == root.k_max + 1:
        return root.Right_child
    
    if root.k_max < k_max:
        return rightTrim(root.Right_child, k_max)
    
    if root.k_min - 1 == k_max:
        root.Left_child = None
        return root

    if root.k_min > k_max:
        root.Left_child = rightTrim(root.Left_child, k_max)
        return root
    else:
        root.k_min = k_max + 1
        root.Left_child = None
        return root

def findMin(root):
    if root is None:
        return -1
    while root.Left_child is not None:
        root = root.Left_child
    return root.k_min

def findMax(root):
    if root is None:
        return -1
    while root.Right_child is not None:
        root = root.Right_child
    return root.k_max

def inorder(root, level):
    if root is None:
        return
    inorder.keys += root.k_max - root.k_min + 1
    if level > inorder.max_depth:
        inorder.max_depth = level
        inorder.freq.append(root.k_max - root.k_min + 1)
    else:
        inorder.freq[level] += root.k_max - root.k_min + 1
    inorder(root.Left_child, level + 1)
    inorder(root.Right_child, level + 1)

def getOutput(root):
    inorder.keys = 0
    inorder.max_depth = -1 
    inorder.freq = []
    inorder(root, 0)
    print("{} {}".format(inorder.keys, inorder.max_depth))
    c = 0
    for k in inorder.freq:
        sys.stdout.write(str(k))
        if c != inorder.max_depth:
            sys.stdout.write(' ')
            c += 1
    sys.stdout.write('\n')

def get_dot(root):
    """return the tree with root 'self' as a dot graph for visualization"""
    return "digraph G{\n%s}" % ("" if root is None else (
        "\t%s [label=\"%s\"];\n%s\n" % (
            str(root.k_min),(str(root.k_min) + '..' + str(root.k_max)),
            "\n".join(_get_dot(root))
        )
    ))

def _get_dot(root):
    """recursively prepare a dot graph entry for this node."""
    if root.Left_child is not None:
        yield "\t%s [label=\"%s\"]" % (str(root.Left_child.k_min), (str(root.Left_child.k_min)+'..'+str(root.Left_child.k_max)))
        yield "\t%s -> %s;" % ((str(root.k_min)), str(root.Left_child.k_min))
        for i in _get_dot(root.Left_child):
            yield i
       
    elif root.Right_child is not None:
        r = random.randint(0, 1e9)
        yield "\tnull%s [shape=point];" % r
        yield "\t%s -> null%s;" % (str(root.k_min),r)
   
    if root.Right_child is not None:
        yield "\t%s [label=\"%s\"]" % (str(root.Right_child.k_min), (str(root.Right_child.k_min) + '..' + str(root.Right_child.k_max)))
        yield "\t%s -> %s;" % (str(root.k_min) ,str(root.Right_child.k_min))
        for i in _get_dot(root.Right_child):
            yield i
     
    elif root.Left_child is not None:
        r = random.randint(0, 1e9)
        yield "\tnull%s [shape=point];" % r
        yield "\t%s -> null%s;" % (str(root.k_min), r)
 
def main():
    root = None
    n = int(sys.stdin.readline())
    for i in range(n):
        command = sys.stdin.readline().split()
        if command[0] == 'I':
            root = insert(root, int(command[1]), int(command[2]))
        else:
            root = delete(root, int(command[1]), int(command[2]))
        print("{} {} {}".format(command[0], command[1], command[2]))
        printTree(root)
#        print(command)
#        print(get_dot(root))
        print()
    getOutput(root)

if __name__ == "__main__":
    main()
