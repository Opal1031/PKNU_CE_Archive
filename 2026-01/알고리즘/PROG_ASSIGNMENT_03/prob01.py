import sys
import os

def dupdetect(target_dir):
    # 4. 해시 테이블 크기 T는 2099로 고정합니다.
    T = 2099
    
    # 4 & 5. chaining 기법을 위한 해시 테이블 초기화 (list의 list 구조)
    hash_table = [[] for _ in range(T)]

    # 7. OS 의존적인 폴더 탐색 (os.walk 사용)
    for root, dirs, files in os.walk(target_dir):
        for file in files:
            # 파일의 전체 경로 구성 및 출력 포맷에 맞게 슬래시 통일
            path = os.path.join(root, file).replace('\\', '/')
            
            # 1. 파일 전체를 하나의 string으로 읽어들임
            try:
                with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()

            except Exception as e:
                print(f"Error reading {path}: {e}")
                continue

            # 2. 파일 내용(content)을 해시 함수로 해시
            hashcode = hash(content)
            
            # 해시코드를 테이블 크기로 나누어 주소(address) 계산
            address = hashcode % T
            
            # 6. 해시 테이블에서 동일한 해시 코드를 가지는 파일(중복 파일) 검사
            is_duplicate = False

            for stored_hash, stored_path in hash_table[address]:
                if (stored_hash == hashcode):
                    # 중복된 파일임이 확인되면 결과 출력
                    print(f"#Removing {path} (duplicate of {stored_path}).")

                    is_duplicate = True

                    # 중복 확인 후 더 이상 탐색하지 않음
                    break
            
            # 3. 중복된 파일이 없으면 테이블에 경로명(path)과 해시코드(hashcode)를 tuple로 저장
            if not is_duplicate:
                hash_table[address].append((hashcode, path))

if __name__ == "__main__":
    # 커맨드라인 매개변수(command line argument) 처리
    if (len(sys.argv) < 2):
        print("사용법: python dupdetect.py <디렉토리 경로>")
        sys.exit(1)
        
    target_directory = sys.argv[1]
    dupdetect(target_directory)