#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define PATHWAY_COLOUR 0
#define WALL_COLOUR    1

int N;
int maze[100][100];

// 4방향 이동
int offsets[4][2] = {
    { -1, 0 },
    { 1, 0 },
    { 0, -1 },
    { 0, 1 }
};

int min_bends;              // 최소 꺾임 횟수
int visited[100][100][4];   // [x][y][dir]: (x,y)에 dir방향으로 도달할 때의 최소 꺾임 수

// DFS로 (x, y) 위치에 dir 방향, bends번 꺾임으로 도달
void dfs(int x, int y, int dir, int bends) {
    // 도착점 도달
    if (x == N - 1 && y == N - 1) {
        if (min_bends == -1 || bends < min_bends)
            min_bends = bends;

        return;
    }

    // 4방향 탐색
    for (int nd = 0; nd < 4; ++nd) {
        int nx = x + offsets[nd][0];
        int ny = y + offsets[nd][1];

        // 방향이 바뀌면 꺾임 추가
        int nbends = bends + (dir != -1 && dir != nd ? 1 : 0);

        if (nx >= 0 && ny >= 0 && nx < N && ny < N && maze[nx][ny] == PATHWAY_COLOUR) {
            // 더 적은 꺾임으로 방문할 때만 진행
            if (visited[nx][ny][nd] == -1 || visited[nx][ny][nd] > nbends) {
                visited[nx][ny][nd] = nbends;

                dfs(nx, ny, nd, nbends);
            }
        }
    }
}

// 최소 꺾임 횟수 계산
int minBendsDFS() {
    min_bends = -1;

    // 방문 배열 초기화
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int d = 0; d < 4; ++d)
                visited[i][j][d] = -1;

    // 시작점에서 4방향 모두 시도
    for (int d = 0; d < 4; ++d) {
        visited[0][0][d] = 0;

        dfs(0, 0, d, 0);
    }

    return min_bends;
}

int main() {
    ifstream file("input2.txt");
    file >> N;

    // 미로 입력
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            file >> maze[i][j];

    // 최소 꺾임 횟수 출력
    cout << minBendsDFS() << endl;

    return 0;
}