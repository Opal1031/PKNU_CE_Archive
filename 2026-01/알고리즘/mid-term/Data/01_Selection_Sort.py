def SelectionSort(arr):
    for i in range(len(arr) - 1, -1, -1):
        max_idx = 0

        for j in range(1, i + 1):
            if (arr[j] > arr[max_idx]):
                max_idx = j

        arr[i], arr[max_idx] = arr[max_idx], arr[i]

    return arr

# 시간복잡도: O(n^2)