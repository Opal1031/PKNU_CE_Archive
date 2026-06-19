#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

// 좌표를 나타내는 클래스
class Point {
public:
    double x, y;

    // 기본 생성자 : 좌표 초기화
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

// 기하학 연산 수행
class Geometry {
public:
    // 두 점 사이 거리 계산
    static double distance(const Point& a, const Point& b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    // 주어진 원이 모든 점을 포함하는지 확인
    static bool Circle_Contains_All(const vector<Point>& points, const Point& center, double radius) {
        for (const auto& p : points) {
            if (distance(p, center) > radius + 1e-9)
                return false;
        }

        return true;
    }

    // 두 점의 중점 반환
    static Point Mid_Point(const Point& a, const Point& b) {
        return Point((a.x + b.x) / 2.0, (a.y + b.y) / 2.0);
    }

    // 세 점으로 외접원 구성 & 중심/반지름 계산
    static bool Make_Circumcircle(const Point& A, const Point& B, const Point& C, Point& center, double& radius) {
        double a1 = B.x - A.x;
        double b1 = B.y - A.y;
        double a2 = C.x - A.x;
        double b2 = C.y - A.y;

        // 외접원 구성 가능 여부 확인
        double d = 2 * (a1 * b2 - a2 * b1);

        if (abs(d) < 1e-9)
            return false;

        // 외접원의 중심 좌표 계산
        double c1 = a1 * (A.x + B.x) + b1 * (A.y + B.y);
        double c2 = a2 * (A.x + C.x) + b2 * (A.y + C.y);

        center.x = (b2 * c1 - b1 * c2) / d;
        center.y = (a1 * c2 - a2 * c1) / d;

        // 반지름은 중심에서 한 점까지의 거리
        radius = distance(center, A);

        return true;
    }
};

// 최소 외접원을 계산하는 클래스
class Circumscribed {
private:
    vector<Point> points; // 모든 직사각형의 꼭짓점 저장

public:
    // 파일에서 직사각형 좌표 -> 꼭짓점 저장
    void loadInput(const string& filename) {
        ifstream file(filename);

        // 직사각형 개수
        int n;
        file >> n;

        for (int i = 0; i < n; ++i) {
            int xmin, xmax, ymin, ymax;
            file >> xmin >> xmax >> ymin >> ymax;

            // 네 꼭짓점 추가
            points.push_back(Point(xmin, ymin));
            points.push_back(Point(xmin, ymax));
            points.push_back(Point(xmax, ymin));
            points.push_back(Point(xmax, ymax));
        }

        file.close();
    }

    // 최소 외접원 계산 및 출력
    void solve() {
        // 가장 멀리 떨어진 두 점 찾기
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

        // 중점을 중심, 거리 절반을 반지름으로 설정
        Point center = Geometry::Mid_Point(A, B);
        double radius = max_Distance / 2.0;

        // 세 점을 모두 포함하면 출력하고 종료
        if (Geometry::Circle_Contains_All(points, center, radius)) {
            printf("%.5f %.5f %.5f\n", center.x, center.y, radius);

            return;
        }

        // 더 작은 외접원 찾기
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

        // 최종 결과 출력
        printf("%.5f %.5f %.5f\n", bestCenter.x, bestCenter.y, bestRadius);
    }
};

int main() {
    Circumscribed solver;

    solver.loadInput("input2.txt");
    solver.solve();

    return 0;
}