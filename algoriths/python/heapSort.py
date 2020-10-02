import max_heap

def heapSort(values):
    max_heap.buildMaxHeap(values)
    sorted = []
    for i in range(len(values)):
        sorted.append(max_heap.getMax(values))
    return reversed(sorted)
