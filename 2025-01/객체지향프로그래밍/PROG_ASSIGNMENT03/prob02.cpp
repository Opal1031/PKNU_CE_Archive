#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Omok {
public:
    int N;
    vector<vector<int>> board;

    int dx[4] = { 0, 1, 1, 1 };
    int dy[4] = { 1, 0, 1, -1 };

    bool isWinning(int x, int y, int color) {
        // 5�� �ݺ�(���� ���±���)
        for (int tmp = 0; tmp < 4; tmp++) {
            int count = 1;

            // ����ĭ���� ���� �̾������� Ȯ��
            int nx = x + dx[tmp];
            int ny = y + dy[tmp];

            // inBounds �˻� ���� ����
            while (nx >= 0 && nx < N && ny >= 0 && ny < N && board[nx][ny] == color) {
                count++;
                nx += dx[tmp];
                ny += dy[tmp];
            }

            // ���� �ϼ�
            if (count >= 5)
                return true;
        }

        return false;
    }

    void checkWinner() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int stone = board[i][j];

                // �� ĭ�� �ǳʶ�
                if (stone == 0)
                    continue;

                // isWinning�� ���� ���� �� Ȯ�� (1�̸� Black, �ƴϸ� White)
                if (isWinning(i, j, stone)) {
                    cout << (stone == 1 ? "Black" : "White") << endl;
                    return;
                }
            }
        }

        cout << "Not Finished" << endl;
    }
};

int main() {
    int N;

    ifstream file("board.txt");
    file >> N;

    vector<vector<int>> board(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            file >> board[i][j];

    Omok game;

    game.N = N;
    game.board = board;
    game.checkWinner();

    return 0;
}