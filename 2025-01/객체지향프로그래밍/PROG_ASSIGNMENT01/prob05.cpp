#include <iostream>
using namespace std;

int main() {
	int Y1, M1, D1, Y2, M2, D2; // 날짜 입력 받기

	cin >> Y1 >> M1 >> D1 >> Y2 >> M2 >> D2;

	// 년 > 월 > 일 순서로 비교
	if (Y1 > Y2)
		cout << (int)1 << endl;
	else if (Y1 < Y2)
		cout << (int)-1 << endl;
	else {
		if (M1 > M2)
			cout << (int)1 << endl;
		else if (M1 < M2)
			cout << (int)-1 << endl;
		else {
			if (D1 > D2)
				cout << (int)1 << endl;
			else if (D1 < D2)
				cout << (int)-1 << endl;
			else
				cout << (int)0 << endl;
		}
	}

	return 0;
}