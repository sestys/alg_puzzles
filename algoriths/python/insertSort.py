
def insertSort(values):
    for i in range(1,len(values)):
        while values[i] < values[i-1] and i > 0:
            values[i], values[i-1] = values[i-1], values[i]
            i -= 1
    return values
