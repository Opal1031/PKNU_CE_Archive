#include <iostream>
#include <vector>
using namespace std;

class Othello {
public:
    // 게임 시작 시 초기 보드 설정
    void start_set(vector<vector<int>>& board) {
        board[3][4] = 1; // 흑
        board[4][3] = 1; // 흑
        board[3][3] = 2; // 백
        board[4][4] = 2; // 백
    }

    // 보드 상태 출력 (0: 빈칸, 1: 흑, 2: 백)
    void print_board(const vector<vector<int>>& board) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j)
                cout << board[i][j] << " ";

            cout << endl;
        }

        cout << endl;
    }

    // 돌을 놓았을 때 뒤집을 수 있는 상대 돌 수 계산
    // flip = true이면 실제로 돌을 뒤집고 보드에 적용
    int countStoneToCapture(int x, int y, int color, vector<vector<int>>& board, bool flip = false) {
        if (board[x][y] != 0)
            return 0; // 이미 돌이 있는 칸에는 둘 수 없음

        int opponent = (color == 1) ? 2 : 1; // 상대 색
        int totalFlipped = 0;

        // 8방향 정의
        int dx[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
        int dy[8] = { -1,  0,  1, 1, 1, 0, -1, -1 };

        for (int dir = 0; dir < 8; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            int count = 0;

            // 상대 돌이 연속으로 있는 방향 탐색
            while (nx >= 0 && ny >= 0 && nx < 8 && ny < 8 && board[nx][ny] == opponent) {
                nx += dx[dir];
                ny += dy[dir];
                count++;
            }

            // 상대 돌 뒤에 자기 돌이 있다면 뒤집을 수 있음
            if (count > 0 && nx >= 0 && ny >= 0 && nx < 8 && ny < 8 && board[nx][ny] == color) {
                totalFlipped += count;

                if (flip) {
                    // 실제 뒤집기
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

        // 돌을 놓고 뒤집은 경우, 해당 위치에 자신의 돌 놓기
        if (flip && totalFlipped > 0)
            board[x][y] = color;

        return totalFlipped;
    }

    // 해당 색이 둘 수 있는 자리가 있는지 확인
    bool hasValidMove(int color, const vector<vector<int>>& board) {
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                if (countStoneToCapture(i, j, color, const_cast<vector<vector<int>>&>(board), false) > 0)
                    return true;

        return false;
    }

    // 컴퓨터(백)의 턴: 가장 많이 뒤집을 수 있는 곳에 착수
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

        // 최적 위치에 착수
        if (maxFlips > 0) {
            countStoneToCapture(bestX, bestY, 2, board, true);

            return true;
        }

        return false;
    }
};

int main() {
    vector<vector<int>> board(8, vector<int>(8, 0)); // 8x8 보드 초기화
    Othello game;

    game.start_set(board); // 시작 돌 배치

    int turn = 1; // 홀수: 사람(흑), 짝수: 컴퓨터(백)

    while (true) {
        game.print_board(board); // 현재 보드 출력

        bool Player_Move = game.hasValidMove(1, board);   // 흑(사람)
        bool Com_Move = game.hasValidMove(2, board); // 백(컴퓨터)

        // 둘 다 둘 수 없으면 종료
        if (!Player_Move && !Com_Move)
            break;

        if (turn % 2 == 1 && Player_Move) {
            int x, y;

            cin >> x >> y; // 사람 입력

            if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                if (game.countStoneToCapture(x, y, 1, board, false) > 0) {
                    game.countStoneToCapture(x, y, 1, board, true); // 착수
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
            turn++; // 착수 불가 시 턴 넘김
        }
    }

    return 0;
}