#include <iostream>
#include <cmath>
using namespace std;
const int MAX = 100;

// ������ �ڸ����� ���ϴ� �Լ�
int length(int num) {
	int length = 0;

	if (num == 0)
		return 1;

	while (num > 0) {
		num /= 10;
		length++;
	}

	return length;
}

// �� ���� ������ �迭 ��
int compare(int a, int b) {
	int len_a = length(a);
	int len_b = length(b);

	// ���̸� ���� ���� �� ��
	long long fake_a = a * pow(10, len_b);
	long long fake_b = b * pow(10, len_a);

	if (fake_a < fake_b)
		return -1;
	else if (fake_a > fake_b)
		return 1;
	else
		return 0;
}

int main() {
	int N;
	int arr[MAX] = { 0 };

	cin >> N;

	for (int i = 0; i < N; i++)
		cin >> arr[i];

	// ���� ����
	for (int j = 1; j < N; j++) {
		int tmp = arr[j];
		int idx = j - 1;

		// ������ ���� �������� ���� ��ġ ã��
		while (idx >= 0 && compare(tmp, arr[idx]) < 1) {
			arr[idx + 1] = arr[idx];
			idx--;
		}

		// �ش� ��ġ�� ����
		arr[idx + 1] = tmp;
	}

	for (int n = 0; n < N; n++)
		cout << arr[n] << " ";

	return 0;
}