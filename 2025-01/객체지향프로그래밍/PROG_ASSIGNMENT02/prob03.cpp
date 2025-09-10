#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int MAX = 100;

// ���ڿ��� �ҹ��ڷ� ��ȯ�ϴ� �Լ�
string lower(string word) {
    for (int i = 0; i < word.length(); i++) {
        word[i] = tolower(word[i]);
    }

    return word;
}

int main() {
    // �ܾ� �� ���� Ƚ�� ���� �迭
    string words[MAX];
    int words_count[MAX] = { 0 };

    string word;

    // ���� �ܾ� ���� (�ʱ⿡ 1�� ����)
    int count = 1;
    int idx = 0, tmp = 0;

    ifstream infile("input3.txt");

    // ù��° �ܾ� ����
    infile >> words[0];

    words_count[0] = 1;
    words[0] = lower(words[0]);

    // ���Ͽ��� �ܾ �ϳ��� ������ ó��
    while (infile >> word) {
        word = lower(word);

        // �ܾ� �ߺ� ���� Ȯ��
        bool duplicate = true;

        // ������ �ܾ�� ��
        for (int j = 0; j < count; j++) {
            // ������ ����� �ܾ� -> ���� ���� �� ���� �߰� X
            if (word == words[j]) {
                words_count[j]++;
                duplicate = false;
                break;
            }
        }

        // ���ο� �ܾ� -> �迭 �߰�
        if (duplicate) {
            words[count] = word;
            words_count[count] = 1;
            count++;
        }
    }

    // �ܾ� ����
    for (int i = 0; i < count; i++) {
        idx = 0;

        for (int j = 1; j < count - i; j++) {
            // ���� Ƚ���� �� ���� �ܾ� ã��
            if (words_count[j] < words_count[idx]) {
                idx = j;
            }
            // ���� Ƚ���� ���� ��� ������ �������� ��
            else if (words_count[j] == words_count[idx]) {
                if (words[j].compare(words[idx]) > 0) {
                    idx = j;
                }
            }
        }

        // �ܾ�� ���� Ƚ�� ����

        // ���� ���� ���� �ܾ� ����
        word = words[idx];
        words[idx] = words[count - i - 1];
        words[count - i - 1] = word;

        // �ش� �ܾ��� ���� Ƚ�� ����
        tmp = words_count[idx];
        words_count[idx] = words_count[count - i - 1];
        words_count[count - i - 1] = tmp;
    }

    for (int i = 0; i < count; i++) {
        cout << words[i] << ":" << words_count[i] << endl;
    }
}