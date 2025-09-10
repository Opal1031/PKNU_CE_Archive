#include <iostream>
#include <string>
#include <vector>
using namespace std;

void sorted_merge(vector<string>& first, vector<string>& second) {
	// second 벡터의 모든 요소를 first 벡터에 추가
	for (int i = 0; i < second.size(); i++)
		first.push_back(second.at(i));

	// first 벡터를 정렬
	for (int p = 0; p < first.size() - 1; p++) {
		for (int q = 0; q < first.size() - 1 - p; q++) {
			if (first[q] > first[q + 1]) {
				swap(first[q], first[q + 1]);
			}
		}
	}
}

int main() {
	int m, n;
	string str;
	vector<string> first, second;

	cin >> m;

	// m개의 영문자열이 사전식 순서로 정렬되어 입력된다.
	for (int i = 0; i < m; i++) {
		cin >> str;
		first.push_back(str);
	}

	cin >> n;

	// n개의 영문자열이 사전식 순서로 정렬되어 입력된다.
	for (int i = 0; i < n; i++) {
		cin >> str;
		second.push_back(str);
	}

	sorted_merge(first, second);

	// m + n개의 문자열이 사전식 순서로 정렬되어 출력되어야 한다.
	for (auto item : first)
		cout << item << " ";

	cout << endl;

	return 0;
}