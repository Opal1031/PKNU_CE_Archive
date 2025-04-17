#include <iostream>
using namespace std;

int main() {
	int N = 7, len = 7;
	int Num_max = 0, Num_max_index = 0, tmp = 0, count = -1;
	int standard = 0, straight = 1, check = 0;
	int data[7] = { 0 };
	int sort_data[7] = { 0 };

	// 데이터 입력
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

		// 가장 큰 값을 배열의 마지막 값과 변경 후, N - 1 -> 마지막 수를 제외한 상태로 위의 탐색 반복
		tmp = data[N - 1];
		data[N - 1] = data[Num_max_index];
		data[Num_max_index] = tmp;

		N--;
	}

	// 중복 제거, [0]번 인덱스부터 값 저장하기 위해 count = -1로 시작
	for (int j = 0; j < 7; j++) {
		if (data[j] == data[j + 1])
			continue;
		else
			count++;
		sort_data[count] = data[j];
	}

	// count가 -1부터 시작이었기 때문에, <가 아닌 <=로 범위 지정
	for (int a = 0; a <= count; a++) {
		straight = 1;

		// 시작 ~ +4까지 스트레이트인지 확인, 도중에 스트레이트가 끊기면 다음 시작점
		for (int b = a + 1; b < a + 5; b++) {
			if (sort_data[b] == sort_data[a] + straight) {
				straight++;
			}

			else
				break;
		}

		// 스트레이트 성립 시 check++
		if (straight >= 5) {
			check++;
		}
	}

	// 스트레이트 여부에 따른 결과 출력
	if (check > 0)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	return 0;
}