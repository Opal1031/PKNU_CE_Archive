#include <iostream>
using namespace std;

int main() {
	int N, tmp; // n번째 수, 입력값
	int check = 0; // 모든 입력값이 음수일 경우 확인용
	int min = 2147483647; // int형에서 표현할 수 있는 최대 정수, 최초 입력값과 대소 비교를 위해 지정

	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> tmp;

		if (tmp < 0)
			continue; // 입력값이 음수이면 진행, check = 0
		else {
			check = 1; // 입력값이 양수이면 check = 1, 추후 출력 시 확인

			// 입력값이 기존의 min보다 작으면 값 변경, 만약 첫 입력값이 2147483647이어도 그 자체가 최소값이기 때문에 유지
			if (tmp < min)
				min = tmp;
		}
	}

	if (check == 0)
		cout << (int)-1 << endl; // 입력값이 모두 음수였으면 -1 출력
	else
		cout << min << endl;

	return 0;
}