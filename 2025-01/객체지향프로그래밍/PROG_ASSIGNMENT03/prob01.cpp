// �Է����� �ϳ��� �ؽ�Ʈ ������ �д´�.
// ���Ͽ� �����ϴ� ��� �ܾ���� ����� �����, �� �ܾ �ؽ�Ʈ ���Ͽ� �����ϴ� ���� ��ȣ�� �����Ѵ�.
// ����ڰ� ��û�ϸ� �ε���(�ܾ�� ���ι�ȣ)�� �ϳ��� ���Ϸ� �����Ѵ�.
// ����ڰ� �ܾ �˻��ϸ� �� �ܾ �ؽ�Ʈ ���Ͽ� �� �� �����ϴ���, �׸��� �� ��° �ٿ� �����ϴ��� ����Ѵ�.

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

	// �� �ܾ �����ϴ� ���� ��ȣ�� �˾ƾ� �ϹǷ� �� ���� �� ���ξ� �Է¹ޱ�
	while (getline(theFile, line)) {
		// ��ü ���� ����
		allLines.push_back(line);
		vector<string> tokens = split_line(line);

		// split�� ������ �ܾ���� ��Ͽ� �߰�
		for (auto token : tokens) {
			addWord(token, lineNum);
		}
		lineNum++;
	}
	theFile.close();

	// ������ �ε��� ������ �� ����
	sortIndex();
}


vector<string> split_line(string line, char delimiter) {
	vector<string> tokens;

	// ���ڿ� line�� �����ϴ� stringstream�� ����
	stringstream sstream(line);

	string str;

	while (getline(sstream, str, delimiter))
		tokens.push_back(str);

	return tokens;
}

void addWord(string word, int lineNum) {
	string norm = normalize(word);

	// ���̰� 3 �̸��� �ܾ� ����
	if (norm.length() < 3)
		return;

	int index = findWord(norm);
	if (index != -1) {
		// ���� ���� �ߺ� ����
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
		cout << "�˻���� 3�� �̻��̾�� �մϴ�.\n";
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
		// �빮�� �� �ҹ���
		if (c >= 'A' && c <= 'Z')
			c = c + ('a' - 'A');

		// ���ĺ��� ����
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