#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int main() {
    ifstream infile("harry.txt");

    vector<string> words;
    string word, text;
    int len = 0, count = 0;

    // 파일 읽기
    while (infile >> word)
        words.push_back(word);

    // 정렬 & unique를 이용한 중복 원소 제거
    sort(words.begin(), words.end());
    words.erase(unique(words.begin(), words.end()), words.end());

    cin >> word;

    len = word.length();

    // 입력한 접두어로 시작하는 단어 출력
    for (int i = 0; i < words.size(); i++) {
        text = words[i].substr(0, len);

        if (word.compare(text) == 0) {
            cout << words[i] << endl;

            count++;
        }
    }

    cout << count << endl;

    return 0;
}