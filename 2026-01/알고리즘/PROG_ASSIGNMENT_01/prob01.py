import sys
input = sys.stdin.readline

N = int(input())
arr = list(map(int, input().split()))
K = int(input())

def Rank(i):
    if (i == N):
        return 0

    if (arr[i] < K):
        return 1 + Rank(i + 1)
    
    else:
        return Rank(i + 1)

print(Rank(0) + 1)