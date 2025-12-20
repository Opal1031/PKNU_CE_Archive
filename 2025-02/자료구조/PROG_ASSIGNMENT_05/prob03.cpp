#include <iostream>

using namespace std;

#define MAX 100

// 두 수의 합이 K가 되는 쌍의 개수를 재귀적으로 세는 함수
int countPairs(int data[], int start, int end, int K) {
	// 시작 인덱스가 끝 인덱스 이상이면 더 이상 쌍이 없음
	if (start >= end) {
		return 0;
	}

	int sum = data[start] + data[end];

	// 합이 K보다 크면 end를 왼쪽으로 이동
	if (sum > K) {
		return countPairs(data, start, end - 1, K);
	}

	// 합이 K보다 작으면 start를 오른쪽으로 이동
	else if (sum < K) {
		return countPairs(data, start + 1, end, K);
	}

	// 합이 K와 같으면 쌍을 하나 세고, 양쪽 포인터 이동
	else {
		return 1 + countPairs(data, start + 1, end - 1, K);
	}
}

int main() {
	// 데이터 배열, N: 데이터 개수, K: 목표 합
	int data[MAX];
	int N, K;

	// N 입력
	cin >> N;

	// 오름차순 정렬된 데이터 입력
	for (int i = 0; i < N; i++) {
		cin >> data[i];
	}

	// K 입력
	cin >> K;

	// 쌍의 개수 계산
	int result = countPairs(data, 0, N - 1, K);

	// 결과 출력
	cout << result << endl;

	return 0;
}