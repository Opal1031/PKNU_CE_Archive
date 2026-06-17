def _heapify(arr, n, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    if (left < n and arr[left] > arr[largest]):
        largest = left

    if (right < n and arr[right] > arr[largest]):
        largest = right

    if (largest != i):
        arr[i], arr[largest] = arr[largest], arr[i]
        _heapify(arr, n, largest)


def HeapSort(arr):
    n = len(arr)

    for i in range(n // 2 - 1, -1, -1):
        _heapify(arr, n, i)

    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        _heapify(arr, i, 0)

    return arr

# 시간복잡도: O(n log n)