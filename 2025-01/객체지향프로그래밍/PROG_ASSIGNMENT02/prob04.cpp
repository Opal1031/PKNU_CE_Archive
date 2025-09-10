#include <iostream>
#include <string>
using namespace std;

int main() {
    int sum = 0, start_idx = 0, n = 0, len = 0;
    string s;

    getline(cin, s);

    // ù ��° ���ڰ� ������ ��츦 ����Ͽ� ���� �տ� 0�� �߰�
    s.insert(0, "0");

    // ������ ���� �����ڸ� ����, +�� �⺻������ ����
    char before_oper = '+';

    for (int i = 0; i < s.length(); i++) {
        // �������� ���
        if (isdigit(s.at(i)) == false) {
            // ���� ���ڸ� �����ڿ� ���� ���
            if (before_oper == '+')
                sum += stoi(s.substr(start_idx, len));
            if (before_oper == '-')
                sum -= stoi(s.substr(start_idx, len));


            // ���ο� ���� ���� ��ġ / ���ο� ���� ���� �ʱ�ȭ / ���� ������ ����
            start_idx = i + 1;
            len = 1;
            before_oper = s.at(i);
        }

        // ������ ���� ó��(���ڿ��� ��)
        if (i == s.length() - 1 && before_oper == '+')
            sum += stoi(s.substr(start_idx, len));
        if (i == s.length() - 1 && before_oper == '-')
            sum -= stoi(s.substr(start_idx, len));

        // ������ ���� ����
        len++;
    }

    cout << sum << endl;

    return 0;
}