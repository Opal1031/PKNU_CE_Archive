#include <iostream>
#include <string>
using namespace std;

int main() {
    int space = 0, space_now = 0, idx = 0;
    string text, ans;

    while (true) {
        space = -1, space_now = 0, idx = 0;

        getline(cin, text);

        while (idx < text.length()) {
            // ���� ��ġ ã��
            space_now = text.find(" ", idx);

            // �� �̻� ������ ���� ���
            if (space_now == -1) {
                // ���� ���ڿ��� �ִٸ� ���� �߰�
                if (ans.length() > 0)
                    ans.append(" ");

                // ������ �ܾ� �߰�
                ans.append(text, space + 1, space_now - 1);
                break;
            }

            // ���ӵ� ������ �ƴ� ���
            if (space_now - 1 > space) {
                // ���� ���ڿ��� �ִٸ� ���� �߰�
                if (ans.length() > 0)
                    ans.append(" ");

                // �ܾ� �߰�
                ans.append(text, space + 1, space_now - space - 1);
            }

            // ���� ������ ��ġ ������Ʈ
            space = space_now;

            // �ٿ� ���ڷ� �̵�
            idx = space_now + 1;
        }

        // ����
        if (ans.compare("exit") == 0)
            break;

        cout << ans << ":" << ans.length() << endl;

        ans.clear();
    }
}