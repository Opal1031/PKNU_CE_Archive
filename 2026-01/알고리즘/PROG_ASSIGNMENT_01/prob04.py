import sys

input = sys.stdin.readline

N = int(input())
maze = [list(map(int, input().split())) for _ in range(N)]
K = int(input())

dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]

visited = [[False] * N for _ in range(N)]

def dfs(x, y, k):
    if (x == N - 1 and y == N - 1):
        return True

    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]

        if not (0 <= nx < N and 0 <= ny < N):
            continue

        if (maze[nx][ny] == 1 or visited[nx][ny]):
            continue

        next_k = k
        
        if (maze[nx][ny] == 2):
            next_k -= 1

        if (next_k < 0):
            continue

        visited[nx][ny] = True
    
        if (dfs(nx, ny, next_k)):
            return True
        
        visited[nx][ny] = False

    return False


if (maze[0][0] == 1 or maze[N - 1][N - 1] == 1):
    print("No")

else:
    visited[0][0] = True

    print("Yes" if dfs(0, 0, K) else "No")