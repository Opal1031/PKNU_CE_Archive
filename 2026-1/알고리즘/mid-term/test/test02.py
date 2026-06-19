import sys
input = sys.stdin.readline

N = int(input())
arr = list(map(int, input().split()))

def max_heap_check(heap, idx = 0):
    left = 2 * idx + 1
    right = 2 * idx + 2

    # 리프 노드면 True
    if idx >= N // 2:
        return True
    
    # 자식이 존재하고, 부모가 자식보다 작으면 False
    if left < N and heap[idx] < heap[left]:
        return False
    
    if right < N and heap[idx] < heap[right]:
        return False
    
    # 왼쪽, 오른쪽 자식에 대해 재귀적으로 확인
    return max_heap_check(heap, left) and max_heap_check(heap, right)

print("YES" if max_heap_check(arr) else "NO")