#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	int success1 = 0, success2 = 0; // ����Ƚ�� ī��Ʈ
	int T = 1000000; // 1,000,000ȸ �ݺ�

	srand((unsigned int)time(NULL));

	for (int t = 1; t <= T; t++) {
		int count1 = 0, count2 = 0; // �Ź� ���� �� ���� 1�� �� �� ���Դ��� ī��Ʈ

		// 6�� ������ ��� 1�� 1�� ������ ���
		for (int i = 1; i <= 6; i++) {
			if (rand() % 6 == 1)
				count1++;
		}

		if (count1 >= 1)
			success1++;

		// 12�� ������ ��� 1�� 2�� ������ ���
		for (int j = 1; j <= 12; j++) {
			if (rand() % 6 == 1)
				count2++;
		}

		if (count2 >= 2)
			success2++;
	}

	cout << 100 * success1 / (double)T << "%" << endl;
	cout << 100 * success2 / (double)T << "%" << endl;

	return 0;
}