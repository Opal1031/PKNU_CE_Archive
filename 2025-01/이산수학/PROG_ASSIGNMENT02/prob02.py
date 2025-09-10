# 초기값 입력
m, a, c, s = map(int, input("모듈러(modulus), multiflier, increment, seed를 입력 : ").split())

# 생성할 난수의 개수 입력
num = int(input("생성할 난수의 개수 : "))

list = [0 for i in range(num)]

for i in range(num):
    # 예외처리) 첫 번째 값(list[0])은 seed 값
    if (i == 0):
        list[0] = s
    # 예제의 난수 생성 공식에 따라 값 계산 후 저장
    else:
        list[i] = (a * list[i - 1] + c) % 11

# 출력
print("생성한 난수 : ", list)