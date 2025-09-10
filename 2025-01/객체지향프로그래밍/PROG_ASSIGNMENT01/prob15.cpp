#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
    int N = 0, start = 0, end = 0, min = 0, tmp = 0;
    int mat[MAX][2] = {};

    // 입력받을 개수 설정
    cin >> N;

    // 데이터 입력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> mat[i][j];
        }
    }

    // 데이터 순서 변경
    for (int p = 0; p < N; p++) {
        for (int q = p; q < N; q++) {

            // 현재 최소값을 찾기 위한 설정
            if (q == p) {
                start = mat[q][0];
                end = mat[q][1];
                min = q;
            }

            // 더 작은 시작점이 생기면 최소값 변경
            else if (start > mat[q][0]) {
                mat[q][0] == start;
                mat[q][1] == end;
                min = q;
            }

            // 시작점이 같으면 끝점을 비교 후 작으면 최소값 변경
            else if (start == mat[q][0]) {
                if (end > mat[q][1]) {
                    mat[q][0] == start;
                    mat[q][1] == end;
                    min = q;
                }
            }
        }

        // 찾은 최소값을 현재의 값과 변경(p) -> 정렬
        for (int r = 0; r < 2; r++) {
            tmp = mat[p][r];
            mat[p][r] = mat[min][r];
            mat[min][r] = tmp;
        }

        start = 0, end = 0;
    }

    // 데이터 출력
    for (int l = 0; l < N; l++) {
        cout << mat[l][0] << " " << mat[l][1] << endl;
    }

    return 0;
}