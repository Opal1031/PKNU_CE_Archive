#include <iostream>
using namespace std;

int main() {
	int Y1, M1, D1, Y2, M2, D2; // ��¥ �Է� �ޱ�

	cin >> Y1 >> M1 >> D1 >> Y2 >> M2 >> D2;

	// �� > �� > �� ������ ��
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