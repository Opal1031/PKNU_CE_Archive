#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 파일 읽기
    ifstream file("input4.txt");

    // 단어 저장 벡터
    vector<string> words;
    string line;

    // 파일에서 한 줄씩 읽기
    while (getline(file, line)) {
        stringstream sstream(line);
        string token;

        // 공백을 기준으로 단어 분리
        while (getline(sstream, token, ' ')) {
            // 조건에 맞는 단어만 벡터에 추가
            if ((token.length() >= 2) && (find(words.begin(), words.end(), token) == words.end())) {
                words.push_back(token);
            }
        }
    }

    // 결과 출력
    for (auto& w : words) {
        cout << w << endl;
    }

    return 0;
}