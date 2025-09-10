#include <iostream>
#include <vector>
using namespace std;

class Walker {
public:
    const int SIZE = 1001;
    const int Pos = 500;  // ���� (0,0) �� (500,500)

    vector<vector<int>> board;

    int x, y;

    // 0, 1, 2, 3�� ����
    int dx[4] = { 0, 1, 0, -1 };
    int dy[4] = { 1, 0, -1, 0 };

    Walker() {
        board = vector<vector<int>>(SIZE, vector<int>(SIZE, 0));

        // ������ ǥ��
        x = Pos;
        y = Pos;

        board[x][y] = 1;
    }

    bool move(int dir, int len) {
        // ���� ��ġ�� �������� �̵���� Ȯ���� ���� �ӽ� ��ǥ
        int nx = x;
        int ny = y;

        // 1ĭ�� �̵��ϸ鼭 ���� Ȯ��
        for (int i = 1; i <= len; ++i) {
            nx += dx[dir];
            ny += dy[dir];

            // ���ݱ��� �̵��� ������ ������ false ��ȯ
            if (board[nx][ny] == 1)
                return false;
        }

        // ���� ���� ���� �ʾ����� ���� ��ǥ �̵�
        // �̵� ��� 1�� ��ȯ
        for (int i = 1; i <= len; ++i) {
            x += dx[dir];
            y += dy[dir];

            board[x][y] = 1;
        }

        return true;
    }

    void printPosition() {
        cout << (x - Pos) << " " << (y - Pos) << endl;
    }
};

int main() {
    Walker game;

    while (true) {
        int direction, len;

        cout << endl;
        cin >> direction >> len;

        // ����
        if (direction == -1 && len == -1)
            break;

        // ���ݱ��� �̵��� ������ ���� �� ���
        if (!game.move(direction, len))
            cout << "invalid move" << endl;

        // ���� ���� �ʾ��� ��� �̵��� ��ǥ ���
        else
            game.printPosition();
    }

    return 0;
}