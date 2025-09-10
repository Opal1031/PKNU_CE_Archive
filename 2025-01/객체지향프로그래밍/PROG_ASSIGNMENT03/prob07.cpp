#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// 직사각형에 대한 class
class Rect {
public:
    int X_min, X_max, Y_min, Y_max;

    // 직사각형의 4 꼭지점
    Rect() {
        X_min = 0, X_max = 0, Y_min = 0, Y_max = 0;
    }

    Rect(int x1, int x2, int y1, int y2) {
        X_min = min(x1, x2);
        X_max = max(x1, x2);
        Y_min = min(y1, y2);
        Y_max = max(y1, y2);
    }

    // 교차 부분 확인
    bool isIntersect(int cx, int cy, int r) {
        int near_X = max(X_min, min(cx, X_max));
        int near_Y = max(Y_min, min(cy, Y_max));

        int dx = cx - near_X;
        int dy = cy - near_Y;

        return dx * dx + dy * dy <= r * r;
    }

    // 교차 부분 넓이
    double area() {
        return (X_max - X_min) * (Y_max - Y_min);
    }

    // 출력
    void print() {
        cout << "R " << X_min << " " << X_max << " " << Y_min << " " << Y_max << endl;
    }
};

// 원에 대한 class
class Circle {
public:
    int cx, cy, r;

    // 원의 중점 좌표 & 반지름
    Circle() {
        cx = 0, cy = 0, r = 0;
    }

    Circle(int x, int y, int rad) {
        cx = x;
        cy = y;
        r = rad;
    }

    // 교차 부분 확인
    bool isIntersect(int x, int y, int rad) {
        int dx = cx - x;
        int dy = cy - y;

        int dist2 = dx * dx + dy * dy;
        int rSum = r + rad;

        return dist2 <= rSum * rSum;
    }

    // 교차 부분 넓이
    double area() {
        return 3.14 * r * r;
    }

    // 출력
    void print() {
        cout << "C " << cx << " " << cy << " " << r << endl;
    }
};

// 도형 정보
class Shape_Info {
public:
    double Shape_Area;
    int type; // 0 : Rect, 1 : Circle

    // 각 도형별 클래스로 지정
    Rect rect;
    Circle circle;

    Shape_Info(Rect r) {
        rect = r;
        type = 0; // 0 : Rect
        circle = Circle(0, 0, 0); // 기본값으로 초기화 (이번 도형은 직사각형 -> 원 사용 X)
        Shape_Area = rect.area();
    }

    Shape_Info(Circle c) {
        circle = c;
        type = 1; // 1 : Circle
        rect = Rect(0, 0, 0, 0); // 기본값으로 초기화 (이번 도형은 원 -> 직사각형 사용 X)
        Shape_Area = circle.area();
    }


    bool isIntersect(int cx, int cy, int r) {
        if (type == 0)
            return rect.isIntersect(cx, cy, r);

        else
            return circle.isIntersect(cx, cy, r);
    }

    void print() {
        if (type == 0)
            rect.print();

        else circle.print();
    }
};

int main() {
    ifstream file("input1.txt");

    int N;
    file >> N; // 도형의 개수

    vector<Shape_Info> game; // 도형의 종류를 저장할 vector

    for (int i = 0; i < N; ++i) {
        // 도형의 종류 판별(R / C)
        char shape;
        file >> shape;

        // 직사각형
        if (shape == 'R') {
            int x1, x2, y1, y2;
            file >> x1 >> x2 >> y1 >> y2;

            game.push_back(Shape_Info(Rect(x1, x2, y1, y2)));
        }

        // 원
        else if (shape == 'C') {
            int x, y, r;
            file >> x >> y >> r;

            game.push_back(Shape_Info(Circle(x, y, r)));
        }
    }

    int tx, ty, tr;
    file >> tx >> ty >> tr;

    file.close();

    vector<Shape_Info> result;

    // 도형이 교차하는 부분이 있으면(insIntersect = true) result에 추가
    for (int i = 0; i < game.size(); i++) {
        if (game[i].isIntersect(tx, ty, tr)) {
            result.push_back(game[i]);
        }
    }

    // lambda 함수를 이용하여 result에 저장된 면적들을 크기순 정렬
    sort(result.begin(), result.end(), [](Shape_Info a, Shape_Info b) {
        return a.Shape_Area < b.Shape_Area;
        }
    );

    // 출력
    for (int i = 0; i < result.size(); i++) {
        result[i].print();
    }

    return 0;
}