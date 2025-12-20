#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// 단어 설명에 등장하는 단어들 중 검색할 조건 확인
bool Deduplication(vector<string>& vec, string& token, string& base_word) {
	if (token.length() < 3)
		return false;

	if (token == base_word)
		return false;

	return find(vec.begin(), vec.end(), token) == vec.end();
}

int main() {
	// 단어와 설명을 저장할 2차원 벡터
	vector<vector<string>> dictionary;

	ifstream file("shuffled_dict.txt");
	string line;

	// 파일에서 단어와 설명을 읽어와서 dictionary에 저장
	while (getline(file, line)) {
		string word, explanation;
		stringstream ss_dict(line);

		getline(ss_dict, word, '\t');
		getline(ss_dict, explanation);
		dictionary.push_back({ word, explanation });
	}

	// 검색할 단어 입력
	string find_word;
	cin >> find_word;

	// 단어 설명에 등장하는 단어들 저장 벡터
	vector<string> explain_find;

	// 입력한 단어와 일치하는 단어 찾기
	for (auto& find_in_dict : dictionary) {
		if (find_in_dict[0] == find_word) {
			// 검색한 단어와 설명 출력
			cout << find_in_dict[0] << ": " << find_in_dict[1] << endl;

			stringstream ss_explain(find_in_dict[1]);
			string token;

			// 설명에서 단어 추출
			while (getline(ss_explain, token, ' ')) {
				if (Deduplication(explain_find, token, find_in_dict[0])) {
					explain_find.push_back(token);
				}
			}
		}
	}

	// 설명에 등장하는 단어들로 다시 단어 찾기 및 출력
	for (auto& explain_find : explain_find) {
		for (auto& find_in_dict : dictionary) {
			if (find_in_dict[0] == explain_find) {
				cout << find_in_dict[0] << ": " << find_in_dict[1] << endl;
			}
		}
	}

	return 0;
}