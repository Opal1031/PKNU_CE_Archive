#include <iostream>
#include <cmath>
using namespace std;
const int MAX = 100;

int main(void) {
	int N;
	double Sum1 = 0, Sum2 = 0, AVG = 0, SD = 0; // AVG = ���, SD = ǥ������
	double list[MAX] = { 0 }; // ũ�Ⱑ 100�� ����Ʈ ���� �� ��� ���� 0���� �ʱ�ȭ

	cin >> N;

	// ����Ʈ�� �Է¹��� ������ ä���, Sum1 -> ��ü ��
	for (int i = 0; i < N; i++) {
		cin >> list[i];

		Sum1 += list[i];
	}

	// ��� = ��ü �� / ����
	AVG = Sum1 / N;

	// Sum2 -> ���Ŀ��� �ñ׸� �κп� �ش��ϴ� ��
	for (int j = 0; j < N; j++) {
		Sum2 += pow((list[j] - AVG), 2);
	}

	// ���� ���� �̿��Ͽ� SD �� ���ϱ�
	SD = sqrt(Sum2 / N);

	cout << AVG << " " << SD << endl;

	return 0;
}