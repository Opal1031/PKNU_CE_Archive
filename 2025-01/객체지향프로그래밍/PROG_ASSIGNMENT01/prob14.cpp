#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
	int N = 0, real_N = 0, tmp = 0, Num_max = 0, Num_max_index = 0, count = 0;
	int data[MAX] = { 0 };
	int print_data[MAX] = { 0 };

	// �Է¹��� ���� ����
	cin >> N;
	real_N = N;

	// ������ �Է�
	for (int i = 0; i < N; i++) {
		cin >> data[i];
	}

	// ��ü���� ���� ū ������ �� �˻�
	while (N > 0) {
		Num_max = data[0], Num_max_index = 0;

		for (int p = 1; p < N; p++) {

			if (data[p] > Num_max) {
				Num_max = data[p];
				Num_max_index = p;
			}
		}

		// ���� ū ���� �迭�� ������ ���� ���� ��, N - 1 -> ������ ���� ������ ���·� ���� Ž�� �ݺ�
		tmp = data[N - 1];
		data[N - 1] = data[Num_max_index];
		data[Num_max_index] = tmp;

		N--;
	}

	// �ߺ� ����
	for (int j = 0; j < real_N; j++) {
		if (data[j] == data[j + 1])
			continue;
		else
			count++;
		print_data[count] = data[j];
	}

	// ���
	cout << count << ": ";

	for (int k = 1; k <= count; k++) {
		cout << print_data[k] << " ";
	}

	cout << endl;

	return 0;
}