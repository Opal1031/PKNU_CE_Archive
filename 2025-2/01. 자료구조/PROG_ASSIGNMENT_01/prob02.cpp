#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct Point2D {
	double x, y;
};

int main() {
	// ��ǥ ����, �迭 ����, �ִ� �Ÿ�, �ش� ��ǥ �ε���
	int N;
	int size = 4;
	double max_Distance = 0.0;
	int coord1 = 0, coord2 = 0;

	// ���� �б�
	ifstream file("input2.txt");
	file >> N;

	Point2D* points = new Point2D[size];

	// ��ǥ �Է� �� ���� �迭 ����
	for (int i = 0; i < N; ++i) {
		if (i == size) {
			size *= 2;

			Point2D* tmp = new Point2D[size];

			for (int j = 0; j < i; ++j) {
				(tmp + j)->x = (points + j)->x;
				(tmp + j)->y = (points + j)->y;
			}

			delete[] points;

			points = tmp;
		}

		file >> (points + i)->x >> (points + i)->y;
	}

	// �� ��ǥ ���� �ִ� �Ÿ� ���
	for (int p = 0; p < N; ++p) {
		for (int q = p + 1; q < N; ++q) {
			double dx = (points + p)->x - (points + q)->x;
			double dy = (points + p)->y - (points + q)->y;
			double distance = sqrt(dx * dx + dy * dy);

			if (distance > max_Distance) {
				max_Distance = distance;
				coord1 = p;
				coord2 = q;
			}
		}
	}

	// ��� ���
	cout << (points + coord1)->x << " " << (points + coord1)->y << endl;
	cout << (points + coord2)->x << " " << (points + coord2)->y << endl;
	cout << max_Distance << endl;

	// ���� �޸� ����
	delete[] points;

	return 0;
}