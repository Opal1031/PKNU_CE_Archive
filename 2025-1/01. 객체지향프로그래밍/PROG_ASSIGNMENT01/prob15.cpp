#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
    int N = 0, start = 0, end = 0, min = 0, tmp = 0;
    int mat[MAX][2] = {};

    // �Է¹��� ���� ����
    cin >> N;

    // ������ �Է�
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> mat[i][j];
        }
    }

    // ������ ���� ����
    for (int p = 0; p < N; p++) {
        for (int q = p; q < N; q++) {

            // ���� �ּҰ��� ã�� ���� ����
            if (q == p) {
                start = mat[q][0];
                end = mat[q][1];
                min = q;
            }

            // �� ���� �������� ����� �ּҰ� ����
            else if (start > mat[q][0]) {
                mat[q][0] == start;
                mat[q][1] == end;
                min = q;
            }

            // �������� ������ ������ �� �� ������ �ּҰ� ����
            else if (start == mat[q][0]) {
                if (end > mat[q][1]) {
                    mat[q][0] == start;
                    mat[q][1] == end;
                    min = q;
                }
            }
        }

        // ã�� �ּҰ��� ������ ���� ����(p) -> ����
        for (int r = 0; r < 2; r++) {
            tmp = mat[p][r];
            mat[p][r] = mat[min][r];
            mat[min][r] = tmp;
        }

        start = 0, end = 0;
    }

    // ������ ���
    for (int l = 0; l < N; l++) {
        cout << mat[l][0] << " " << mat[l][1] << endl;
    }

    return 0;
}