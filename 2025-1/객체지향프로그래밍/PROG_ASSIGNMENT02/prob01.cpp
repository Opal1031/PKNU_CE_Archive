#include <iostream>
#include <cmath>
using namespace std;
const int MAX = 100;

// 숫자의 자리수를 구하는 함수
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

// 두 수의 사전식 배열 비교
int compare(int a, int b) {
	int len_a = length(a);
	int len_b = length(b);

	// 길이를 같게 만든 후 비교
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

	// 삽입 정렬
	for (int j = 1; j < N; j++) {
		int tmp = arr[j];
		int idx = j - 1;

		// 사전순 정렬 기준으로 삽입 위치 찾기
		while (idx >= 0 && compare(tmp, arr[idx]) < 1) {
			arr[idx + 1] = arr[idx];
			idx--;
		}

		// 해당 위치에 삽입
		arr[idx + 1] = tmp;
	}

	for (int n = 0; n < N; n++)
		cout << arr[n] << " ";

	return 0;
}