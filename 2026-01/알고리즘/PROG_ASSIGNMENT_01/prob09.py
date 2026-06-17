import sys

input = sys.stdin.readline

N = int(input())
A = [list(map(int, input().split())) for _ in range(N)]
k = int(input())

team = []

def dfs(start):
    if (len(team) == k):
        s = 0

        for i in team:
            for j in team:
                s += A[i][j]
        
        return s

    if (N - start < k - len(team)):
        return None

    best = None

    for i in range(start, N):
        team.append(i)
        val = dfs(i + 1)
        team.pop()

        if val is not None:
            if (best is None or val > best):
                best = val

    return best

print(dfs(0))