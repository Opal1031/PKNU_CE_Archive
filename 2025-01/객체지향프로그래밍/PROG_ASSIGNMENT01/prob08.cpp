#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	int success1 = 0, success2 = 0; // 성공횟수 카운트
	int T = 1000000; // 1,000,000회 반복

	srand((unsigned int)time(NULL));

	for (int t = 1; t <= T; t++) {
		int count1 = 0, count2 = 0; // 매번 실험 때 마다 1이 몇 번 나왔는지 카운트

		// 6번 던져서 적어도 1번 1이 나오는 사건
		for (int i = 1; i <= 6; i++) {
			if (rand() % 6 == 1)
				count1++;
		}

		if (count1 >= 1)
			success1++;

		// 12번 던져서 적어도 1이 2번 나오는 사건
		for (int j = 1; j <= 12; j++) {
			if (rand() % 6 == 1)
				count2++;
		}

		if (count2 >= 2)
			success2++;
	}

	cout << 100 * success1 / (double)T << "%" << endl;
	cout << 100 * success2 / (double)T << "%" << endl;

	return 0;
}