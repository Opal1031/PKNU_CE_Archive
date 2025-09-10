#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	ifstream infile("sample.txt");

	string str; // �� �ܾ Ȯ��
	vector<string> words; // sort�� �ܾ�� ���� ����

	while (infile >> str) { // ������ ���� �����ϸ� false�� ��ȯ�ϱ� ������ �ݺ��� �����
		int s = 0, t = str.length() - 1; // ������ & ����

		// ���ڿ����� �տ������� ó������ �����ϴ� ���ĺ��̳� ������ ��ġ s ã��

		// ���ĺ��̳� ���ڰ� �ƴϸ� ���� �ε���
		while (s < str.length() && !isalnum(str[s]))
			s++;

		// �ڿ������� �˻�
		while (t >= 0 && !isalnum(str[t]))
			t--;

		if (s <= t) { // �����ִ� ���ڰ� �ϳ��� ���ٸ�
			// �ش� ���ڿ� �߶󳻱�
			string pure_word = str.substr(s, t - s + 1);

			// ��� ���� �ҹ��ڷ� ��ȯ
			for (int i = 0; i < pure_word.length(); i++)
				pure_word[i] = tolower(pure_word[i]);

			// �̹� ��Ͽ� ��ϵ� ���ڿ����� �˻�
			bool found = false;

			for (int j = 0; j < words.size(); j++) {
				if (words[j] == pure_word) {
					found = true;
					break;
				}
			}

			// ��Ͽ� ���� ���ڿ��� ��Ͽ� �߰�
			if (!found)
				words.push_back(pure_word);
		}
	}

	// ���� �ݱ�
	infile.close();

	for (int p = 0; p < words.size() - 1; p++) {
		for (int q = 0; q < words.size() - 1 - p; q++) {
			if (words[q] > words[q + 1]) {
				// �ܾ ���������� �ڿ� ������ ��ȯ
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