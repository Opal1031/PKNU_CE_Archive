#include <iostream>
#include <string>
#include <vector>
using namespace std;

void sorted_merge(vector<string>& first, vector<string>& second) {
	// second ������ ��� ��Ҹ� first ���Ϳ� �߰�
	for (int i = 0; i < second.size(); i++)
		first.push_back(second.at(i));

	// first ���͸� ����
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

	// m���� �����ڿ��� ������ ������ ���ĵǾ� �Էµȴ�.
	for (int i = 0; i < m; i++) {
		cin >> str;
		first.push_back(str);
	}

	cin >> n;

	// n���� �����ڿ��� ������ ������ ���ĵǾ� �Էµȴ�.
	for (int i = 0; i < n; i++) {
		cin >> str;
		second.push_back(str);
	}

	sorted_merge(first, second);

	// m + n���� ���ڿ��� ������ ������ ���ĵǾ� ��µǾ�� �Ѵ�.
	for (auto item : first)
		cout << item << " ";

	cout << endl;

	return 0;
}