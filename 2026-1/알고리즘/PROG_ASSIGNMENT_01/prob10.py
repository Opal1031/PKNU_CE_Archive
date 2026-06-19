import sys

input = sys.stdin.readline

N = int(input())

w = []
val = []
tot_c = 0

for _ in range(N):
    item_w, item_v, item_c = map(int, input().split())

    w.append(item_w)
    val.append(item_v + item_c)
    
    tot_c += item_c

W = int(input())

dp = [0] * (W + 1)

for i in range(N):
    item_w = w[i]
    item_val = val[i]

    for cap in range(W, item_w - 1, -1):
        cand = dp[cap - item_w] + item_val

        if (cand > dp[cap]):
            dp[cap] = cand

print(max(dp) - tot_c)