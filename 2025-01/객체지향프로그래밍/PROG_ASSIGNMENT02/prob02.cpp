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
            // 공백 위치 찾기
            space_now = text.find(" ", idx);

            // 더 이상 공백이 없을 경우
            if (space_now == -1) {
                // 기존 문자열이 있다면 공백 추가
                if (ans.length() > 0)
                    ans.append(" ");

                // 마지막 단어 추가
                ans.append(text, space + 1, space_now - 1);
                break;
            }

            // 연속된 공백이 아닐 경우
            if (space_now - 1 > space) {
                // 기존 문자열이 있다면 공백 추가
                if (ans.length() > 0)
                    ans.append(" ");

                // 단어 추가
                ans.append(text, space + 1, space_now - space - 1);
            }

            // 이전 공백의 위치 업데이트
            space = space_now;

            // 다움 문자로 이동
            idx = space_now + 1;
        }

        // 종료
        if (ans.compare("exit") == 0)
            break;

        cout << ans << ":" << ans.length() << endl;

        ans.clear();
    }
}