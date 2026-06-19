#include <iostream>
using namespace std;

int main(void) {
    int prev = 2147483647, curr, next; // 처음 입력되는 숫자와 비교하기 위한 prev를 int형의 최대값으로 설정
    int count = 0;

    cin >> curr; // 첫번째 입력

    while (true) {
        cin >> next; // 숫자 입력

        // 3개 입력 후 끝나는 경우
        if (next == -1) {
            next = 2147483647; // 두번째 숫자와 비교하기 위한 next를 int형의 최대값으로 설정

            if (curr <= prev && curr <= next) // 극소값 찾기
                count++;
            break;
        }

        // 극소값 찾기
        if (curr <= prev && curr <= next)
            count++;

        // 다음 입력되는 값과 비교를 위한 변경
        prev = curr;
        curr = next;
    }

    cout << count << endl;

    return 0;
}