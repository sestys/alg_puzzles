


# maxHeap - full binary tree, where last row is filled from left
# Property: if p is parent, s is son, the value(p) >= value(s).
# Heap is saved in a array, for node at position i, i = 0, 1, 2, ..., n-1; goes:
# left son is at position 2i+1, right son at 2i+2, for son at position i goes:
# parent is at position (i-1)//2

# implemented methods: buildMaxHeap(array) - builds max heap from array, returns array
#                      insert(heap, value) - inserts value into heap, return array
#                      getMax(heap) - returns max value from heap, removes the value

def buildMaxHeap(values):
    for i in range(len(values)//2-1, -1, -1):
        heapMaxify(values, i)



def insert(heap, value):
    heap.append(value)
    i = len(heap)-1
    while i >= 0 and heap[i] > heap[(i-1)//2]:
        heap[i], heap[(i-1)//2] = heap[(i-1)//2], heap[i]
        i = (i-1)//2



def getMax(heap):
    max = heap[0]
    heap[0] = heap[len(heap)-1]
    heap.pop(len(heap)-1)
    heapMaxify(heap, 0)
    return max

#check if node at position satisfies Max Heap property
def heapMaxify(heap, i):
    if 2*i+2 < len(heap) and (heap[i] < heap[2*i+1] or heap[i] < heap[2*i + 2]):
        # find bigger son
        if heap[2*i + 1] > heap[2*i +2]:
            heap[i], heap[2*i+1] = heap[2*i+1], heap[i]
            heapMaxify(heap, 2*i + 1)
        else:
            heap[i], heap[2*i+2] = heap[2*i+2], heap[i]
            heapMaxify(heap, 2*i + 2)
    elif 2*i+1 < len(heap) and heap[i] < heap[2*i+1]:
        heap[i], heap[2*i+1] = heap[2*i+1], heap[i]
        heapMaxify(heap, 2*i + 1)
