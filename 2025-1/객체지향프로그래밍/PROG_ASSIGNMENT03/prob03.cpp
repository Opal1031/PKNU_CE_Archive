#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Segment {
public:
    int x1, y1, x2, y2;
    bool isVertical;

    Segment(int a, int b, int c, int d) {
        x1 = a; y1 = b; x2 = c; y2 = d;

        // 수직선 여부 확인(두 좌표의 X값이 같은지) -> 수직선이 아니라면 무조건 수평선
        isVertical = (x1 == x2);

        // 수직선인 경우 더 큰 y좌표값이 먼저 입력되었으면 swap
        if (isVertical && y1 > y2)
            swap(y1, y2);
        // 수평선인 경우 더 큰 x좌표값이 먼저 입력되었으면 swap
        if (!isVertical && x1 > x2)
            swap(x1, x2);
    }
};

bool intersect(Segment& a, Segment& b, int& x, int& y) {
    // 두 선분이 같은 성분이면 교차하지 않음
    if (a.isVertical == b.isVertical)
        return false;

    // 하나는 수직, 하나는 수평으로 분리
    Segment& vert = a.isVertical ? a : b;
    Segment& hori = a.isVertical ? b : a;

    // 교차할 수 있는 좌표는 수직선의 x, 수평선의 y
    x = vert.x1;
    y = hori.y1;

    // 실제 교차하는지 확인 (vert & hori 값이 각각의 선분 위에 존재하는지 확인)
    if (x >= hori.x1 && x <= hori.x2 && y >= vert.y1 && y <= vert.y2)
        return true;

    return false;
}

int main() {
    // 입력할 선분 개수
    int N;
    cin >> N;

    // 입력 받은 좌표값을 Segment 저장
    vector<Segment> segments;
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        segments.push_back(Segment(x1, y1, x2, y2));
    }

    // 교차점 저장 벡터
    vector<vector<int>> cross;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int x, y;

            // intersect에 해당값들은 넣은 return값이 True이면 cross 벡터에 저장
            if (intersect(segments[i], segments[j], x, y))
                cross.push_back({ x, y });
        }
    }

    // 정렬
    sort(cross.begin(), cross.end());

    // 중복 제거
    cross.erase(unique(cross.begin(), cross.end()), cross.end());

    // 출력
    for (int i = 0; i < cross.size(); i++)
        cout << "[" << cross[i][0] << ", " << cross[i][1] << "]\n";

    return 0;
}