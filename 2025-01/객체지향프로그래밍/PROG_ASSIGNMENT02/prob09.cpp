#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int main() {
    vector<string> words, descript; // �ܾ� & ���� vector
    vector<string> dict; // ���� vector

    string str, input; // ���� �б� & �˻��� �ܾ�
    int tap; // �� �ܾ��� \t�� �ε���
    size_t w_size = 0, prefix; // �ܾ� ����, �ܾ� ����

    // ���� �ޱ�
    ifstream infile("shuffled_dict.txt");

    while (getline(infile, str))
        dict.push_back(str);

    // ���� vector�� �������� ����
    sort(dict.begin(), dict.end());

    // �� �ܾ�� \t�� ��ġ Ȯ�� -> �����̽��� ���� ���� words�� descript vector�� ������ ����
    for (int i = 0; i < dict.size(); i++) {
        tap = dict[i].find("\t");
        words.push_back(dict[i].substr(0, tap));
        descript.push_back(dict[i].substr(tap + 1));
    }

    cin >> input;

    w_size = words.size();

    // �ܾ ������ ������ ��
    for (int i = 0; i < w_size; i++) {
        if (input.compare(words[i]) == 0) {
            cout << "Found" << endl;
            cout << words[i] << ": " << descript[i] << endl;
            cout << endl;
            break;
        }

        // �˻��ϴ� �ܾ ������ �������� ������
        else if (input.compare(words[i]) < 0) {
            cout << "Not found" << endl;

            // ù ��° �ܾ� ���� ó�� (���� �ܾ ����)
            if (i == 0) {
                cout << "+ " << words[i] << ": " << descript[i] << endl;
                cout << endl;
                break;
            }

            // �ٷ� �յ� �ܾ� & ���� ���
            else if (i > 0) {
                cout << "- " << words[i - 1] << ": " << descript[i - 1] << endl;
                cout << "+ " << words[i] << ": " << descript[i] << endl;
                cout << endl;
                break;
            }
        }

        // ������ �ܾ� ���� ó�� (���� �ܾ ����)
        if (i == w_size - 1) {
            cout << "- " << words[w_size - 1] << ": " << descript[w_size - 1] << endl;
            cout << endl;
        }
    }

    cout << "Results of prefix search:" << endl;

    // ���ξ�
    prefix = input.length();

    // ���ξ ���� �ܾ� & ���� ���
    for (int i = 0; i < w_size; i++) {
        if (input.compare(words[i].substr(0, prefix)) == 0)
            cout << words[i] << ": " << descript[i] << endl;
    }

    return 0;
}