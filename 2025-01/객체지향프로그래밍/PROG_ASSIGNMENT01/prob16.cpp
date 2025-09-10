#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
    int N = 0, count = 0;
    int data[MAX] = {};

    cin >> N;

    // 데이터 입력
    for (int i = 0; i < N; i++) {
        cin >> data[i];
    }

    // j가 k보다 크면 카운트
    for (int j = 0; j < N; j++) {
        for (int k = j + 1; k < N; k++) {
            if (data[j] > data[k])
                count++;
        }
    }

    cout << count << endl;

    return 0;
}