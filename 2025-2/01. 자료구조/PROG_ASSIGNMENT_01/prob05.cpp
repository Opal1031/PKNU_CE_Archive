#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// ���ĺ� �̿��� ���� ���� �Լ�
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
    // ���� �б�
    ifstream file("input4.txt");

    // �ܾ� ���� ����
    vector<vector <string>> words;
    string line;

    // ���Ͽ��� �� �پ� �б�
    while (getline(file, line)) {
        stringstream sstream(line);
        string token;

        // ������ �������� �ܾ� �и�
        while (getline(sstream, token, ' ')) {
            // ���ĺ� �̿��� ���� ����
            token = Alpha(token);

            // ���ǿ� �´� �ܾ ���Ϳ� �߰�
            if ((token.length() >= 2)) {
                bool Flag = false;

                // ������ �ִ� �ܾ����� Ȯ��
                for (auto& c : words) {
                    if (c[0] == token) {
                        c[1] = to_string(stoi(c[1]) + 1);
                        Flag = true;
                        break;
                    }
                }

                // ���ο� �ܾ��� ���Ϳ� �߰�
                if (!Flag) {
                    words.push_back({ token, "1" });
                }
            }
        }
    }

    // �ܾ� ������ ����
    sort(words.begin(), words.end());

    // ��� ���
    for (auto& w : words) {
        cout << w[0] << " " << w[1] << endl;
    }

    return 0;
}