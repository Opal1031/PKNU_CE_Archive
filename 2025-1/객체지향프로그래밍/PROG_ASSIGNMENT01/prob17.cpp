#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
    int N = 0, length = 1, Max_length = 0;
    int data[MAX] = { 0 };

    cin >> N;

    // 데이터 입력
    for (int i = 0; i < N; i++) {
        cin >> data[i];
    }

    // 두 번째 값부터 데이터 입력 (첫 번째 데이터 -> 이전값 없음 -> 확인 필요 X, length = 1로 시작한 이유)
    for (int j = 1; j < N; j++) {
        // 이전의 값보다 크거나 같으면 length++
        if (data[j] >= data[j - 1]) {
            length++;

            // 바뀐 length값이 기존의 Max_length보다 크면 값 변경
            if (length >= Max_length) {
                Max_length = length;
            }
        }

        // 이전의 값보다 작으면 length 초기화
        else
            length = 1;
    }

    cout << Max_length << endl;

    return 0;
}