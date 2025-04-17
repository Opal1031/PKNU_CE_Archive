// 입력으로 하나의 텍스트 파일을 읽는다.
// 파일에 등장하는 모든 단어들의 목록을 만들고, 각 단어가 텍스트 파일에 등장하는 라인 번호를 수집한다.
// 사용자가 요청하면 인덱스(단어와 라인번호)를 하나의 파일로 저장한다.
// 사용자가 단어를 검색하면 그 단어가 텍스트 파일에 몇 번 등장하는지, 그리고 몇 번째 줄에 등장하는지 출력한다.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

vector<string> words;
vector<vector<int>> lineNums;
vector<string> allLines;

string normalize(string word);
void sortIndex();
void makeIndex(string fileName);
void handle_find(string keyword);
void addWord(string word, int lineNum);
int findWord(string keyword);
vector<string> split_line(string line, char delimiter = ' ');

void makeIndex(string fileName) {
	ifstream theFile(fileName);

	words.clear();
	lineNums.clear();
	allLines.clear();

	string line;
	int lineNum = 0;

	// 각 단어가 등장하는 라인 번호를 알아야 하므로 한 번에 한 라인씩 입력받기
	while (getline(theFile, line)) {
		// 전체 라인 저장
		allLines.push_back(line);
		vector<string> tokens = split_line(line);

		// split된 각각의 단어들을 목록에 추가
		for (auto token : tokens) {
			addWord(token, lineNum);
		}
		lineNum++;
	}
	theFile.close();

	// 정렬은 인덱싱 끝나고 한 번만
	sortIndex();
}


vector<string> split_line(string line, char delimiter) {
	vector<string> tokens;

	// 문자열 line을 저장하는 stringstream을 생성
	stringstream sstream(line);

	string str;

	while (getline(sstream, str, delimiter))
		tokens.push_back(str);

	return tokens;
}

void addWord(string word, int lineNum) {
	string norm = normalize(word);

	// 길이가 3 미만인 단어 제외
	if (norm.length() < 3)
		return;

	int index = findWord(norm);
	if (index != -1) {
		// 같은 라인 중복 방지
		for (int n : lineNums[index])
			if (n == lineNum) return;
		lineNums[index].push_back(lineNum);
	}

	else {
		words.push_back(norm);
		vector<int> tmp = { lineNum };
		lineNums.push_back(tmp);
	}
}

int findWord(string word) {
	for (int i = 0; i < words.size(); i++)
		if (words[i] == word)
			return i;

	return -1;
}

void handle_find(string keyword) {
	string norm = normalize(keyword);
	if (norm.length() < 3) {
		cout << "검색어는 3자 이상이어야 합니다.\n";
		return;
	}

	int index = findWord(norm);
	if (index == -1) {
		cout << "The word '" << keyword << "' doesn't appear.\n";
		return;
	}

	cout << "The word '" << keyword << "' appears " << lineNums[index].size() << " times in lines:\n";
	for (int i : lineNums[index]) {
		cout << i << ": " << allLines[i] << endl;
	}
}

string normalize(string word) {
	string result = "";
	for (char c : word) {
		// 대문자 → 소문자
		if (c >= 'A' && c <= 'Z')
			c = c + ('a' - 'A');

		// 알파벳만 유지
		if (c >= 'a' && c <= 'z')
			result += c;
	}

	return result;
}

void sortIndex() {
	for (int i = 0; i < words.size() - 1; i++) {
		for (int j = i + 1; j < words.size(); j++) {
			if (words[i] > words[j]) {
				swap(words[i], words[j]);
				swap(lineNums[i], lineNums[j]);
			}
		}
	}
}

int main() {
	string command;

	while (true) {
		cout << endl;
		cout << "$  ";
		cin >> command;

		if (command == "read") {
			string fileName;
			cin >> fileName;
			makeIndex(fileName);
		}

		else if (command == "find") {
			string keyword;
			cin >> keyword;
			handle_find(keyword);
		}

		else if (command == "exit")
			break;
	}

	return 0;
}