#include <iostream>
using namespace std;

int main() {
	int N; // n��° ��
	double Answer = 1, tmp = -0.5; // -(1/2)�� �ŵ�������ŭ ��� ���� -> tmp

	cin >> N;

	for (int i = 1; i <= N; i++) {
		Answer += tmp;

		tmp *= -0.5; // -(1/2)�� N�� �ŵ������� �� -> tmp
	}

	cout << Answer << endl;

	return 0;
}