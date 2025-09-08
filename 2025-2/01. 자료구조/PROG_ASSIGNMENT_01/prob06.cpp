#include <iostream>
#include <string>

using namespace std;

int main() {
	while (true) {
		// 문장, 문장의 길이, 단어의 개수, 단어의 시작 여부
		string sentence;
		int len = 0;
		int token = 0;
		bool Word_Flag = false;

		// 문장 입력
		cout << "$ ";
		getline(cin, sentence);

		// 프로그램 종료
		if (sentence == "exit") {
			break;
		}

		// 문장의 길이
		len = sentence.length();

		// 단어의 개수
		for (char t : sentence) {
			// 공백이 아니고 단어의 시작일 때 token 증가
			if (t != ' ' && !Word_Flag) {
				token++;
				Word_Flag = true;
			}

			// 공백일 때 단어의 끝
			else if (t == ' ') {
				Word_Flag = false;
			}
		}

		cout << sentence << ":" << len << ":" << token << endl;
	}

	return 0;
}