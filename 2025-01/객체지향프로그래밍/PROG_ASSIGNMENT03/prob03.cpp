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

        // ������ ���� Ȯ��(�� ��ǥ�� X���� ������) -> �������� �ƴ϶�� ������ ����
        isVertical = (x1 == x2);

        // �������� ��� �� ū y��ǥ���� ���� �ԷµǾ����� swap
        if (isVertical && y1 > y2)
            swap(y1, y2);
        // ������ ��� �� ū x��ǥ���� ���� �ԷµǾ����� swap
        if (!isVertical && x1 > x2)
            swap(x1, x2);
    }
};

bool intersect(Segment& a, Segment& b, int& x, int& y) {
    // �� ������ ���� �����̸� �������� ����
    if (a.isVertical == b.isVertical)
        return false;

    // �ϳ��� ����, �ϳ��� �������� �и�
    Segment& vert = a.isVertical ? a : b;
    Segment& hori = a.isVertical ? b : a;

    // ������ �� �ִ� ��ǥ�� �������� x, ������ y
    x = vert.x1;
    y = hori.y1;

    // ���� �����ϴ��� Ȯ�� (vert & hori ���� ������ ���� ���� �����ϴ��� Ȯ��)
    if (x >= hori.x1 && x <= hori.x2 && y >= vert.y1 && y <= vert.y2)
        return true;

    return false;
}

int main() {
    // �Է��� ���� ����
    int N;
    cin >> N;

    // �Է� ���� ��ǥ���� Segment ����
    vector<Segment> segments;
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        segments.push_back(Segment(x1, y1, x2, y2));
    }

    // ������ ���� ����
    vector<vector<int>> cross;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int x, y;

            // intersect�� �ش簪���� ���� return���� True�̸� cross ���Ϳ� ����
            if (intersect(segments[i], segments[j], x, y))
                cross.push_back({ x, y });
        }
    }

    // ����
    sort(cross.begin(), cross.end());

    // �ߺ� ����
    cross.erase(unique(cross.begin(), cross.end()), cross.end());

    // ���
    for (int i = 0; i < cross.size(); i++)
        cout << "[" << cross[i][0] << ", " << cross[i][1] << "]\n";

    return 0;
}