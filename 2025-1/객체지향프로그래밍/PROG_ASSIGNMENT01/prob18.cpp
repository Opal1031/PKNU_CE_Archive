#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
    int N = 0, K = 0, sum = 0;
    int idx = 0, real_idx = 0;
    int length = 1, Max_length = 0;
    int data[MAX] = { 0 };

    cin >> N;

    // 데이터 입력
    for (int i = 0; i < N; i++) {
        cin >> data[i];
    }

    cin >> K;

    // 탐색 시작
    while (idx < N) {
        sum += data[idx];

        // 합이 K보다 작으면 다음 값 더하기 / 구간 + 1
        if (sum < K) {
            idx++;
            length++;
        }

        // 합이 K를 초과하면 다음 시작점(real_idx), 길이 & 합 초기화
        else {
            real_idx++;
            idx = real_idx;
            length = 0;
            sum = 0;
        }

        // 구간 길이가 최대치를 갱신하면 값 변경
        if (length >= Max_length) {
            Max_length = length;
        }
    }

    cout << Max_length << endl;

    return 0;
}