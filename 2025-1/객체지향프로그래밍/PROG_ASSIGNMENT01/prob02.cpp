#include <iostream>
using namespace std;

int main() {
	int N; // n번째 수
	double Answer = 1, tmp = -0.5; // -(1/2)의 거듭제곱만큼 계산 예정 -> tmp

	cin >> N;

	for (int i = 1; i <= N; i++) {
		Answer += tmp;

		tmp *= -0.5; // -(1/2)를 N번 거듭제곱한 값 -> tmp
	}

	cout << Answer << endl;

	return 0;
}