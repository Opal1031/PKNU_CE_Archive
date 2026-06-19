def _counting_sort_by_digit(arr, exp):
    count = [0] * 10
    result = [0] * len(arr)

    for value in arr:
        index = (value // exp) % 10
        count[index] += 1

    for i in range(1, 10):
        count[i] += count[i - 1]

    for i in range(len(arr) - 1, -1, -1):
        value = arr[i]
        index = (value // exp) % 10
        count[index] -= 1
        result[count[index]] = value

    for i in range(len(arr)):
        arr[i] = result[i]


def RadixSort(arr):
    if (len(arr) == 0):
        return arr

    max_value = max(arr)
    exp = 1

    while (max_value // exp > 0):
        _counting_sort_by_digit(arr, exp)
        exp *= 10

    return arr

# 시간복잡도: O(d(n + 10)) = O(dn)  # n개의 d자리 정수, 10진수 기준