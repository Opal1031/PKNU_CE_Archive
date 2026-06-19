#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
	vector<int> v;

	// 정수 개수
	int n;
	cin >> n;

	// 배열 크기, 최대 검색 범위
	int size = n - 1;
	int limit = sqrt(n);

	for (int i = 2; i <= n; i++) {
		v.push_back(i);
	}

	// 에라토스테네스의 체
	// n의 제곱근까지만 확인 -> 불필요한 반복 제거
	for (int p = 0; (p < size) && (v.at(p) <= limit); p++) {
		int div = v.at(p);

		for (int q = p + 1; q < size;) {
			// 소수가 아닌 수 제거
			if (v.at(q) % div == 0) {
				// 이터레이터가 가리키는 위치의 원소 제거 & 벡터 크기 감소
				v.erase(v.begin() + q);
				size--;
			}

			// 소수의 배수가 아닌 수는 다음 수로 이동
			else {
				q++;
			}
		}
	}

	// 결과 출력
	for (int prime : v) {
		cout << prime << " ";
	}

	return 0;
}