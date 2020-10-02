import io
import max_heap
import heapSort
import insertSort
import mergeSort

values = [4, 5, 1, 11, 54, 3, 5, 10, 6, 7]

def sorting(values):
    tmp = values.copy()
    print("Unsorted values: ", *values)
    heap = heapSort.heapSort(tmp)
    insert = insertSort.insertSort(values)
    merge = mergeSort.mergeSort(values)
    print("Heap sort: ", *heap)
    print("Insert sort: ", *insert)
    print("Merge sort: ", *merge)

def main(values):
    print(*values)
    max_heap.buildMaxHeap(values)
    print(*values)
    max = max_heap.getMax(values)
    print("Max: ", max, ", heap: ", *values)
    max_heap.insert(values, 11)
    print(*values)

if __name__ == '__main__':
    sorting(values)
