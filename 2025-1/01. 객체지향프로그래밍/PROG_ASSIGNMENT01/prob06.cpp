#include <iostream>
using namespace std;

int main(void) {
    int prev = 2147483647, curr, next; // ó�� �ԷµǴ� ���ڿ� ���ϱ� ���� prev�� int���� �ִ밪���� ����
    int count = 0;

    cin >> curr; // ù��° �Է�

    while (true) {
        cin >> next; // ���� �Է�

        // 3�� �Է� �� ������ ���
        if (next == -1) {
            next = 2147483647; // �ι�° ���ڿ� ���ϱ� ���� next�� int���� �ִ밪���� ����

            if (curr <= prev && curr <= next) // �ؼҰ� ã��
                count++;
            break;
        }

        // �ؼҰ� ã��
        if (curr <= prev && curr <= next)
            count++;

        // ���� �ԷµǴ� ���� �񱳸� ���� ����
        prev = curr;
        curr = next;
    }

    cout << count << endl;

    return 0;
}