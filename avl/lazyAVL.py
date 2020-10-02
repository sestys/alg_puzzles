import sys, random

r = None

class Node():
    def __init__(self, value):
        self.value = value
        self.right = None
        self.left = None
        self.deleted = False
        self.path = 0
        self.height = 0

def getHeight(root):
    if not root:
        return -1
    return 1 + max(_getHeight(root.left), _getHeight(root.right))

def _getHeight(root):
    if not root:
        return -1
    else:
        return root.height

def getPath(root):
    if not root:
        return 0
    if root.deleted:
        return 1 + max(_getPath(root.right), _getPath(root.left))
    else:
        return max(_getPath(root.left), _getPath(root.right))


def _getPath(root):
    if not root:
        return 0
    return root.path

def getBalance(root):
    return getHeight(root.left) - getHeight(root.right)

def rotateRight(root):
    rotateRight.counter += 1
    new_root = root.left
    new_left = new_root.right
    #rotation
    new_root.right = root
    root.left = new_left

    root.height = getHeight(root)
    new_root.height = getHeight(new_root)

    root.path = getPath(root)
    new_root.path = getPath(new_root)

    return new_root

def rotateLeft(root):
    rotateLeft.counter += 1
    new_root = root.right
    new_right = new_root.left
    #rotation
    new_root.left = root
    root.right = new_right

    root.height = getHeight(root)
    new_root.height = getHeight(new_root)

    root.path = getPath(root)
    new_root.path = getPath(new_root)

    return new_root

def insert(root, value):
    if not root:
        return Node(value)

    if value > root.value:
        root.right = insert(root.right, value)
    elif value < root.value:
        root.left = insert(root.left, value)
    else:
        if root.deleted:
            root.deleted = False
            root.path -= 1
        return root
    
    root.path = getPath(root)
    root.height = getHeight(root)
    balance = getBalance(root)

    if balance > 1 and value < root.left.value: #L
        return rotateRight(root)

    if balance < -1 and value > root.right.value: #R
        return rotateLeft(root)

    if balance > 1 and value >= root.left.value:
        root.left = rotateLeft(root.left)
        return rotateRight(root)

    if balance < -1 and value <= root.right.value: #L
        root.right = rotateRight(root.right)
        return rotateLeft(root)
    return root

def lazyDelete(root, value):
    if not root:
        return None
    if value < root.value:
        root.left = lazyDelete(root.left, value)
    elif value > root.value:
        root.right = lazyDelete(root.right, value)
    else:
        root.deleted = True

    root.path = getPath(root)
    
    return root

def delete(root, value):
    if not root:
        return None
    if value < root.value:
        root.left = delete(root.left, value)
    elif value > root.value:
        root.right = delete(root.right, value)
    else:
        if root.left:
            root.value = findMax(root.left)
            root.left = delete(root.left, root.value)
        elif root.right:
            root.value = findMin(root.right)
            root.right = delete(root.right, root.value)
        else:
            return None

    root.height = getHeight(root)
    root.path = getPath(root)
    balance = getBalance(root)
    #rotations
    if balance > 1 and  getBalance(root.left) >= 0:
        return rotateRight(root)
    if balance < -1 and getBalance(root.right) <= 0:
        return rotateLeft(root)
    if balance > 1 and getBalance(root.left) < 0:
        root.left = rotateLeft(root.left)
        return rotateRight(root)
    if balance < -1 and getBalance(root.right) > 0:
        root.right = rotateRight(root.right)
        return rotateLeft(root)
    return root

def remove(root, value):
    if not root:
        return root

def findMax(root):
    if not root:
        return -1
    while root.right:
        root = root.right
    return root.value

def findMin(root):
    if not root:
        return -1
    while root.left:
        root = root.left
    return root.value

def checkConsolidation(root):
    if not root or root.path < 1 + root.height//2:
        return False
    else:
        return True

def consolidation(root):
    global r
    while getPath(root) > 0:
        print(root.value)
        if getPath(root.left) > 0:
            consolidation(root.left)
        elif getPath(root.right) > 0:
            consolidation(root.right)
        elif root.deleted:
            root.deleted = False
            r = delete(r, root.value)
        else:
            root.left.path = 0
            root.right.path = 0
            return

def consolidationStupid(root):
    if not root:
        return False
    if getPath(root) > 0:
        if getPath(root.left) > 0:
            consolidationStupid(root.left)
            return True
        if getPath(root.right) > 0:
            consolidationStupid(root.right)
            return True

        if root.deleted:
            global r
            root.deleted = False
            r = delete(r, root.value)
            return True
    return False 

def get_dot(root):
    """return the tree with root 'self' as a dot graph for visualization"""
    return "digraph G{\n%s}" % ("" if root is None else (
        "\t%s [label=\"%s\"];\n%s\n" % (
            str(root.value),(str(root.value)+('-' if root.deleted else '+') + str(root.height)),
            "\n".join(_get_dot(root))
        )
    ))

def _get_dot(root):
    """recursively prepare a dot graph entry for this node."""
    if root.left is not None:
        yield "\t%s [label=\"%s\"]" % (str(root.left.value), (str(root.left.value)+('-' if root.left.deleted else '+') + str(root.left.height)))
        yield "\t%s -> %s;" % ((str(root.value)), str(root.left.value))
        for i in _get_dot(root.left):
            yield i
       
    elif root.right is not None:
        r = random.randint(0, 1e9)
        yield "\tnull%s [shape=point];" % r
        yield "\t%s -> null%s;" % (str(root.value),r)
   
    if root.right is not None:
        yield "\t%s [label=\"%s\"]" % (str(root.right.value), (str(root.right.value)+('-' if root.right.deleted else '+') + str(root.right.height)))
        yield "\t%s -> %s;" % (str(root.value) ,str(root.right.value))
        for i in _get_dot(root.right):
            yield i
     
    elif root.left is not None:
        r = random.randint(0, 1e9)
        yield "\tnull%s [shape=point];" % r
        yield "\t%s -> null%s;" % (str(root.value), r)


def main():
    global r
    con_counter = 0
    rotateLeft.counter = 0
    rotateRight.counter = 0
    n = int(sys.stdin.readline())
    for i in range(n):
        command = int(sys.stdin.readline())
        if command > 0:
            r = insert(r, command)

        else:
            r = lazyDelete(r, abs(command))
        if checkConsolidation(r):
            con_counter += 1
            while consolidationStupid(r):
                pass
    print("{} {} {}".format(getHeight(r), rotateLeft.counter + rotateRight.counter, con_counter))

        
if __name__=="__main__":
    main()
