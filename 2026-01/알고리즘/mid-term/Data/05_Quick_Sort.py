def _partition(arr, low, high):
    pivot = arr[high]
    i = low - 1

    for j in range(low, high):
        if (arr[j] <= pivot):
            i += 1
            arr[i], arr[j] = arr[j], arr[i]

    arr[i + 1], arr[high] = arr[high], arr[i + 1]

    return i + 1


def _quick_sort(arr, low, high):
    if (low < high):
        pi = _partition(arr, low, high)

        _quick_sort(arr, low, pi - 1)
        _quick_sort(arr, pi + 1, high)


def QuickSort(arr):
    _quick_sort(arr, 0, len(arr) - 1)

    return arr

# 시간복잡도: 평균 O(n log n), 최악 O(n^2)