#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
	int tmp, count = 0;
	int list[MAX] = { 0 };

	while (true) {
		cin >> tmp;
		count++;

		// �Է°��� -1�̸� ����
		if (tmp == -1)
			break;

		// ù��° �Է°� ���� ���
		else if (count == 1) {
			list[0] = tmp;
			cout << list[0] << endl;
			continue;
		}


		for (int i = 0; i < count; i++) {
			// �Է�	���� ���� �迭�� �ִ� ������ ũ�� continue
			if (tmp > list[i] && i != count - 1) {
				continue;
			}

			// �Է� ���� ���� �迭�� ���� �ߺ��̸� ����
			else if (tmp == list[i]) {
				cout << "duplicate" << endl;
				count--;
				break;
			}

			// �Է� ���� ������ ū ������ �迭���� �� ĭ�� �ڷ� �з��� ����
			for (int p = count - 1; p > i; p--) {
				list[p] = list[p - 1];
			}

			// �о ���ڸ��� �Է� ���� �� ����
			list[i] = tmp;

			// �迭 ���
			for (int q = 0; q < count; q++) {
				cout << list[q] << " ";
			}

			cout << endl;

			break;
		}

	}

	return 0;
}