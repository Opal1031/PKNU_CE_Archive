#include <iostream>
#include <vector>

using namespace std;

const int PATHWAY_COLOR = 0;
const int WALL_COLOR = 1;
const int PATH_COLOR = 2;
const int BLOCKED_COLOR = 3;

int N;

vector<vector<int>> maze;
vector<vector<bool>> visited;

// (x, y)에서 출구까지 경로가 존재하는지 확인
bool findMazePath(int x, int y) {
    if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] != PATHWAY_COLOR)
        return false;

    // 출구 도달
    else if (x == N - 1 && y == N - 1) {
        maze[x][y] = PATH_COLOR; // 경로 표시

        return true;
    }

    else {
        maze[x][y] = PATH_COLOR; // 경로 표시

        // 상, 우, 하, 좌 순서로 이동
        if (findMazePath(x - 1, y) || findMazePath(x, y + 1) || findMazePath(x + 1, y) || findMazePath(x, y - 1))
            return true;

        maze[x][y] = BLOCKED_COLOR; // 막힌 길 표시

        return false;
    }
}

// (x, y)에서 출구까지 갈 수 있는 모든 경로의 개수 세기
int countAllPaths(int x, int y) {
    if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] != PATHWAY_COLOR || visited[x][y])
        return 0;

    if (x == N - 1 && y == N - 1)
        return 1;

    visited[x][y] = true;

    int total = 0;

    // 상, 우, 하, 좌 방향으로 이동하며 경로 개수 합산
    total += countAllPaths(x - 1, y);
    total += countAllPaths(x, y + 1);
    total += countAllPaths(x + 1, y);
    total += countAllPaths(x, y - 1);

    visited[x][y] = false;

    return total;
}

int main() {
    cin >> N;

    maze = vector<vector<int>>(N, vector<int>(N));
    visited = vector<vector<bool>>(N, vector<bool>(N, false));

    // 미로 정보 입력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> maze[i][j];
        }
    }

    // (0,0)에서 출구까지의 경로 개수 출력
    cout << countAllPaths(0, 0) << endl;

    return 0;
}