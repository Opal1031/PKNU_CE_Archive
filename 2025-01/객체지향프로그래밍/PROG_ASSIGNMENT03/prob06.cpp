#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// 단어찾기 클래스 정의
class WordSearch {
public:
    vector<string> dictionary; // 사전 단어 저장 벡터
    vector<vector<char>> field; // 퍼즐 문자 격자
    vector<string> foundWords; // 이미 찾은 단어들을 저장할 벡터 (중복방지)

    int n;

    // 사전 파일을 읽어 ditionary 벡터에 저장
    void Read_Dict(const string& filename) {
        ifstream file(filename);

        string word;

        // 파일에서 단어를 하나씩 읽어 저장
        while (file >> word)
            dictionary.push_back(word);
    }

    // 퍼즐 파일을 읽어 field에 문자 저장
    void Load_Puzzle(const string& filename) {
        ifstream file(filename);

        file >> n;

        field.resize(n, vector<char>(n));

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                file >> field[i][j];
    }

    void searchFrom(int x, int y, int dx, int dy) {
        string word;
        int cx = x, cy = y;

        // 입력 범위 안에 속하는지 먼저 확인
        while (cx >= 0 && cy >= 0 && cx < n && cy < n) {
            word += field[cx][cy];

            // 이미 찾은 단어가 아닌지 먼저 확인
            bool found = false;

            for (const string& w : foundWords) {
                if (w == word) {
                    found = true;
                    break;
                }
            }

            // 사전에 있고, 아직 찾은 단어가 아니라면 출력
            if (!found) {
                for (const string& dictWord : dictionary) {
                    if (word == dictWord) {
                        foundWords.push_back(word);

                        cout << word << endl;
                        break;  // 찾았으면 더 이상 dict 탐색 안 해도 됨
                    }
                }
            }

            cx += dx;
            cy += dy;
        }
    }

    void searchWords() {
        int directions[8][2] = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}
        };

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (auto& dir : directions)
                    searchFrom(i, j, dir[0], dir[1]);
    }
};

int main() {
    WordSearch ws;

    ws.Read_Dict("dictionary.txt");
    ws.Load_Puzzle("puzzle.txt");
    ws.searchWords();

    return 0;
}