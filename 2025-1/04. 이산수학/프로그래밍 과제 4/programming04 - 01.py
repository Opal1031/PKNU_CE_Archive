import random
import math

# 랜덤한 소수 생성 함수
def is_PrimeNum(x):
    if (x < 2):
        return False
    
    for i in range(2, int(math.sqrt(x)) + 1):
        # 소수가 아닌 경우 False 반환
        if (x % i == 0):
            return False

    # 소수인 경우 True 반환
    return True

# 확장된 유클리드 알고리즘 함수
def extended_gcd(a, b):
    if (a < b):
        a, b = b, a

    # 예외) b가 0인 경우
    if (b == 0):
        return a, 1, 0

    r = a % b
    gcd, x1, y1 = extended_gcd(b, r)

    x = y1
    y = x1 - (a // b) * y1
    
    return gcd, x, y

# 제곱 함수
def repeated_squaring(a, n, z):
    result = 1
    base = a % z

    while (n > 0):
        if (n % 2 == 1):
            result = (result * base) % z
        
        base = (base * base) % z
        n //= 2

    return result

# 랜덤 p 생성
while (True):
    p = random.randint(1, 100)

    if is_PrimeNum(p):
        break

# 랜덤 q 생성
while (True):
    q = random.randint(1, 100)

    if is_PrimeNum(q):
        break

# z, phi, n, s값 생성
z = p * q
phi = (p - 1) * (q - 1)
n = 65537 #가장 대중적인 값
gcd, x, y = extended_gcd(n, phi)
s = x % phi

print("해당 프로그래밍 리포트에서는 결과값 확인을 위해 모든 변수의 값을 출력해둔다.")
print("")

print("p : %d" %p)
print("q : %d" %q)
print("공개키(z, n) : (%d, %d)" %(z, n))
print("개인키(s) : %d" %s)

print("")

Enc_A, Enc_Z, Enc_N = map(int, input("평문 메시지로 정수 a, 공개키 (z, n)을 입력하시오 : ").split())
print("암호문 메시지 :", repeated_squaring(Enc_A, Enc_N, Enc_Z))

print("")

Dec_C, Dec_Z, Dec_S = map(int, input("암호문 c와 z, 그리고 개인키 s를 입력 하시오. : ").split())
print("평문 메시지 :", repeated_squaring(Dec_C, Dec_S, Dec_Z))