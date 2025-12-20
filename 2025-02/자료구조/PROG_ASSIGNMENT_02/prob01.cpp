#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<string> v;
	string s;

	while (true) {
		// 문자열 입력
		cin >> s;

		// 프로그램 종료
		if (s == "exit") {
			break;
		}

		// 벡터에 없으면 추가
		if (find(v.begin(), v.end(), s) == v.end()) {
			v.push_back(s);
		}

		// 벡터에 있으면 제거
		else {
			// remove : 제거할 원소를 벡터의 끝으로 이동시키고, 새로운 끝 위치를 반환
			// erase : remove가 이동시킨 원소들을 벡터에서 실제로 제거
			v.erase(remove(v.begin(), v.end(), s), v.end());
		}

		// 사전 순으로 정렬
		sort(v.begin(), v.end());

		// 결과 출력
		for (string& str : v) {
			cout << str << " ";
		}

		cout << endl;
	}

	return 0;
}