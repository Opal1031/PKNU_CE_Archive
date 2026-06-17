import sys

input = sys.stdin.readline

N = int(input())
maze = [list(map(int, input().split())) for _ in range(N)]
K = int(input())

dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]

visited = [[False] * N for _ in range(N)]

def dfs(x, y, k):
    dist = abs((N - 1) - x) + abs((N - 1) - y)

    if (dist > k):
        return 0

    if (x == N - 1 and y == N - 1):
        return 1

    if (k == 0):
        return 0

    cnt = 0

    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]

        if not (0 <= nx < N and 0 <= ny < N):
            continue

        if (maze[nx][ny] == 1 or visited[nx][ny]):
            continue

        visited[nx][ny] = True
        cnt += dfs(nx, ny, k - 1)
        visited[nx][ny] = False

    return cnt


if (maze[0][0] == 1 or maze[N - 1][N - 1] == 1):
    print(0)

else:
    visited[0][0] = True
    
    print(dfs(0, 0, K))