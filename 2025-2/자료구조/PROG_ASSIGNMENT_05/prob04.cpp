#include <iostream>
#include <algorithm>

using namespace std;

#define MAX 1000

// K보다 작거나 같은 가장 큰 정수를 찾는 함수 (없으면 -1 반환)
int floor(int data[], int start, int end, int K) {
	// 시작 인덱스가 끝 인덱스보다 크면 값 없음
	if (start > end) {
		return -1;
	}

	int mid = (start + end) / 2;

	// K와 같은 값 발견 시 반환
	if (data[mid] == K) {
		return data[mid];
	}

	// 중간값이 K보다 크면 왼쪽 탐색
	else if (data[mid] > K) {
		return floor(data, start, mid - 1, K);
	}

	// 중간값이 K보다 작으면 오른쪽 탐색
	else {
		int rightFloor = floor(data, mid + 1, end, K);
		if (rightFloor == -1) {
			return data[mid];
		}

		else {
			return rightFloor;
		}
	}
}

// K보다 크거나 같은 가장 작은 정수를 찾는 함수 (없으면 -1 반환)
int ceiling(int data[], int start, int end, int K) {
	// 시작 인덱스가 끝 인덱스보다 크면 값 없음
	if (start > end) {
		return -1;
	}

	int mid = (start + end) / 2;

	// K와 같은 값 발견 시 반환
	if (data[mid] == K) {
		return data[mid];
	}

	// 중간값이 K보다 작으면 오른쪽 탐색
	else if (data[mid] < K) {
		return ceiling(data, mid + 1, end, K);
	}

	// 중간값이 K보다 크면 왼쪽 탐색
	else {
		int leftCeil = ceiling(data, start, mid - 1, K);
		if (leftCeil == -1) {
			return data[mid];
		}

		else {
			return leftCeil;
		}
	}
}

int main() {
	int data[MAX]; // 입력 데이터 배열
	int N, K;      // N: 데이터 개수, K: 기준값

	// N 입력
	cin >> N;

	// 정렬된 데이터 입력
	for (int i = 0; i < N; i++) {
		cin >> data[i];
	}

	// K 입력
	cin >> K;

	// floor 함수 호출 및 결과 출력
	int resultFloor = floor(data, 0, N - 1, K);

	if (resultFloor == -1) {
		cout << "-1" << endl;
	}

	else {
		cout << resultFloor << endl;
	}

	// ceiling 함수 호출 및 결과 출력
	int resultCeil = ceiling(data, 0, N - 1, K);
	if (resultCeil == -1) {
		cout << "-1" << endl;
	}

	else {
		cout << resultCeil << endl;
	}

	return 0;
}