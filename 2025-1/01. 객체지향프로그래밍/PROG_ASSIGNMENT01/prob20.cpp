#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// 네 방향 : 상([0], 하([1], 좌[2], 우[3]
const int move_x[4] = { -1, 1, 0, 0 };
const int move_y[4] = { 0, 0, -1, 1 };

int main() {
    int N;
    srand((unsigned int)time(NULL));

    cin >> N;

    int success = 0;

    for (int i = 0; i < 10000; i++) {
        int puppy_x = N / 2, puppy_y = N / 2; // 시작 위치
        int visited[100][100] = { 0 }; // 필드 지정
        visited[puppy_x][puppy_y] = 1; // 방문 기록을 1로 변경

        while (true) {
            // 가장자리에 도달하면 탈출 성공
            if (puppy_x == 0 || puppy_x == N - 1 || puppy_y == 0 || puppy_y == N - 1) {
                success++;
                break;
            }

            // 이동 가능한 방향 찾기
            int count = 0;
            int choices[4] = { 0 };

            // 다음으로 움직이는 위치가 범위에 속함 & 지나간 곳이 아님 -> 이동 가능 (choices에 등록)
            for (int j = 0; j < 4; j++) {
                int next_x = puppy_x + move_x[j], next_y = puppy_y + move_y[j];
                if (next_x >= 0 && next_x < N && next_y >= 0 && next_y < N && !visited[next_x][next_y]) {
                    choices[count++] = j;
                }
            }

            // 이동할 곳이 없으면 탈출 실패
            if (count == 0) break;

            // 등록해둔 choices 중에서 랜덤으로 이동 방향 선택 (가능한 가짓 수를 방향 수로 나눔)
            int tmp = choices[rand() % count];
            puppy_x += move_x[tmp];
            puppy_y += move_y[tmp];
            visited[puppy_x][puppy_y] = true;
        }
    }

    cout << (double)success / 10000 << endl;

    return 0;
}