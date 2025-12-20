#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

const int MAX_N = 16;

int board[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

int N;

// 상, 하, 좌, 우
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

bool bfs(int sx, int sy, int ex, int ey) {
    queue<pair<int, int>> q;

    q.push({ sx, sy });
    visited[sx][sy] = true;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;

        q.pop();

        if (x == ex && y == ey) {
            return true;
        }

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // 말을 하나라도 뛰어넘어야 하므로, 인접칸부터 쭉 진행
            bool jumped = false;

            while (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                if (board[nx][ny] == 1) {
                    // 말을 만났으면, 그 다음 칸부터 탐색
                    nx += dx[dir];
                    ny += dy[dir];

                    jumped = true;

                    break;
                }

                nx += dx[dir];
                ny += dy[dir];
            }

            // 말을 뛰어넘은 경우에만, 그 다음 칸부터 계속 진행
            if (jumped) {
                while (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                    if (board[nx][ny] == 0 && !visited[nx][ny]) {
                        visited[nx][ny] = true;
                        q.push({ nx, ny });
                    }

                    else if (board[nx][ny] == 1) {
                        break;
                    }

                    nx += dx[dir];
                    ny += dy[dir];
                }
            }
        }
    }

    return false;
}

int main() {
    ifstream file("input8.txt");
    file >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            file >> board[i][j];
        }
    }

    int sx, sy, ex, ey;

    file >> sx >> sy;
    file >> ex >> ey;
    file.close();

    // 방문 배열 초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = false;
        }
    }

    if (bfs(sx, sy, ex, ey)) {
        cout << "Yes" << endl;
    }

    else {
        cout << "No" << endl;
    }

    return 0;
}