#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // ���� �б�
    ifstream file("input4.txt");

    // �ܾ� ���� ����
    vector<string> words;
    string line;

    // ���Ͽ��� �� �پ� �б�
    while (getline(file, line)) {
        stringstream sstream(line);
        string token;

        // ������ �������� �ܾ� �и�
        while (getline(sstream, token, ' ')) {
            // ���ǿ� �´� �ܾ ���Ϳ� �߰�
            if ((token.length() >= 2) && (find(words.begin(), words.end(), token) == words.end())) {
                words.push_back(token);
            }
        }
    }

    // ��� ���
    for (auto& w : words) {
        cout << w << endl;
    }

    return 0;
}