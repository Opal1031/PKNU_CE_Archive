def CountingSort(arr):
    if (len(arr) == 0):
        return arr

    max_value = max(arr)
    count = [0] * (max_value + 1)
    result = [0] * len(arr)

    for value in arr:
        count[value] += 1

    for i in range(1, len(count)):
        count[i] += count[i - 1]

    for i in range(len(arr) - 1, -1, -1):
        value = arr[i]
        count[value] -= 1
        result[count[value]] = value

    for i in range(len(arr)):
        arr[i] = result[i]

    return arr

# 시간복잡도: O(n + k)