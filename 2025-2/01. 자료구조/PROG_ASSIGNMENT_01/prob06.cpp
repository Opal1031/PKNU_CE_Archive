#include <iostream>
#include <string>

using namespace std;

int main() {
	while (true) {
		// ����, ������ ����, �ܾ��� ����, �ܾ��� ���� ����
		string sentence;
		int len = 0;
		int token = 0;
		bool Word_Flag = false;

		// ���� �Է�
		cout << "$ ";
		getline(cin, sentence);

		// ���α׷� ����
		if (sentence == "exit") {
			break;
		}

		// ������ ����
		len = sentence.length();

		// �ܾ��� ����
		for (char t : sentence) {
			// ������ �ƴϰ� �ܾ��� ������ �� token ����
			if (t != ' ' && !Word_Flag) {
				token++;
				Word_Flag = true;
			}

			// ������ �� �ܾ��� ��
			else if (t == ' ') {
				Word_Flag = false;
			}
		}

		cout << sentence << ":" << len << ":" << token << endl;
	}

	return 0;
}