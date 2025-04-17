#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int MAX = 100;

// 문자열을 소문자로 변환하는 함수
string lower(string word) {
    for (int i = 0; i < word.length(); i++) {
        word[i] = tolower(word[i]);
    }

    return word;
}

int main() {
    // 단어 및 등장 횟수 저장 배열
    string words[MAX];
    int words_count[MAX] = { 0 };

    string word;

    // 고유 단어 개수 (초기에 1로 설정)
    int count = 1;
    int idx = 0, tmp = 0;

    ifstream infile("input3.txt");

    // 첫번째 단어 읽음
    infile >> words[0];

    words_count[0] = 1;
    words[0] = lower(words[0]);

    // 파일에서 단어를 하나씩 읽으며 처리
    while (infile >> word) {
        word = lower(word);

        // 단어 중복 여부 확인
        bool duplicate = true;

        // 기존의 단어와 비교
        for (int j = 0; j < count; j++) {
            // 기존에 저장된 단어 -> 개수 증가 및 새로 추가 X
            if (word == words[j]) {
                words_count[j]++;
                duplicate = false;
                break;
            }
        }

        // 새로운 단어 -> 배열 추가
        if (duplicate) {
            words[count] = word;
            words_count[count] = 1;
            count++;
        }
    }

    // 단어 정렬
    for (int i = 0; i < count; i++) {
        idx = 0;

        for (int j = 1; j < count - i; j++) {
            // 등장 횟수가 더 적은 단어 찾기
            if (words_count[j] < words_count[idx]) {
                idx = j;
            }
            // 등장 횟수가 같은 경우 사전순 내림차순 비교
            else if (words_count[j] == words_count[idx]) {
                if (words[j].compare(words[idx]) > 0) {
                    idx = j;
                }
            }
        }

        // 단어와 등장 횟수 정렬

        // 가장 작은 빈도의 단어 저장
        word = words[idx];
        words[idx] = words[count - i - 1];
        words[count - i - 1] = word;

        // 해당 단어의 등장 횟수 저장
        tmp = words_count[idx];
        words_count[idx] = words_count[count - i - 1];
        words_count[count - i - 1] = tmp;
    }

    for (int i = 0; i < count; i++) {
        cout << words[i] << ":" << words_count[i] << endl;
    }
}