#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Rect {
private:
    int x1, x2, y1, y2;

public:
    Rect(int x_min, int x_max, int y_min, int y_max) {
        x1 = x_min;
        x2 = x_max;
        y1 = y_min;
        y2 = y_max;
    }

    // 사각형과 셀의 영역이 겹치는지 판별
    bool intersects(int x_left, int x_right, int y_bottom, int y_top) const {
        return x_left < x2 && x_right > x1 && y_bottom < y2 && y_top > y1;
    }
};

int main() {
    ifstream fin("input3.txt");
    int N;
    fin >> N;

    vector<int> x_coords, y_coords;
    vector<Rect*> rects;

    for (int i = 0; i < N; ++i) {
        int x1, x2, y1, y2;
        fin >> x1 >> x2 >> y1 >> y2;
        rects.push_back(new Rect(x1, x2, y1, y2));

        // 좌표 분할 기준이 될 모든 수직선/수평선 좌표 수집
        x_coords.push_back(x1);
        x_coords.push_back(x2);
        y_coords.push_back(y1);
        y_coords.push_back(y2);
    }

    // 좌표 정렬 및 중복 제거
    sort(x_coords.begin(), x_coords.end());
    x_coords.erase(unique(x_coords.begin(), x_coords.end()), x_coords.end());

    sort(y_coords.begin(), y_coords.end());
    y_coords.erase(unique(y_coords.begin(), y_coords.end()), y_coords.end());

    int total_area = 0;

    // 좌표로 만들어지는 각 셀을 반복
    for (size_t i = 0; i < x_coords.size() - 1; ++i) {
        for (size_t j = 0; j < y_coords.size() - 1; ++j) {
            // 셀의 (x_left, y_bottom), (x_right, y_top) 좌표
            int x_left = x_coords[i];
            int x_right = x_coords[i + 1];
            int y_bottom = y_coords[j];
            int y_top = y_coords[j + 1];

            // 이 셀이 하나라도 사각형에 포함되면 면적 추가
            for (Rect* r : rects) {
                if (r->intersects(x_left, x_right, y_bottom, y_top)) {
                    // 셀 면적 계산 후 더함
                    int area = (x_right - x_left) * (y_top - y_bottom);
                    total_area += area;
                    break;  // 하나만 겹쳐도 되므로 break
                }
            }
        }
    }

    cout << total_area << endl;

    // 동적 할당된 사각형 메모리 해제
    for (Rect* r : rects) {
        delete r;
    }

    return 0;
}