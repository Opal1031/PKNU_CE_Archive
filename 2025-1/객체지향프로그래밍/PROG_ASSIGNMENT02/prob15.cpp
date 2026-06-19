#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
    // 입력 파일을 열고 출력 파일을 준비
    ifstream inputFile("table.txt");
    ofstream outputFile("output.txt");

    int row = 0, col = 0;
    inputFile >> row >> col;  // 행과 열의 수를 입력 받음
    inputFile.ignore();  // 개행 문자 제거

    // 테이블 데이터를 저장할 벡터
    vector<vector<string>> table(row, vector<string>(col));

    // 각 열의 최대 너비를 추적할 벡터
    vector<size_t> width_col(col, 0);
    string line;

    for (int i = 0; i < row; ++i) {
        size_t start = 0;
        int col = 0;

        // 한 줄 읽기
        getline(inputFile, line);

        // '&'를 기준으로 각 셀을 분리하여 저장
        for (size_t j = 0; j < line.length(); ++j) {
            if (line[j] == '&' || j == line.length() - 1) {

                string cell = line.substr(start, j - start);  // 셀 추출

                // 마지막 문자가 '&'가 아닌 경우
                if (j == line.length() - 1)
                    cell += line[j];

                table[i][col] = cell;  // 해당 셀에 값 저장
                width_col[col] = max(width_col[col], cell.length());  // 열 너비 갱신
                start = j + 1;  // 다음 셀의 시작 위치
                ++col;  // 열 인덱스 증가
            }
        }
    }

    // 출력 (각 열을 맞춰 정렬)
    for (int a = 0; a < row; ++a) {  // 각 행에 대해
        for (size_t b = 0; b < col; ++b) {  // 각 열에 대해
            outputFile << table[a][b];  // 셀을 출력

            // 열 간의 간격 맞추기 (현재 셀의 길이를 빼고 공백을 추가)
            if (b < col - 1)
                outputFile << string(width_col[b] - table[a][b].length() + 1, ' ');
        }

        outputFile << "\n";  // 한 행을 출력하고 줄바꿈
    }

    return 0;
}