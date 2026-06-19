#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 주어진 단어들에서 가장 긴 공통 접두사를 찾는 함수
string prefix(vector<string> words) {

    string prefix = words[0]; // 첫 번째 단어를 기준으로 접두사 설정

    for (int i = 1; i < words.size(); i++) {
        int j = 0;
        int min_length = prefix.length(); // 기본적으로 접두사의 길이를 최소 길이로 설정

        // 현재 단어가 더 짧으면 최소 길이 변경
        if (words[i].length() < min_length) {
            min_length = words[i].length();
        }

        // 최소 길이까지만 비교
        while (j < min_length) {
            if (prefix[j] != words[i][j])
                break;

            j++;
        }

        // 접두사 변경
        prefix = prefix.substr(0, j);

        // 공통 부분이 없으면 nothing으로 반환
        if (prefix.empty())
            prefix = "nothing";
    }

    return prefix;
}

int main() {
    int n;

    cin >> n;

    vector<string> words; // 단어를 저장할 벡터 생성

    for (int i = 0; i < n; i++) {
        string str;

        cin >> str;

        words.push_back(str); // 벡터에 단어 추가
    }

    // 가장 긴 공통 접두사 출력
    cout << prefix(words) << endl;

    return 0;
}