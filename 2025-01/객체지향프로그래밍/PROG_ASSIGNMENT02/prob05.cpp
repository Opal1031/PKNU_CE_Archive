#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX = 1000; // 배열 크기 확장

int main() {
    string lines[MAX]; // 입력된 라인 저장 배열
    string line, delete_gap; // 한 줄의 문자열 & 공백 제거 문자열 저장

    int lines_index = 0; // 저장된 라인의 개수를 저장할 변수
    int word_count[MAX] = { 0 }; // 각 라인의 단어 개수를 저장하는 배열

    ifstream infile("sample_lines.txt");

    // 파일에서 한 줄씩 읽기
    while (getline(infile, line)) {
        int word_start = -1, word_end = 0, word_index = 0;
        delete_gap.clear(); // 공백 제거된 문자열 초기화

        while (word_index < line.length()) {
            // 공백 찾기
            word_end = line.find(" ", word_index);

            // 마지막 단어 처리
            if (word_end == -1) {
                if (word_start + 1 < line.length()) {
                    if (!delete_gap.empty())
                        delete_gap.append(" ");  // 마지막 단어 앞에 공백 추가

                    delete_gap.append(line.substr(word_start + 1));
                    word_count[lines_index]++;
                }
                break;
            }

            // 연속된 공백이 아닐 경우 단어 추가
            if (word_end - 1 > word_start) {
                if (!delete_gap.empty())
                    delete_gap.append(" "); // 단어 앞에 공백 추가

                delete_gap.append(line.substr(word_start + 1, word_end - word_start - 1));
                word_count[lines_index]++;
            }

            word_start = word_end;
            word_index = word_end + 1;
        }

        // 공백만 있는 줄은 저장하지 않음
        if (!delete_gap.empty()) {
            lines[lines_index++] = delete_gap;
        }
    }

    // 단어 개수를 기준으로 내림차순 정렬 (선택 정렬)
    for (int i = 0; i < lines_index - 1; i++) {
        int max_index = i;

        for (int j = i + 1; j < lines_index; j++) {
            if (word_count[j] > word_count[max_index]) { // 내림차순 정렬
                max_index = j;
            }
        }

        swap(lines[i], lines[max_index]);
        swap(word_count[i], word_count[max_index]);
    }

    // 정렬된 결과 출력
    for (int i = 0; i < lines_index; i++) {
        cout << lines[i] << ":" << word_count[i] << endl;
    }
}