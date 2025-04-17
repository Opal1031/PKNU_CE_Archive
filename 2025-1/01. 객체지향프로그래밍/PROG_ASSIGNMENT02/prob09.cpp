#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int main() {
    vector<string> words, descript; // 단어 & 설명 vector
    vector<string> dict; // 사전 vector

    string str, input; // 파일 읽기 & 검색할 단어
    int tap; // 각 단어의 \t의 인덱스
    size_t w_size = 0, prefix; // 단어 개수, 단어 길이

    // 파일 받기
    ifstream infile("shuffled_dict.txt");

    while (getline(infile, str))
        dict.push_back(str);

    // 사전 vector을 오름차순 정렬
    sort(dict.begin(), dict.end());

    // 각 단어에서 \t의 위치 확인 -> 슬라이싱을 통해 각각 words와 descript vector에 나눠서 저장
    for (int i = 0; i < dict.size(); i++) {
        tap = dict[i].find("\t");
        words.push_back(dict[i].substr(0, tap));
        descript.push_back(dict[i].substr(tap + 1));
    }

    cin >> input;

    w_size = words.size();

    // 단어가 사전에 존재할 때
    for (int i = 0; i < w_size; i++) {
        if (input.compare(words[i]) == 0) {
            cout << "Found" << endl;
            cout << words[i] << ": " << descript[i] << endl;
            cout << endl;
            break;
        }

        // 검색하는 단어가 사전에 존재하지 않으면
        else if (input.compare(words[i]) < 0) {
            cout << "Not found" << endl;

            // 첫 번째 단어 예외 처리 (이전 단어가 없음)
            if (i == 0) {
                cout << "+ " << words[i] << ": " << descript[i] << endl;
                cout << endl;
                break;
            }

            // 바로 앞뒤 단어 & 설명 출력
            else if (i > 0) {
                cout << "- " << words[i - 1] << ": " << descript[i - 1] << endl;
                cout << "+ " << words[i] << ": " << descript[i] << endl;
                cout << endl;
                break;
            }
        }

        // 마지막 단어 예외 처리 (이후 단어가 없음)
        if (i == w_size - 1) {
            cout << "- " << words[w_size - 1] << ": " << descript[w_size - 1] << endl;
            cout << endl;
        }
    }

    cout << "Results of prefix search:" << endl;

    // 접두어
    prefix = input.length();

    // 접두어가 같은 단어 & 설명 출력
    for (int i = 0; i < w_size; i++) {
        if (input.compare(words[i].substr(0, prefix)) == 0)
            cout << words[i] << ": " << descript[i] << endl;
    }

    return 0;
}