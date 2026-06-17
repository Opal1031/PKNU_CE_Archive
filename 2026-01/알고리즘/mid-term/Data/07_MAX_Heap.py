import sys
input = sys.stdin.readline

def max_heap_push(heap, value):
    heap.append(value)
    idx = len(heap) - 1

    while idx > 0:
        parent = (idx - 1) // 2

        if heap[idx] > heap[parent]:
            heap[idx], heap[parent] = heap[parent], heap[idx]
            idx = parent

        else:
            break

def build_max_heap(arr):
    heap = []

    for v in arr:
        max_heap_push(heap, v)

    return heap

def max_heap_check(heap, idx=0):
    n = len(heap)
    left = 2 * idx + 1
    right = 2 * idx + 2

    # 리프 노드면 True
    if idx >= n // 2:
        return True
    
    # 자식이 존재하고, 부모가 자식보다 작으면 False
    if left < n and heap[idx] < heap[left]:
        return False
    
    if right < n and heap[idx] < heap[right]:
        return False
    
    # 왼쪽, 오른쪽 자식에 대해 재귀적으로 확인
    return max_heap_check(heap, left) and max_heap_check(heap, right)

if __name__ == "__main__":
    heap1 = build_max_heap([40, 30, 20, 10, 15])
    heap2 = build_max_heap([35, 17, 16, 8, 4])

    merged = heap1 + heap2  # 두 힙 배열을 합침
    merged_heap = build_max_heap(merged)  # 한 번에 최대 힙으로 만듦

    print("Heap 1:", heap1)
    print("Heap 2:", heap2)
    print("Merge:", merged)
    print("Merged Heap:", merged_heap)

    print("Heap 1 is max heap:", "YES" if max_heap_check(heap1) else "NO")
    print("Heap 2 is max heap:", "YES" if max_heap_check(heap2) else "NO")
    print("Merged Heap is max heap:", "YES" if max_heap_check(merged_heap) else "NO")

# 시간 복잡도: O(n log n)