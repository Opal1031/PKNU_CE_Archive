#include <iostream>
#include <vector>
using namespace std;

class Walker {
public:
    const int SIZE = 1001;
    const int Pos = 500;  // 원점 (0,0) → (500,500)

    vector<vector<int>> board;

    int x, y;

    // 0, 1, 2, 3의 뱡향
    int dx[4] = { 0, 1, 0, -1 };
    int dy[4] = { 1, 0, -1, 0 };

    Walker() {
        board = vector<vector<int>>(SIZE, vector<int>(SIZE, 0));

        // 시작점 표시
        x = Pos;
        y = Pos;

        board[x][y] = 1;
    }

    bool move(int dir, int len) {
        // 현재 위치를 기준으로 이동경로 확인을 위한 임시 좌표
        int nx = x;
        int ny = y;

        // 1칸씩 이동하면서 궤적 확인
        for (int i = 1; i <= len; ++i) {
            nx += dx[dir];
            ny += dy[dir];

            // 지금까지 이동한 궤적과 교차시 false 반환
            if (board[nx][ny] == 1)
                return false;
        }

        // 궤적 교차 하지 않았으면 실제 좌표 이동
        // 이동 경로 1로 변환
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

        // 종료
        if (direction == -1 && len == -1)
            break;

        // 지금까지 이동한 궤적과 교차 시 출력
        if (!game.move(direction, len))
            cout << "invalid move" << endl;

        // 교차 하지 않았을 경우 이동한 좌표 출력
        else
            game.printPosition();
    }

    return 0;
}