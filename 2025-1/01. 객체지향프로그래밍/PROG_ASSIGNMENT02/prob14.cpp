#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int main() {
    ifstream infile("harry.txt");

    vector<string> words;
    string word, text;
    int len = 0, count = 0;

    // ���� �б�
    while (infile >> word)
        words.push_back(word);

    // ���� & unique�� �̿��� �ߺ� ���� ����
    sort(words.begin(), words.end());
    words.erase(unique(words.begin(), words.end()), words.end());

    cin >> word;

    len = word.length();

    // �Է��� ���ξ�� �����ϴ� �ܾ� ���
    for (int i = 0; i < words.size(); i++) {
        text = words[i].substr(0, len);

        if (word.compare(text) == 0) {
            cout << words[i] << endl;

            count++;
        }
    }

    cout << count << endl;

    return 0;
}