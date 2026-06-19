def count_distinct_elements(arr, k):
    # 예외 처리: 배열이 비어있거나 윈도우 크기가 배열보다 클 경우
    if not arr or k > len(arr):
        return []

    frequency_map = {} # 빈도를 저장할 해시맵 (파이썬 딕셔너리)
    result = []

    # 1. 첫 k개 구간에 대한 초기 윈도우 설정
    for i in range(k):
        # 딕셔너리에 키가 없으면 0을 반환하고 1을 더함
        frequency_map[arr[i]] = frequency_map.get(arr[i], 0) + 1
        
    # 현재 해시맵에 존재하는 키(Key)의 개수가 서로 다른 원소의 개수임
    result.append(len(frequency_map))

    # 2. 윈도우를 한 칸씩 이동하며 업데이트
    for i in range(k, len(arr)):
        # 들어오는 새 원소 추가
        incoming = arr[i]
        frequency_map[incoming] = frequency_map.get(incoming, 0) + 1
        
        # 나가는 옛날 원소 제거
        outgoing = arr[i - k]
        frequency_map[outgoing] -= 1
        
        # [중요] 빈도가 0이 되면 해시맵에서 해당 원소를 완전히 삭제!
        # 삭제하지 않으면 len(frequency_map)에 0개짜리 원소도 카운트됨
        if frequency_map[outgoing] == 0:
            del frequency_map[outgoing]
            
        # 업데이트된 종류의 개수를 결과에 저장
        result.append(len(frequency_map))
        
    return result

# --- 테스트 ---
# 문제 3 예시 (영문 대문자)
X = ['A', 'B', 'A', 'C', 'D', 'B', 'C']
k_X = 4
print(f"문제 3 결과: {count_distinct_elements(X, k_X)}") 
# 출력: [3, 4, 4, 3]

# 문제 4 예시 (넓은 범위의 정수)
A = [1, 2, 1, 3, 4, 2, 3]
k_A = 4
print(f"문제 4 결과: {count_distinct_elements(A, k_A)}") 
# 출력: [3, 4, 4, 3]