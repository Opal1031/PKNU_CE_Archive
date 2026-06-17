import sys
input = sys.stdin.readline

N = int(input())

arr = []
while (len(arr) < N):
    nums = list(map(int, input().split()))

    for num in nums:
        if (len(arr) == N):
            break

        arr.append(num)

K = int(input())

def lower_bound(lo, hi):
    if (lo >= hi):
        return lo

    mid = (lo + hi) // 2
    
    if arr[mid] < K:
        return lower_bound(mid + 1, hi)
    
    return lower_bound(lo, mid)

pos = lower_bound(0, N)

if pos == 0:
    print(arr[0])

elif (pos == N):
    print(arr[N - 1])

else:
    left = arr[pos - 1]
    right = arr[pos]

    if (K - left <= right - K):
        print(left)
    
    else:
        print(right)