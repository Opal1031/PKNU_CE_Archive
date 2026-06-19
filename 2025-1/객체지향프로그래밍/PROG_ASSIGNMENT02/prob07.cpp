#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	string str; // 한 단어씩 확인
	vector<string> words; // sort된 단어들 저장 벡터

	while (true) {
		cin >> str;

		if (str.compare("exit") == 0)
			break;

		// 이미 목록에 등록된 문자열인지 검사
		bool found = false;

		for (int j = 0; j < words.size(); j++) {
			if (words[j] == str) {
				found = true;

				cout << "duplicate" << endl;
				break;
			}
		}

		// duplicate인 words 출력 없이 다음으로
		if (found)
			continue;

		// 목록에 없는 문자열만 목록에 추가
		if (!found)
			words.push_back(str);

		for (int p = 0; p < words.size() - 1; p++) {
			for (int q = 0; q < words.size() - 1 - p; q++) {
				if (words[q] > words[q + 1]) {
					// 단어가 사전순으로 뒤에 있으면 교환
					string tmp = words[q];
					words[q] = words[q + 1];
					words[q + 1] = tmp;
				}
			}
		}

		for (int k = 0; k < words.size(); k++)
			cout << words[k] << " ";

		cout << endl;
	}


	return 0;
}