#include <iostream>
using namespace std;

int main() {
	int N, tmp; // n��° ��, �Է°�
	int MAX, MIN, gap; // �ִ밪, �ּҰ�, ����

	cin >> N;
	cin >> tmp;

	MAX = tmp, MIN = tmp; // ù �Է°��� �ִ밪���� �ּҰ�

	cout << (int)0 << " "; // ù ���̴� ������ 0

	for (int i = 2; i <= N; i++) { // ù��° �Է°� ���� ��������Ƿ� i = 2���� ����

		cin >> tmp;

		// MAX, MIN���� �Է°��� �񱳿� ���� ��ȯ
		if (tmp >= MAX)
			MAX = tmp;
		else if (tmp <= MIN)
			MIN = tmp;

		gap = MAX - MIN; // gap ���

		cout << gap << " "; // gap ���
	}

	return 0;
}