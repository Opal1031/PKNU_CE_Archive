#include <iostream>
using namespace std;
const int MAX = 100;

int main() {
	int tmp, count = 0;
	int list[MAX] = { 0 };

	while (true) {
		cin >> tmp;
		count++;

		// 입력값이 -1이면 종료
		if (tmp == -1)
			break;

		// 첫번째 입력값 따로 출력
		else if (count == 1) {
			list[0] = tmp;
			cout << list[0] << endl;
			continue;
		}


		for (int i = 0; i < count; i++) {
			// 입력	받은 값이 배열에 있는 수보다 크면 continue
			if (tmp > list[i] && i != count - 1) {
				continue;
			}

			// 입력 받은 값이 배열의 수와 중복이면 종료
			else if (tmp == list[i]) {
				cout << "duplicate" << endl;
				count--;
				break;
			}

			// 입력 받은 값보다 큰 수들을 배열에서 한 칸씩 뒤로 밀려서 저장
			for (int p = count - 1; p > i; p--) {
				list[p] = list[p - 1];
			}

			// 밀어낸 빈자리에 입력 받은 값 저장
			list[i] = tmp;

			// 배열 출력
			for (int q = 0; q < count; q++) {
				cout << list[q] << " ";
			}

			cout << endl;

			break;
		}

	}

	return 0;
}