def read_input(filename):
    with open(filename, 'r', encoding='utf-8') as f:
        lines = [line.strip() for line in f if line.strip()]

    N = int(lines[0])
    w_i = list(map(int, lines[1].split()))
    v_i = list(map(int, lines[2].split()))
    W = int(lines[3])

    return N, w_i, v_i, W

N, w_i, v_i, W = read_input('mid-term/input1.txt')

dp = [0] * (W + 1)

for i in range(N):
    item_w = w_i[i]
    item_v = v_i[i]

    for cur in range(item_w, W + 1):
        dp[cur] = max(dp[cur], dp[cur - item_w] + item_v)

print(dp[W])