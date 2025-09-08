#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct Point2D {
	double x, y;
};

int main() {
	// 좌표 개수, 배열 길이, 최대 거리, 해당 좌표 인덱스
	int N;
	int size = 4;
	double max_Distance = 0.0;
	int coord1 = 0, coord2 = 0;

	// 파일 읽기
	ifstream file("input2.txt");
	file >> N;

	Point2D* points = new Point2D[size];

	// 좌표 입력 및 동적 배열 저장
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

	// 두 좌표 간의 최대 거리 계산
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

	// 결과 출력
	cout << (points + coord1)->x << " " << (points + coord1)->y << endl;
	cout << (points + coord2)->x << " " << (points + coord2)->y << endl;
	cout << max_Distance << endl;

	// 동적 메모리 해제
	delete[] points;

	return 0;
}