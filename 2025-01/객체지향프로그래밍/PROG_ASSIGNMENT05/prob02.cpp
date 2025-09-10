#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Shape {
public:
    virtual ~Shape() {}
    virtual double area() = 0;
    virtual bool isIntersect(int cx, int cy, int r) = 0;
    virtual void print() = 0;
};

class Rect : public Shape {
public:
    int X_min, X_max, Y_min, Y_max;

    Rect(int x1, int x2, int y1, int y2) {
        X_min = min(x1, x2);
        X_max = max(x1, x2);
        Y_min = min(y1, y2);
        Y_max = max(y1, y2);
    }

    double area() override {
        return (X_max - X_min) * (Y_max - Y_min);
    }

    bool isIntersect(int cx, int cy, int r) override {
        int near_X = max(X_min, min(cx, X_max));
        int near_Y = max(Y_min, min(cy, Y_max));
        int dx = cx - near_X;
        int dy = cy - near_Y;
        return dx * dx + dy * dy <= r * r;
    }

    void print() override {
        cout << "R " << X_min << " " << X_max << " " << Y_min << " " << Y_max << endl;
    }
};

class Circle : public Shape {
public:
    int cx, cy, r;

    Circle(int x, int y, int rad) : cx(x), cy(y), r(rad) {}

    double area() override {
        return 3.14 * r * r;
    }

    bool isIntersect(int x, int y, int rad) override {
        int dx = cx - x;
        int dy = cy - y;
        int dist2 = dx * dx + dy * dy;
        int rSum = r + rad;
        return dist2 <= rSum * rSum;
    }

    void print() override {
        cout << "C " << cx << " " << cy << " " << r << endl;
    }
};

int main() {
    ifstream file("input1.txt");
    int N;
    file >> N;

    vector<Shape*> shapes;

    for (int i = 0; i < N; ++i) {
        char shape_type;
        file >> shape_type;

        if (shape_type == 'R') {
            int x1, x2, y1, y2;
            file >> x1 >> x2 >> y1 >> y2;
            shapes.push_back(new Rect(x1, x2, y1, y2));
        }
        else if (shape_type == 'C') {
            int x, y, r;
            file >> x >> y >> r;
            shapes.push_back(new Circle(x, y, r));
        }
    }

    int tx, ty, tr;
    file >> tx >> ty >> tr;
    file.close();

    vector<Shape*> result;

    for (Shape* s : shapes) {
        if (s->isIntersect(tx, ty, tr)) {
            result.push_back(s);
        }
    }

    sort(result.begin(), result.end(), [](Shape* a, Shape* b) {
        return a->area() < b->area();
        });

    for (Shape* s : result) {
        s->print();
    }

    for (Shape* s : shapes) {
        delete s;
    }

    return 0;
}
