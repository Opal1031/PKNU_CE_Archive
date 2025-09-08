#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// 알파벳 이외의 문자 제거 함수
string Alpha(const string& s) {
    string result;

    for (char c : s) {
        if (isalpha(static_cast<char>(c))) {
            result += c;
        }
    }

    return result;
}

int main() {
    // 파일 읽기
    ifstream file("input4.txt");

    // 단어 저장 벡터
    vector<vector <string>> words;
    string line;

    // 파일에서 한 줄씩 읽기
    while (getline(file, line)) {
        stringstream sstream(line);
        string token;

        // 공백을 기준으로 단어 분리
        while (getline(sstream, token, ' ')) {
            // 알파벳 이외의 문자 제거
            token = Alpha(token);

            // 조건에 맞는 단어만 벡터에 추가
            if ((token.length() >= 2)) {
                bool Flag = false;

                // 기존에 있는 단어인지 확인
                for (auto& c : words) {
                    if (c[0] == token) {
                        c[1] = to_string(stoi(c[1]) + 1);
                        Flag = true;
                        break;
                    }
                }

                // 새로운 단어라면 벡터에 추가
                if (!Flag) {
                    words.push_back({ token, "1" });
                }
            }
        }
    }

    // 단어 사전순 정렬
    sort(words.begin(), words.end());

    // 결과 출력
    for (auto& w : words) {
        cout << w[0] << " " << w[1] << endl;
    }

    return 0;
}