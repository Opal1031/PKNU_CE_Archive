#include <iostream>
#include <string>
using namespace std;

int main() {
    int sum = 0, start_idx = 0, n = 0, len = 0;
    string s;

    getline(cin, s);

    // 첫 번째 숫자가 음수일 경우를 대비하여 가장 앞에 0을 추가
    s.insert(0, "0");

    // 숫자의 직전 연산자를 저장, +를 기본값으로 시작
    char before_oper = '+';

    for (int i = 0; i < s.length(); i++) {
        // 연산자일 경우
        if (isdigit(s.at(i)) == false) {
            // 이전 숫자를 연산자에 따라 계산
            if (before_oper == '+')
                sum += stoi(s.substr(start_idx, len));
            if (before_oper == '-')
                sum -= stoi(s.substr(start_idx, len));


            // 새로운 숫자 시작 위치 / 새로운 숫자 길이 초기화 / 현재 연산자 저장
            start_idx = i + 1;
            len = 1;
            before_oper = s.at(i);
        }

        // 마지막 숫자 처리(문자열의 끝)
        if (i == s.length() - 1 && before_oper == '+')
            sum += stoi(s.substr(start_idx, len));
        if (i == s.length() - 1 && before_oper == '-')
            sum -= stoi(s.substr(start_idx, len));

        // 숫자의 길이 증가
        len++;
    }

    cout << sum << endl;

    return 0;
}