# 리스트 입력 함수
# 원소들을 입력 후, 0을 입력하면 집합 입력 종료
def get_input_set():
    A = list(map(int, input("집합의 원소를 공백으로 구분하여 입력 (마지막에 0 입력): ").split()))
    return A[:-1]  # 마지막 0 제거

# 멱집합 생성
def generate_power_set(arr):
    n = len(arr)
    power_set = []
    
    for i in range(1 << n):  # 원소의 개수는 2^n 개(부분집합)
        subset = []

        for j in range(n):
            if i & (1 << j):  # j번째 원소가 부분집합에 포함되는지 확인
                subset.append(arr[j])

        power_set.append(subset)
    
    return power_set

# main 함수
def main():
    input_set = get_input_set() # 전체 원소 입력
    power_set = generate_power_set(input_set) # 멱집합 생성
    
    print("\n멱집합:")

    for subset in power_set:
        print(subset)

if __name__ == "__main__":
    main()