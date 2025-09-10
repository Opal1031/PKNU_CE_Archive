#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// �ܾ�ã�� Ŭ���� ����
class WordSearch {
public:
    vector<string> dictionary; // ���� �ܾ� ���� ����
    vector<vector<char>> field; // ���� ���� ����
    vector<string> foundWords; // �̹� ã�� �ܾ���� ������ ���� (�ߺ�����)

    int n;

    // ���� ������ �о� ditionary ���Ϳ� ����
    void Read_Dict(const string& filename) {
        ifstream file(filename);

        string word;

        // ���Ͽ��� �ܾ �ϳ��� �о� ����
        while (file >> word)
            dictionary.push_back(word);
    }

    // ���� ������ �о� field�� ���� ����
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

        // �Է� ���� �ȿ� ���ϴ��� ���� Ȯ��
        while (cx >= 0 && cy >= 0 && cx < n && cy < n) {
            word += field[cx][cy];

            // �̹� ã�� �ܾ �ƴ��� ���� Ȯ��
            bool found = false;

            for (const string& w : foundWords) {
                if (w == word) {
                    found = true;
                    break;
                }
            }

            // ������ �ְ�, ���� ã�� �ܾ �ƴ϶�� ���
            if (!found) {
                for (const string& dictWord : dictionary) {
                    if (word == dictWord) {
                        foundWords.push_back(word);

                        cout << word << endl;
                        break;  // ã������ �� �̻� dict Ž�� �� �ص� ��
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