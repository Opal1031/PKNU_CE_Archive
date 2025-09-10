#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

// ��ǥ�� ��Ÿ���� Ŭ����
class Point {
public:
    double x, y;

    // �⺻ ������ : ��ǥ �ʱ�ȭ
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

// ������ ���� ����
class Geometry {
public:
    // �� �� ���� �Ÿ� ���
    static double distance(const Point& a, const Point& b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    // �־��� ���� ��� ���� �����ϴ��� Ȯ��
    static bool Circle_Contains_All(const vector<Point>& points, const Point& center, double radius) {
        for (const auto& p : points) {
            if (distance(p, center) > radius + 1e-9)
                return false;
        }

        return true;
    }

    // �� ���� ���� ��ȯ
    static Point Mid_Point(const Point& a, const Point& b) {
        return Point((a.x + b.x) / 2.0, (a.y + b.y) / 2.0);
    }

    // �� ������ ������ ���� & �߽�/������ ���
    static bool Make_Circumcircle(const Point& A, const Point& B, const Point& C, Point& center, double& radius) {
        double a1 = B.x - A.x;
        double b1 = B.y - A.y;
        double a2 = C.x - A.x;
        double b2 = C.y - A.y;

        // ������ ���� ���� ���� Ȯ��
        double d = 2 * (a1 * b2 - a2 * b1);

        if (abs(d) < 1e-9)
            return false;

        // �������� �߽� ��ǥ ���
        double c1 = a1 * (A.x + B.x) + b1 * (A.y + B.y);
        double c2 = a2 * (A.x + C.x) + b2 * (A.y + C.y);

        center.x = (b2 * c1 - b1 * c2) / d;
        center.y = (a1 * c2 - a2 * c1) / d;

        // �������� �߽ɿ��� �� �������� �Ÿ�
        radius = distance(center, A);

        return true;
    }
};

// �ּ� �������� ����ϴ� Ŭ����
class Circumscribed {
private:
    vector<Point> points; // ��� ���簢���� ������ ����

public:
    // ���Ͽ��� ���簢�� ��ǥ -> ������ ����
    void loadInput(const string& filename) {
        ifstream file(filename);

        // ���簢�� ����
        int n;
        file >> n;

        for (int i = 0; i < n; ++i) {
            int xmin, xmax, ymin, ymax;
            file >> xmin >> xmax >> ymin >> ymax;

            // �� ������ �߰�
            points.push_back(Point(xmin, ymin));
            points.push_back(Point(xmin, ymax));
            points.push_back(Point(xmax, ymin));
            points.push_back(Point(xmax, ymax));
        }

        file.close();
    }

    // �ּ� ������ ��� �� ���
    void solve() {
        // ���� �ָ� ������ �� �� ã��
        double max_Distance = -1;

        Point A, B;

        for (const auto& p1 : points) {
            for (const auto& p2 : points) {
                double d = Geometry::distance(p1, p2);
                if (d > max_Distance) {
                    max_Distance = d;
                    A = p1;
                    B = p2;
                }
            }
        }

        // ������ �߽�, �Ÿ� ������ ���������� ����
        Point center = Geometry::Mid_Point(A, B);
        double radius = max_Distance / 2.0;

        // �� ���� ��� �����ϸ� ����ϰ� ����
        if (Geometry::Circle_Contains_All(points, center, radius)) {
            printf("%.5f %.5f %.5f\n", center.x, center.y, radius);

            return;
        }

        // �� ���� ������ ã��
        double bestRadius = 1e9;
        Point bestCenter;

        for (const auto& C : points) {
            if ((C.x == A.x && C.y == A.y) || (C.x == B.x && C.y == B.y))
                continue;

            Point tempCenter;
            double tempRadius;

            if (Geometry::Make_Circumcircle(A, B, C, tempCenter, tempRadius)) {
                if (Geometry::Circle_Contains_All(points, tempCenter, tempRadius) && tempRadius < bestRadius) {
                    bestCenter = tempCenter;
                    bestRadius = tempRadius;
                }
            }
        }

        // ���� ��� ���
        printf("%.5f %.5f %.5f\n", bestCenter.x, bestCenter.y, bestRadius);
    }
};

int main() {
    Circumscribed solver;

    solver.loadInput("input2.txt");
    solver.solve();

    return 0;
}