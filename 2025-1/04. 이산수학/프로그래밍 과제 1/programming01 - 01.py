# 리스트를 입력 받는 함수
# 원소들을 입력 후, 0을 입력하면 집합 입력 종료
def get_set():
    arr = list(map(int, input("집합 입력 (0으로 종료) : ").split()))
    return arr[:-1]  # 0을 제외한 부분을 리스트로 반환

# 합집합 함수
# result 리스트 안에 A, B에 해당하는 원소가 없으면 추가가
def union(A, B):
    result = []

    for x in A:
        if x not in result:
            result.append(x)

    for y in B:
        if y not in result:
            result.append(y)

    return sorted(result)

# 교집합 함수
# A, B 모두에 해당하는 원소만 result 리스트에 추가
def intersection(A, B):
    result = []

    for x in A:
        if x in B and x not in result:
            result.append(x)

    return sorted(result)

# 차집합 함수
# A집합에는 포함되나, B집합에는 포함되지 않는 원소만 result 리스트에 추가
def difference(A, B):
    result = []

    for x in A:
        if x not in B:
            result.append(x)

    return sorted(result)

# 배열 입력 받기
A = get_set()
B = get_set()

# 출력
print("합집합 : ", union(A, B))
print("교집합 : ", intersection(A, B))
print("차집합 (A - B) : ", difference(A, B))
print("차집합 (B - A) : ", difference(B, A))