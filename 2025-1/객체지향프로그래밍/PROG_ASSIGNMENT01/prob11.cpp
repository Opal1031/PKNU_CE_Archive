#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
	int N, tmp = 0, lead_count = 1;
	int lead_list[MAX] = { 0 }; // 리더가 된 숫자들을 저장하는 배열

	cin >> N;

	// 첫번째 정수는 무조건 리더
	cin >> lead_list[0];

	// 입력되는 정수의 리더 여부 판별
	for (int j = 1; j < N; j++) {
		cin >> tmp;

		// 입력되는 정수가 현재 마지막 리더 숫자보다 크면 리더 배열에 저장
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