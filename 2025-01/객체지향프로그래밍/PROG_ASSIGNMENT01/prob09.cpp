#include <iostream>
#include <cmath>
using namespace std;
const int MAX = 100;

int main(void) {
	int N;
	double Sum1 = 0, Sum2 = 0, AVG = 0, SD = 0; // AVG = 평균, SD = 표준편차
	double list[MAX] = { 0 }; // 크기가 100인 리스트 생성 후 모든 값을 0으로 초기화

	cin >> N;

	// 리스트를 입력받은 값으로 채우고, Sum1 -> 전체 합
	for (int i = 0; i < N; i++) {
		cin >> list[i];

		Sum1 += list[i];
	}

	// 평균 = 전체 합 / 개수
	AVG = Sum1 / N;

	// Sum2 -> 공식에서 시그마 부분에 해당하는 값
	for (int j = 0; j < N; j++) {
		Sum2 += pow((list[j] - AVG), 2);
	}

	// 위의 값을 이용하여 SD 값 구하기
	SD = sqrt(Sum2 / N);

	cout << AVG << " " << SD << endl;

	return 0;
}