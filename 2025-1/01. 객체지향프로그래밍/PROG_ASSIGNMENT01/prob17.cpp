#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
    int N = 0, length = 1, Max_length = 0;
    int data[MAX] = { 0 };

    cin >> N;

    // ������ �Է�
    for (int i = 0; i < N; i++) {
        cin >> data[i];
    }

    // �� ��° ������ ������ �Է� (ù ��° ������ -> ������ ���� -> Ȯ�� �ʿ� X, length = 1�� ������ ����)
    for (int j = 1; j < N; j++) {
        // ������ ������ ũ�ų� ������ length++
        if (data[j] >= data[j - 1]) {
            length++;

            // �ٲ� length���� ������ Max_length���� ũ�� �� ����
            if (length >= Max_length) {
                Max_length = length;
            }
        }

        // ������ ������ ������ length �ʱ�ȭ
        else
            length = 1;
    }

    cout << Max_length << endl;

    return 0;
}