#include <iostream>
using namespace std;

int main() {
	int N, tmp; // n번째 수, 입력값
	int MAX, MIN, gap; // 최대값, 최소값, 차이

	cin >> N;
	cin >> tmp;

	MAX = tmp, MIN = tmp; // 첫 입력값은 최대값이자 최소값

	cout << (int)0 << " "; // 첫 차이는 무조건 0

	for (int i = 2; i <= N; i++) { // 첫번째 입력값 따로 출력했으므로 i = 2부터 시작

		cin >> tmp;

		// MAX, MIN값과 입력값의 비교에 따른 변환
		if (tmp >= MAX)
			MAX = tmp;
		else if (tmp <= MIN)
			MIN = tmp;

		gap = MAX - MIN; // gap 계산

		cout << gap << " "; // gap 출력
	}

	return 0;
}