#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define GRASS_AREA 0
#define ROCK_AREA 1

const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };

// k년 동안 (x, y)에서 풀을 심었을 때 자라는 칸 수 반환
int dfs(const vector<vector<int>>& Area, vector<vector<int>>& visited, int N, int k, int x, int y, int depth) {
    // k년을 초과하면 더 이상 탐색하지 않음
    if (depth > k)
        return 0;

    // 이미 방문한 칸이면서 더 짧은 시간에 도달한 적이 있으면 탐색하지 않음
    int cnt = 0;
    if (visited[x][y] == -1) {
        visited[x][y] = depth;
        cnt = 1;
    }

    // 더 짧은 시간에 도달한 적이 있으면 갱신
    else if (visited[x][y] > depth) {
        visited[x][y] = depth;
    }

    // 이미 방문한 칸이면서 더 짧은 시간에 도달한 적이 있으면 탐색하지 않음
    else
        return 0;

    // 4방향 탐색
    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (nx >= 0 && nx < N && ny >= 0 && ny < N && Area[nx][ny] == GRASS_AREA) {
            cnt += dfs(Area, visited, N, k, nx, ny, depth + 1);
        }
    }

    return cnt;
}

int main() {
    ifstream file("input1.txt");

    // 영역 크기 N
    int N;
    file >> N;

    // 영역 정보 입력
    vector<vector<int>> Area;
    for (int i = 0; i < N; ++i) {
        vector<int> row;

        for (int j = 0; j < N; ++j) {
            int val;
            file >> val;
            row.push_back(val);
        }

        Area.push_back(row);
    }

    // k년 동안 풀을 심음
    int k;
    file >> k;

    // 최대 풀 성장 칸 수 및 위치 찾기
    int maxCnt = 0;
    int maxX = -1, maxY = -1;

    // 모든 칸에서 시작해 탐색
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (Area[i][j] == GRASS_AREA) {
                vector<vector<int>> visited(N, vector<int>(N, -1));

                int cnt = dfs(Area, visited, N, k, i, j, 0);

                if (cnt > maxCnt) {
                    maxCnt = cnt;
                    maxX = i;
                    maxY = j;
                }
            }
        }
    }

    cout << maxX << " " << maxY << endl;
    cout << maxCnt << endl;

    return 0;
}