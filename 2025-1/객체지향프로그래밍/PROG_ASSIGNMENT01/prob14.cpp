#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
	int N = 0, real_N = 0, tmp = 0, Num_max = 0, Num_max_index = 0, count = 0;
	int data[MAX] = { 0 };
	int print_data[MAX] = { 0 };

	// 입력받을 개수 설정
	cin >> N;
	real_N = N;

	// 데이터 입력
	for (int i = 0; i < N; i++) {
		cin >> data[i];
	}

	// 전체에서 가장 큰 데이터 값 검색
	while (N > 0) {
		Num_max = data[0], Num_max_index = 0;

		for (int p = 1; p < N; p++) {

			if (data[p] > Num_max) {
				Num_max = data[p];
				Num_max_index = p;
			}
		}

		// 가장 큰 값을 배열의 마지막 값과 변경 후, N - 1 -> 마지막 수를 제외한 상태로 위의 탐색 반복
		tmp = data[N - 1];
		data[N - 1] = data[Num_max_index];
		data[Num_max_index] = tmp;

		N--;
	}

	// 중복 제거
	for (int j = 0; j < real_N; j++) {
		if (data[j] == data[j + 1])
			continue;
		else
			count++;
		print_data[count] = data[j];
	}

	// 출력
	cout << count << ": ";

	for (int k = 1; k <= count; k++) {
		cout << print_data[k] << " ";
	}

	cout << endl;

	return 0;
}