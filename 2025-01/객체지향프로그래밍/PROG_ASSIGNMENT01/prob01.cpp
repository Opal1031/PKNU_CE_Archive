#include <iostream>
using namespace std;

int main() {
	int N; // n��° ��
	int Fib = 0; // n��° Fibonacci ��
	int Num_a = 1, Num_b = 1; // (n - 1), (n - 2)��° ��

	cin >> N;

	for (int i = 0; i <= N - 2; i++) { // N - 2�� �ݺ� / n >= 2
		Fib = Num_a + Num_b; // ���� 2���� ��

		Num_b = Num_a; // ���� Fib�� ���ϱ� ���� ������ ����
		Num_a = Fib;
	}

	cout << Fib << endl;

	return 0;
}