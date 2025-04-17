#include <iostream>
#include <cmath>
using namespace std;
const int MAX = 100;

int main() {
	int N, K;
	int list[MAX] = { 0 };

	cin >> N;

	// �Է¹��� ���� �迭�� ����
	for (int i = 0; i < N; i++) {
		cin >> list[i];
	}

	cin >> K;

	// ù��° ������ ���밪 �� ����
	int num = list[0];
	int min_gap = abs(K - list[0]); // ���밪 �Լ�

	// �迭�� ���ڵ��� ���밪 ���ϱ�
	for (int j = 1; j < N; j++) {
		int gap = abs(K - list[j]);

		// ���밪�� ������ ���ذ� ����
		if (gap < min_gap) {
			min_gap = gap;
			num = list[j];
		}
	}

	cout << num << endl;

	return 0;
}