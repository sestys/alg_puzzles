
def mergeSort(values):
    n = len(values)
    if n <= 1:
        return values
    else:
        left = mergeSort(values[:n//2])
        right = mergeSort(values[n//2:])
        nLeft = len(left)
        nRight = len(right)
        idL = 0
        idR = 0
        result = []
        for i in range(n):
            if idL == nLeft:
                result.append(right[idR])
                idR += 1
            elif idR == nRight or left[idL] < right[idR]:
                result.append(left[idL])
                idL += 1;
            else:
                result.append(right[idR])
                idR += 1
        return result
