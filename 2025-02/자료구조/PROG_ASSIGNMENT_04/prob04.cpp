#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

const int MAX_SIZE = 50;

int img[MAX_SIZE][MAX_SIZE];        // 이미지 픽셀 데이터
bool visited[MAX_SIZE][MAX_SIZE];   // 방문한 픽셀 표시

// 8방향 - 2차 평면 기준
const int offset[8][2] = {
    {0, 1},    // 상
    {1, 1},    // 우상
    {1, 0},    // 우
    {1, -1},   // 우하
    {0, -1},   // 하
    {-1, -1},  // 좌하
    {-1, 0},   // 좌
    {-1, 1}    // 좌상
};

// 위치를 나타내는 구조체
struct Position {
    int x, y;

    Position() {}
    Position(int x, int y) : x(x), y(y) {}
};

void read_image(ifstream& pixel_img, int& N);                               // 이미지 파일 읽기
void reset_visited(int N);                                                  // 방문 배열 초기화
void find_components(int N, int component_sizes[], int& component_count);   // 컴포넌트 탐색
void print_components(int component_sizes[], int component_count);          // 결과 출력

int main() {
    ifstream pixel_img("input.txt");

    // 테스트 케이스 수
    int T;
    pixel_img >> T;

    int N;                                      // 이미지 크기
    int component_sizes[MAX_SIZE * MAX_SIZE];   // 이미지 컴포넌트 크기 저장 배열
    int component_count;                        // 이미지 컴포넌트 개수

    for (int t = 0; t < T; t++) {
        read_image(pixel_img, N);                               // 이미지 읽기
        reset_visited(N);                                       // 방문 배열 초기화
        find_components(N, component_sizes, component_count);   // 컴포넌트 탐색
        print_components(component_sizes, component_count);     // 결과 출력
    }

    pixel_img.close();

    return 0;
}

// 이미지 파일 읽기
void read_image(ifstream& pixel_img, int& N) {
    pixel_img >> N;

    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            pixel_img >> img[x][y];
}

// 방문 배열 초기화
void reset_visited(int N) {
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            visited[x][y] = false;
}

// 컴포넌트 탐색
void find_components(int N, int component_sizes[], int& component_count) {
    component_count = 0;

    // 모든 픽셀 탐색
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            // 새로운 컴포넌트 발견
            if (img[x][y] == 1 && !visited[x][y]) {
                int cnt = 0;    // 컴포넌트 크기 카운트

                stack<Position> s;      // 픽셀 위치 스택
                s.push(Position(x, y)); // 시작 픽셀 위치 푸시
                visited[x][y] = true;   // 방문 표시

                while (!s.empty()) {
                    // 현재 픽셀 위치 pop
                    Position p = s.top();
                    s.pop();

                    cnt++;  // 컴포넌트 크기 증가

                    // 8방향 탐색
                    for (int d = 0; d < 8; d++) {
                        int nx = p.x + offset[d][0];
                        int ny = p.y + offset[d][1];

                        if (nx >= 0 && nx < N && ny >= 0 && ny < N && img[nx][ny] == 1 && !visited[nx][ny]) {
                            s.push(Position(nx, ny));

                            visited[nx][ny] = true;
                        }
                    }
                }

                component_sizes[component_count++] = cnt;   // 컴포넌트 크기 저장
            }
        }
    }
}

// 결과 출력
void print_components(int component_sizes[], int component_count) {
    for (int i = 0; i < component_count; i++)
        cout << component_sizes[i] << " ";

    cout << endl;
}