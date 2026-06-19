#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	ifstream infile("sample.txt");

	string str; // 한 단어씩 확인
	vector<string> words; // sort된 단어들 저장 벡터

	while (infile >> str) { // 파일의 끝에 도달하면 false를 반환하기 때문에 반복문 종료됨
		int s = 0, t = str.length() - 1; // 시작점 & 끝점

		// 문자열에서 앞에서부터 처음으로 등장하는 알파벳이나 숫자의 위치 s 찾기

		// 알파벳이나 숫자가 아니면 다음 인덱스
		while (s < str.length() && !isalnum(str[s]))
			s++;

		// 뒤에서부터 검사
		while (t >= 0 && !isalnum(str[t]))
			t--;

		if (s <= t) { // 남아있는 문자가 하나도 없다면
			// 해당 문자열 잘라내기
			string pure_word = str.substr(s, t - s + 1);

			// 모든 문자 소문자로 변환
			for (int i = 0; i < pure_word.length(); i++)
				pure_word[i] = tolower(pure_word[i]);

			// 이미 목록에 등록된 문자열인지 검사
			bool found = false;

			for (int j = 0; j < words.size(); j++) {
				if (words[j] == pure_word) {
					found = true;
					break;
				}
			}

			// 목록에 없는 문자열만 목록에 추가
			if (!found)
				words.push_back(pure_word);
		}
	}

	// 파일 닫기
	infile.close();

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
		cout << words[k] << endl;

	return 0;
}