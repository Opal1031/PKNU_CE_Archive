import sys
from collections import deque

input = sys.stdin.readline

N = int(input())
maze = [list(map(int, input().split())) for _ in range(N)]
K = int(input())

dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]

def bfs():
	dist = [[-1] * N for _ in range(N)]
	
	dq = deque()
	dq.append((0, 0))
	dist[0][0] = 0

	while dq:
		x, y = dq.popleft()

		if (x == N - 1 and y == N - 1):
			return dist[x][y]

		for i in range(4):
			for step in range(1, K + 1):
				nx = x + dx[i] * step
				ny = y + dy[i] * step

				if not (0 <= nx < N and 0 <= ny < N):
					break
				
				if (maze[nx][ny] == 1):
					break

				if (dist[nx][ny] != -1):
					continue

				dist[nx][ny] = dist[x][y] + 1
				dq.append((nx, ny))

	return -1

print(bfs())