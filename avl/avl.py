import sys, random

class Node():
    def __init__(self, value):
        self.value = value
        self.right = None
        self.left = None
        self.height = 0

def getHeight(root):
    if not root:
        return -1
    return 1 + max(getHeight(root.left), getHeight(root.right))

def _getHeight(root):
    if not root:
        return 0
    else:
        return root.height

def getBalance(root):
    return getHeight(root.left) - getHeight(root.right)


def rotateRight(root):
    new_root = root.left
    new_left = new_root.right
    #rotation
    new_root.right = root
    root.left = new_left

    root.height = getHeight(root)
    new_root.height = getHeight(new_root)

    return new_root

def rotateLeft(root):
    new_root = root.right
    new_right = new_root.left
    #rotation
    new_root.left = root
    root.right = new_right

    root.height = getHeight(root)
    new_root.height = getHeight(new_root)

    return new_root

def insert(root, value):
    if not root:
        return Node(value)

    if value > root.value:
        root.right = insert(root.right, value)
    elif value < root.value:
        root.left = insert(root.left, value)
    else:
        return root
    
    root.height = getHeight(root)
    balance = getBalance(root)

    if balance == 2: #L
        if value < root.left.value: #L
            return rotateRight(root)
        else: #R
            root.left = rotateLeft(root.left)
            return rotateRight(root)

    if balance == -2: #R
        if value > root.right.value: #R
            return rotateLeft(root)
        else: #L
            root.right = rotateRight(root.right)
            return rotateLeft(root)
    return root

def delete(root, value):
    if not root:
        return None
    if value < root.value:
        root.left = delete(root.left, value)
    elif value > root.value:
        root.right = delete(root.right, value)
    else:
        if not root.left:
            return root.right
        elif not root.right:
            return root.left
        else:
            root.value = findMin(root.right)
            root.right = delete(root.right, root.value)

    root.height = getHeight(root)
    balance = getBalance(root)
    #rotations
    if balance > 1:
        if getBalance(root.left) >= 0:
            return rotateRight(root)
        else:
            root.left = rotateLeft(root.left)
            return rotateRight(root)
    if balance < -1:
        if getBalance(root.right) <= 0:
            return rotateLeft(root)
        else:
            root.right = rotateRight(root.right)
            return rotateLeft(root)
    return root
def findMin(root):
    if not root:
        return -1
    while root.left:
        root = root.left
    return root.value

def get_dot(root):
    """return the tree with root 'self' as a dot graph for visualization"""
    return "digraph G{\n%s}" % ("" if root is None else (
        "\t%s [label=\"%s\"];\n%s\n" % (
            str(root.value),(str(root.value)),
            "\n".join(_get_dot(root))
        )
    ))

def _get_dot(root):
    """recursively prepare a dot graph entry for this node."""
    if root.left is not None:
        yield "\t%s [label=\"%s\"]" % (str(root.left.value), (str(root.left.value)))
        yield "\t%s -> %s;" % ((str(root.value)), str(root.left.value))
        for i in _get_dot(root.left):
            yield i
       
    elif root.right is not None:
        r = random.randint(0, 1e9)
        yield "\tnull%s [shape=point];" % r
        yield "\t%s -> null%s;" % (str(root.value),r)
   
    if root.right is not None:
        yield "\t%s [label=\"%s\"]" % (str(root.right.value), (str(root.right.value)))
        yield "\t%s -> %s;" % (str(root.value) ,str(root.right.value))
        for i in _get_dot(root.right):
            yield i
     
    elif root.left is not None:
        r = random.randint(0, 1e9)
        yield "\tnull%s [shape=point];" % r
        yield "\t%s -> null%s;" % (str(root.value), r)

def main():
    root = None
    n = int(sys.stdin.readline())
    for i in range(n):
        command = int(sys.stdin.readline())
        if command > 0:
            root = insert(root, command)
        else:
            root = delete(root, abs(command))

        print(get_dot(root))

        
if __name__=="__main__":
    main()
