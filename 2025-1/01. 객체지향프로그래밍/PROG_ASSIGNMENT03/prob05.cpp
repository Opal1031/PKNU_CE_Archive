#include <iostream>
#include <vector>
using namespace std;

class Othello {
public:
    // ���� ���� �� �ʱ� ���� ����
    void start_set(vector<vector<int>>& board) {
        board[3][4] = 1; // ��
        board[4][3] = 1; // ��
        board[3][3] = 2; // ��
        board[4][4] = 2; // ��
    }

    // ���� ���� ��� (0: ��ĭ, 1: ��, 2: ��)
    void print_board(const vector<vector<int>>& board) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j)
                cout << board[i][j] << " ";

            cout << endl;
        }

        cout << endl;
    }

    // ���� ������ �� ������ �� �ִ� ��� �� �� ���
    // flip = true�̸� ������ ���� ������ ���忡 ����
    int countStoneToCapture(int x, int y, int color, vector<vector<int>>& board, bool flip = false) {
        if (board[x][y] != 0)
            return 0; // �̹� ���� �ִ� ĭ���� �� �� ����

        int opponent = (color == 1) ? 2 : 1; // ��� ��
        int totalFlipped = 0;

        // 8���� ����
        int dx[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
        int dy[8] = { -1,  0,  1, 1, 1, 0, -1, -1 };

        for (int dir = 0; dir < 8; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            int count = 0;

            // ��� ���� �������� �ִ� ���� Ž��
            while (nx >= 0 && ny >= 0 && nx < 8 && ny < 8 && board[nx][ny] == opponent) {
                nx += dx[dir];
                ny += dy[dir];
                count++;
            }

            // ��� �� �ڿ� �ڱ� ���� �ִٸ� ������ �� ����
            if (count > 0 && nx >= 0 && ny >= 0 && nx < 8 && ny < 8 && board[nx][ny] == color) {
                totalFlipped += count;

                if (flip) {
                    // ���� ������
                    int fx = x + dx[dir];
                    int fy = y + dy[dir];

                    while (board[fx][fy] == opponent) {
                        board[fx][fy] = color;
                        fx += dx[dir];
                        fy += dy[dir];
                    }
                }
            }
        }

        // ���� ���� ������ ���, �ش� ��ġ�� �ڽ��� �� ����
        if (flip && totalFlipped > 0)
            board[x][y] = color;

        return totalFlipped;
    }

    // �ش� ���� �� �� �ִ� �ڸ��� �ִ��� Ȯ��
    bool hasValidMove(int color, const vector<vector<int>>& board) {
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                if (countStoneToCapture(i, j, color, const_cast<vector<vector<int>>&>(board), false) > 0)
                    return true;

        return false;
    }

    // ��ǻ��(��)�� ��: ���� ���� ������ �� �ִ� ���� ����
    bool computerMove(vector<vector<int>>& board) {
        int maxFlips = 0, bestX = -1, bestY = -1;

        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j) {
                int flips = countStoneToCapture(i, j, 2, board, false);

                if (flips > maxFlips) {
                    maxFlips = flips;
                    bestX = i;
                    bestY = j;
                }
            }

        // ���� ��ġ�� ����
        if (maxFlips > 0) {
            countStoneToCapture(bestX, bestY, 2, board, true);

            return true;
        }

        return false;
    }
};

int main() {
    vector<vector<int>> board(8, vector<int>(8, 0)); // 8x8 ���� �ʱ�ȭ
    Othello game;

    game.start_set(board); // ���� �� ��ġ

    int turn = 1; // Ȧ��: ���(��), ¦��: ��ǻ��(��)

    while (true) {
        game.print_board(board); // ���� ���� ���

        bool Player_Move = game.hasValidMove(1, board);   // ��(���)
        bool Com_Move = game.hasValidMove(2, board); // ��(��ǻ��)

        // �� �� �� �� ������ ����
        if (!Player_Move && !Com_Move)
            break;

        if (turn % 2 == 1 && Player_Move) {
            int x, y;

            cin >> x >> y; // ��� �Է�

            if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                if (game.countStoneToCapture(x, y, 1, board, false) > 0) {
                    game.countStoneToCapture(x, y, 1, board, true); // ����
                    turn++;
                }
            }
        }

        else if (turn % 2 == 0 && Com_Move) {
            if (game.computerMove(board)) {
                turn++;
            }
        }

        else {
            turn++; // ���� �Ұ� �� �� �ѱ�
        }
    }

    return 0;
}