# 원소의 개수 입력 및 리스트 생성
N = int(input("원소의 개수 : "))
arr = [0 for i in range(N)]

# N개의 양의 정수 입력
for i in range(N):
    arr[i] = int(input())

# 삽입 정렬 알고리즘 구현
for j in range(1, N):
    i = 0

    # 알맞은 위치 찾기
    while arr[j] > arr[i]:
        i += 1

    m = arr[j]

    # 오른쪽으로 한 칸씩 이동
    for k in range(j, i, -1):
        arr[k] = arr[k - 1]

    # m을 올바른 위치에 삽입
    arr[i] = m

# 삽입정렬 이후 리스트 출력
print("정렬된 리스트 : ", arr)

# 검색할 값 입력
Find = int(input("검색할 원소 : "))

# 이진 탐색
p = 0            # 왼쪽 끝 인덱스
r = N - 1        # 오른쪽 끝 인덱스

while p < r:
    # 범위 내 중앙에 위치한 값
    q = (p + r) // 2

    # 크기 비교 후 범위 재지정
    if (Find > arr[q]):
        p = q + 1
    else:
        r = q

# 찾고자 하는 값의 저장 위치 출력
if p < N and arr[p] == Find:
    print("저장된 위치 :", p + 1)
else:
    print("0")