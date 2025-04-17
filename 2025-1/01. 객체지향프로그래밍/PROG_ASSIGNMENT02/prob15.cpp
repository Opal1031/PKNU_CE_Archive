#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
    // �Է� ������ ���� ��� ������ �غ�
    ifstream inputFile("table.txt");
    ofstream outputFile("output.txt");

    int row = 0, col = 0;
    inputFile >> row >> col;  // ��� ���� ���� �Է� ����
    inputFile.ignore();  // ���� ���� ����

    // ���̺� �����͸� ������ ����
    vector<vector<string>> table(row, vector<string>(col));

    // �� ���� �ִ� �ʺ� ������ ����
    vector<size_t> width_col(col, 0);
    string line;

    for (int i = 0; i < row; ++i) {
        size_t start = 0;
        int col = 0;

        // �� �� �б�
        getline(inputFile, line);

        // '&'�� �������� �� ���� �и��Ͽ� ����
        for (size_t j = 0; j < line.length(); ++j) {
            if (line[j] == '&' || j == line.length() - 1) {

                string cell = line.substr(start, j - start);  // �� ����

                // ������ ���ڰ� '&'�� �ƴ� ���
                if (j == line.length() - 1)
                    cell += line[j];

                table[i][col] = cell;  // �ش� ���� �� ����
                width_col[col] = max(width_col[col], cell.length());  // �� �ʺ� ����
                start = j + 1;  // ���� ���� ���� ��ġ
                ++col;  // �� �ε��� ����
            }
        }
    }

    // ��� (�� ���� ���� ����)
    for (int a = 0; a < row; ++a) {  // �� �࿡ ����
        for (size_t b = 0; b < col; ++b) {  // �� ���� ����
            outputFile << table[a][b];  // ���� ���

            // �� ���� ���� ���߱� (���� ���� ���̸� ���� ������ �߰�)
            if (b < col - 1)
                outputFile << string(width_col[b] - table[a][b].length() + 1, ' ');
        }

        outputFile << "\n";  // �� ���� ����ϰ� �ٹٲ�
    }

    return 0;
}