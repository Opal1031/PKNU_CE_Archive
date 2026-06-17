import sys

input = sys.stdin.readline

N = int(input())
cap = int(input())

w = list(map(int, input().split()))
v = list(map(int, input().split()))

dp = [0] * (cap + 1)

for i in range(N):
    item_w = w[i]
    item_v = v[i]

    for cur in range(cap, item_w - 1, -1):
        dp[cur] = max(dp[cur], dp[cur - item_w] + item_v)

print(dp[cap])