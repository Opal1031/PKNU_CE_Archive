#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	string str; // �� �ܾ Ȯ��
	vector<string> words; // sort�� �ܾ�� ���� ����

	while (true) {
		cin >> str;

		if (str.compare("exit") == 0)
			break;

		// �̹� ��Ͽ� ��ϵ� ���ڿ����� �˻�
		bool found = false;

		for (int j = 0; j < words.size(); j++) {
			if (words[j] == str) {
				found = true;

				cout << "duplicate" << endl;
				break;
			}
		}

		// duplicate�� words ��� ���� ��������
		if (found)
			continue;

		// ��Ͽ� ���� ���ڿ��� ��Ͽ� �߰�
		if (!found)
			words.push_back(str);

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
			cout << words[k] << " ";

		cout << endl;
	}


	return 0;
}