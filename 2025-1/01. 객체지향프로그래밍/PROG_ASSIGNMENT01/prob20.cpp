#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// �� ���� : ��([0], ��([1], ��[2], ��[3]
const int move_x[4] = { -1, 1, 0, 0 };
const int move_y[4] = { 0, 0, -1, 1 };

int main() {
    int N;
    srand((unsigned int)time(NULL));

    cin >> N;

    int success = 0;

    for (int i = 0; i < 10000; i++) {
        int puppy_x = N / 2, puppy_y = N / 2; // ���� ��ġ
        int visited[100][100] = { 0 }; // �ʵ� ����
        visited[puppy_x][puppy_y] = 1; // �湮 ����� 1�� ����

        while (true) {
            // �����ڸ��� �����ϸ� Ż�� ����
            if (puppy_x == 0 || puppy_x == N - 1 || puppy_y == 0 || puppy_y == N - 1) {
                success++;
                break;
            }

            // �̵� ������ ���� ã��
            int count = 0;
            int choices[4] = { 0 };

            // �������� �����̴� ��ġ�� ������ ���� & ������ ���� �ƴ� -> �̵� ���� (choices�� ���)
            for (int j = 0; j < 4; j++) {
                int next_x = puppy_x + move_x[j], next_y = puppy_y + move_y[j];
                if (next_x >= 0 && next_x < N && next_y >= 0 && next_y < N && !visited[next_x][next_y]) {
                    choices[count++] = j;
                }
            }

            // �̵��� ���� ������ Ż�� ����
            if (count == 0) break;

            // ����ص� choices �߿��� �������� �̵� ���� ���� (������ ���� ���� ���� ���� ����)
            int tmp = choices[rand() % count];
            puppy_x += move_x[tmp];
            puppy_y += move_y[tmp];
            visited[puppy_x][puppy_y] = true;
        }
    }

    cout << (double)success / 10000 << endl;

    return 0;
}