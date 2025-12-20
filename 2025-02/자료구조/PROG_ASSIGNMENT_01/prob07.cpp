#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // 정수 개수
    int n;
    cin >> n;

    // 배열 크기, 최대 검색 범위, 배열
    int size = n - 1;
    int limit = sqrt(n);
    int* data = new int[size];

    for (int i = 0; i < size; i++) {
        data[i] = i + 2;
    }

    // 에라토스테네스의 체
    // n의 제곱근까지만 확인 -> 불필요한 반복 제거
    for (int p = 0; (p < size) && (data[p] <= limit); p++) {
        int div = data[p];

        for (int q = p + 1; q < size;) {
            // 소수가 아닌 수 제거
            if (data[q] % div == 0) {
                for (int k = q; k < size - 1; k++) {
                    data[k] = data[k + 1];
                }

                // 배열 크기 줄이기
                size--;

                int* tmp = new int[size];

                for (int k = 0; k < size; k++) {
                    tmp[k] = data[k];
                }

                delete[] data;

                data = tmp;
            }

            // 소수의 배수가 아닌 수는 다음 수로 이동
            else {
                q++;
            }
        }
    }

    // 결과 출력
    for (int prime = 0; prime < size; prime++) {
        cout << data[prime] << " ";
    }

    delete[] data;

    return 0;
}