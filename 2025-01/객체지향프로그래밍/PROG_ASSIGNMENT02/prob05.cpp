#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX = 1000; // �迭 ũ�� Ȯ��

int main() {
    string lines[MAX]; // �Էµ� ���� ���� �迭
    string line, delete_gap; // �� ���� ���ڿ� & ���� ���� ���ڿ� ����

    int lines_index = 0; // ����� ������ ������ ������ ����
    int word_count[MAX] = { 0 }; // �� ������ �ܾ� ������ �����ϴ� �迭

    ifstream infile("sample_lines.txt");

    // ���Ͽ��� �� �پ� �б�
    while (getline(infile, line)) {
        int word_start = -1, word_end = 0, word_index = 0;
        delete_gap.clear(); // ���� ���ŵ� ���ڿ� �ʱ�ȭ

        while (word_index < line.length()) {
            // ���� ã��
            word_end = line.find(" ", word_index);

            // ������ �ܾ� ó��
            if (word_end == -1) {
                if (word_start + 1 < line.length()) {
                    if (!delete_gap.empty())
                        delete_gap.append(" ");  // ������ �ܾ� �տ� ���� �߰�

                    delete_gap.append(line.substr(word_start + 1));
                    word_count[lines_index]++;
                }
                break;
            }

            // ���ӵ� ������ �ƴ� ��� �ܾ� �߰�
            if (word_end - 1 > word_start) {
                if (!delete_gap.empty())
                    delete_gap.append(" "); // �ܾ� �տ� ���� �߰�

                delete_gap.append(line.substr(word_start + 1, word_end - word_start - 1));
                word_count[lines_index]++;
            }

            word_start = word_end;
            word_index = word_end + 1;
        }

        // ���鸸 �ִ� ���� �������� ����
        if (!delete_gap.empty()) {
            lines[lines_index++] = delete_gap;
        }
    }

    // �ܾ� ������ �������� �������� ���� (���� ����)
    for (int i = 0; i < lines_index - 1; i++) {
        int max_index = i;

        for (int j = i + 1; j < lines_index; j++) {
            if (word_count[j] > word_count[max_index]) { // �������� ����
                max_index = j;
            }
        }

        swap(lines[i], lines[max_index]);
        swap(word_count[i], word_count[max_index]);
    }

    // ���ĵ� ��� ���
    for (int i = 0; i < lines_index; i++) {
        cout << lines[i] << ":" << word_count[i] << endl;
    }
}