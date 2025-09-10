#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// ���簢���� ���� class
class Rect {
public:
    int X_min, X_max, Y_min, Y_max;

    // ���簢���� 4 ������
    Rect() {
        X_min = 0, X_max = 0, Y_min = 0, Y_max = 0;
    }

    Rect(int x1, int x2, int y1, int y2) {
        X_min = min(x1, x2);
        X_max = max(x1, x2);
        Y_min = min(y1, y2);
        Y_max = max(y1, y2);
    }

    // ���� �κ� Ȯ��
    bool isIntersect(int cx, int cy, int r) {
        int near_X = max(X_min, min(cx, X_max));
        int near_Y = max(Y_min, min(cy, Y_max));

        int dx = cx - near_X;
        int dy = cy - near_Y;

        return dx * dx + dy * dy <= r * r;
    }

    // ���� �κ� ����
    double area() {
        return (X_max - X_min) * (Y_max - Y_min);
    }

    // ���
    void print() {
        cout << "R " << X_min << " " << X_max << " " << Y_min << " " << Y_max << endl;
    }
};

// ���� ���� class
class Circle {
public:
    int cx, cy, r;

    // ���� ���� ��ǥ & ������
    Circle() {
        cx = 0, cy = 0, r = 0;
    }

    Circle(int x, int y, int rad) {
        cx = x;
        cy = y;
        r = rad;
    }

    // ���� �κ� Ȯ��
    bool isIntersect(int x, int y, int rad) {
        int dx = cx - x;
        int dy = cy - y;

        int dist2 = dx * dx + dy * dy;
        int rSum = r + rad;

        return dist2 <= rSum * rSum;
    }

    // ���� �κ� ����
    double area() {
        return 3.14 * r * r;
    }

    // ���
    void print() {
        cout << "C " << cx << " " << cy << " " << r << endl;
    }
};

// ���� ����
class Shape_Info {
public:
    double Shape_Area;
    int type; // 0 : Rect, 1 : Circle

    // �� ������ Ŭ������ ����
    Rect rect;
    Circle circle;

    Shape_Info(Rect r) {
        rect = r;
        type = 0; // 0 : Rect
        circle = Circle(0, 0, 0); // �⺻������ �ʱ�ȭ (�̹� ������ ���簢�� -> �� ��� X)
        Shape_Area = rect.area();
    }

    Shape_Info(Circle c) {
        circle = c;
        type = 1; // 1 : Circle
        rect = Rect(0, 0, 0, 0); // �⺻������ �ʱ�ȭ (�̹� ������ �� -> ���簢�� ��� X)
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
    file >> N; // ������ ����

    vector<Shape_Info> game; // ������ ������ ������ vector

    for (int i = 0; i < N; ++i) {
        // ������ ���� �Ǻ�(R / C)
        char shape;
        file >> shape;

        // ���簢��
        if (shape == 'R') {
            int x1, x2, y1, y2;
            file >> x1 >> x2 >> y1 >> y2;

            game.push_back(Shape_Info(Rect(x1, x2, y1, y2)));
        }

        // ��
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

    // ������ �����ϴ� �κ��� ������(insIntersect = true) result�� �߰�
    for (int i = 0; i < game.size(); i++) {
        if (game[i].isIntersect(tx, ty, tr)) {
            result.push_back(game[i]);
        }
    }

    // lambda �Լ��� �̿��Ͽ� result�� ����� �������� ũ��� ����
    sort(result.begin(), result.end(), [](Shape_Info a, Shape_Info b) {
        return a.Shape_Area < b.Shape_Area;
        }
    );

    // ���
    for (int i = 0; i < result.size(); i++) {
        result[i].print();
    }

    return 0;
}