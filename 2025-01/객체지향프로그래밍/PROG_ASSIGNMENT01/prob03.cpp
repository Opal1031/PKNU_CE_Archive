#include <iostream>
using namespace std;

int main() {
	int N, tmp; // n��° ��, �Է°�
	int check = 0; // ��� �Է°��� ������ ��� Ȯ�ο�
	int min = 2147483647; // int������ ǥ���� �� �ִ� �ִ� ����, ���� �Է°��� ��� �񱳸� ���� ����

	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> tmp;

		if (tmp < 0)
			continue; // �Է°��� �����̸� ����, check = 0
		else {
			check = 1; // �Է°��� ����̸� check = 1, ���� ��� �� Ȯ��

			// �Է°��� ������ min���� ������ �� ����, ���� ù �Է°��� 2147483647�̾ �� ��ü�� �ּҰ��̱� ������ ����
			if (tmp < min)
				min = tmp;
		}
	}

	if (check == 0)
		cout << (int)-1 << endl; // �Է°��� ��� ���������� -1 ���
	else
		cout << min << endl;

	return 0;
}