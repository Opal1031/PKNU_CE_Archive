def is_subset(A, B):
    # 1. 배열 B의 모든 원소를 해시 세트(set)에 삽입 -> 시간 복잡도 O(n)
    hash_set_B = set(B)
    
    # 2. 배열 A의 원소를 하나씩 꺼내어 확인 -> 시간 복잡도 O(m)
    for num in A:
        if num not in hash_set_B:
            # 해시 세트에 없는 원소가 하나라도 있다면 부분집합이 아님
            return False
            
    # 모든 원소가 존재한다면 부분집합임
    return True

# --- 테스트 ---
A = [1, 3, 5]
B = [1, 2, 3, 4, 5, 6]
print(f"문제 2 결과: {is_subset(A, B)}") # True 출력