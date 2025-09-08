#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // ���� ����
    int n;
    cin >> n;

    // �迭 ũ��, �ִ� �˻� ����, �迭
    int size = n - 1;
    int limit = sqrt(n);
    int* data = new int[size];

    for (int i = 0; i < size; i++) {
        data[i] = i + 2;
    }

    // �����佺�׳׽��� ü
    // n�� �����ٱ����� Ȯ�� -> ���ʿ��� �ݺ� ����
    for (int p = 0; (p < size) && (data[p] <= limit); p++) {
        int div = data[p];

        for (int q = p + 1; q < size;) {
            // �Ҽ��� �ƴ� �� ����
            if (data[q] % div == 0) {
                for (int k = q; k < size - 1; k++) {
                    data[k] = data[k + 1];
                }

                // �迭 ũ�� ���̱�
                size--;

                int* tmp = new int[size];

                for (int k = 0; k < size; k++) {
                    tmp[k] = data[k];
                }

                delete[] data;

                data = tmp;
            }

            // �Ҽ��� ����� �ƴ� ���� ���� ���� �̵�
            else {
                q++;
            }
        }
    }

    // ��� ���
    for (int prime = 0; prime < size; prime++) {
        cout << data[prime] << " ";
    }

    delete[] data;

    return 0;
}