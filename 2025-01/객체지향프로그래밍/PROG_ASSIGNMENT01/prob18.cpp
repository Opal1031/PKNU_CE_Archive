#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
    int N = 0, K = 0, sum = 0;
    int idx = 0, real_idx = 0;
    int length = 1, Max_length = 0;
    int data[MAX] = { 0 };

    cin >> N;

    // ������ �Է�
    for (int i = 0; i < N; i++) {
        cin >> data[i];
    }

    cin >> K;

    // Ž�� ����
    while (idx < N) {
        sum += data[idx];

        // ���� K���� ������ ���� �� ���ϱ� / ���� + 1
        if (sum < K) {
            idx++;
            length++;
        }

        // ���� K�� �ʰ��ϸ� ���� ������(real_idx), ���� & �� �ʱ�ȭ
        else {
            real_idx++;
            idx = real_idx;
            length = 0;
            sum = 0;
        }

        // ���� ���̰� �ִ�ġ�� �����ϸ� �� ����
        if (length >= Max_length) {
            Max_length = length;
        }
    }

    cout << Max_length << endl;

    return 0;
}