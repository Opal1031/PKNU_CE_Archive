#include <iostream>
#include <string>
#include <vector>

using namespace std;

// �־��� �ܾ�鿡�� ���� �� ���� ���λ縦 ã�� �Լ�
string prefix(vector<string> words) {

    string prefix = words[0]; // ù ��° �ܾ �������� ���λ� ����

    for (int i = 1; i < words.size(); i++) {
        int j = 0;
        int min_length = prefix.length(); // �⺻������ ���λ��� ���̸� �ּ� ���̷� ����

        // ���� �ܾ �� ª���� �ּ� ���� ����
        if (words[i].length() < min_length) {
            min_length = words[i].length();
        }

        // �ּ� ���̱����� ��
        while (j < min_length) {
            if (prefix[j] != words[i][j])
                break;

            j++;
        }

        // ���λ� ����
        prefix = prefix.substr(0, j);

        // ���� �κ��� ������ nothing���� ��ȯ
        if (prefix.empty())
            prefix = "nothing";
    }

    return prefix;
}

int main() {
    int n;

    cin >> n;

    vector<string> words; // �ܾ ������ ���� ����

    for (int i = 0; i < n; i++) {
        string str;

        cin >> str;

        words.push_back(str); // ���Ϳ� �ܾ� �߰�
    }

    // ���� �� ���� ���λ� ���
    cout << prefix(words) << endl;

    return 0;
}