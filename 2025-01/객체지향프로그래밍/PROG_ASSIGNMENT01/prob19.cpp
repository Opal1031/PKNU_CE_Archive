#include <iostream>
using namespace std;

int main() {
	int N = 7, len = 7;
	int Num_max = 0, Num_max_index = 0, tmp = 0, count = -1;
	int standard = 0, straight = 1, check = 0;
	int data[7] = { 0 };
	int sort_data[7] = { 0 };

	// ������ �Է�
	for (int i = 0; i < N; i++) {
		cin >> data[i];
	}

	while (N > 0) {
		Num_max = data[0], Num_max_index = 0;

		for (int j = 1; j < N; j++) {

			if (data[j] > Num_max) {
				Num_max = data[j];
				Num_max_index = j;
			}
		}

		// ���� ū ���� �迭�� ������ ���� ���� ��, N - 1 -> ������ ���� ������ ���·� ���� Ž�� �ݺ�
		tmp = data[N - 1];
		data[N - 1] = data[Num_max_index];
		data[Num_max_index] = tmp;

		N--;
	}

	// �ߺ� ����, [0]�� �ε������� �� �����ϱ� ���� count = -1�� ����
	for (int j = 0; j < 7; j++) {
		if (data[j] == data[j + 1])
			continue;
		else
			count++;
		sort_data[count] = data[j];
	}

	// count�� -1���� �����̾��� ������, <�� �ƴ� <=�� ���� ����
	for (int a = 0; a <= count; a++) {
		straight = 1;

		// ���� ~ +4���� ��Ʈ����Ʈ���� Ȯ��, ���߿� ��Ʈ����Ʈ�� ����� ���� ������
		for (int b = a + 1; b < a + 5; b++) {
			if (sort_data[b] == sort_data[a] + straight) {
				straight++;
			}

			else
				break;
		}

		// ��Ʈ����Ʈ ���� �� check++
		if (straight >= 5) {
			check++;
		}
	}

	// ��Ʈ����Ʈ ���ο� ���� ��� ���
	if (check > 0)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	return 0;
}