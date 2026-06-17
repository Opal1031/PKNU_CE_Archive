import sys
from collections import deque

input = sys.stdin.readline

N = int(input())
lst = list(map(int, input().split()))

visited = [False] * N

def bfs():
    dq = deque()
    dq.append(0)
    visited[0] = True

    while dq:
        x = dq.popleft()

        if (x == N - 1):
            return True
        
        for i in range(1, lst[x] + 1):
            nx = x + i

            if (nx >= N):
                continue

            if (visited[nx]):
                continue

            if (lst[nx] == 0 and nx != N - 1):
                continue

            visited[nx] = True
            dq.append(nx)

    return False

print("Yes" if bfs() else "No")