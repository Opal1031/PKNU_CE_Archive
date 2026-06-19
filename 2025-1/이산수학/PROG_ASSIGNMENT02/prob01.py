# 해쉬함수 h(n) = n mod 11
def hash(a):
    return a % 11

# 크기가 11인 배열을 초기화(0으로 초기화)
list = [0 for i in range(11)]

# 총 10개의 정수 입력
for i in range(10):
    # 정수 하나씩 입력받기
    input_data = int(input("정수 입력 : "))
    
    # hash 함수로 hash_data(11로 나눴을 때의 나머지) 구하기
    hash_data = hash(input_data)

    # 만약 hash_data에 해당하는 list값이 없다면, 해당 인덱스에 저장
    if (list[hash_data] == 0):
        list[hash_data] = input_data

    # hash_data에 해당하는 list값이 있다면 Collision 출력
    else:
        print("Collision!")

        # 빈 인덱스까지 idx값 증가 후 저장
        idx = hash_data

        while(True):
            if (list[idx] == 0):
                list[idx] = input_data
                hash_data = idx
                break
            # 순환 인덱스
            else:
                if (idx == 10):
                    idx = 0
                else:
                    idx += 1

    # 출력
    print("저장된 배열의 위치 인덱스 : ", hash_data)
    print("배열 : ", list)