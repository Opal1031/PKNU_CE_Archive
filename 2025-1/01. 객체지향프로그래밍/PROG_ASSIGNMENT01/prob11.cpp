#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
	int N, tmp = 0, lead_count = 1;
	int lead_list[MAX] = { 0 }; // ������ �� ���ڵ��� �����ϴ� �迭

	cin >> N;

	// ù��° ������ ������ ����
	cin >> lead_list[0];

	// �ԷµǴ� ������ ���� ���� �Ǻ�
	for (int j = 1; j < N; j++) {
		cin >> tmp;

		// �ԷµǴ� ������ ���� ������ ���� ���ں��� ũ�� ���� �迭�� ����
		if (tmp >= lead_list[lead_count - 1]) {
			lead_list[lead_count] = tmp;
			lead_count++;
		}
	}

	cout << lead_count << ": ";

	for (int j = 0; j < lead_count; j++) {
		cout << lead_list[j] << " ";
	}

	return 0;
}