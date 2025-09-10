#include <iostream>
using namespace std;

int main() {
	int N; // n번째 수
	int Fib = 0; // n번째 Fibonacci 수
	int Num_a = 1, Num_b = 1; // (n - 1), (n - 2)번째 수

	cin >> N;

	for (int i = 0; i <= N - 2; i++) { // N - 2번 반복 / n >= 2
		Fib = Num_a + Num_b; // 이전 2개의 합

		Num_b = Num_a; // 다음 Fib을 구하기 위한 변수값 변경
		Num_a = Fib;
	}

	cout << Fib << endl;

	return 0;
}