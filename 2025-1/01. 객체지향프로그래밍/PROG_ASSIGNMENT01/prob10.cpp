#include <iostream>
#include <cmath>
using namespace std;
const int MAX = 100;

int main() {
	int N, K;
	int list[MAX] = { 0 };

	cin >> N;

	// 입력받은 값을 배열에 저장
	for (int i = 0; i < N; i++) {
		cin >> list[i];
	}

	cin >> K;

	// 첫번째 값으로 절대값 비교 기준
	int num = list[0];
	int min_gap = abs(K - list[0]); // 절대값 함수

	// 배열에 숫자들의 절대값 구하기
	for (int j = 1; j < N; j++) {
		int gap = abs(K - list[j]);

		// 절대값이 작으면 기준값 변경
		if (gap < min_gap) {
			min_gap = gap;
			num = list[j];
		}
	}

	cout << num << endl;

	return 0;
}