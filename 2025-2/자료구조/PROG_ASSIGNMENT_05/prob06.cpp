#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// 거리 계산
int distance(string& a, string& b) {
    int cnt = 0;

    for (auto i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            ++cnt;
        }
    }

    return cnt;
}

int main() {
    string input;
    int K;

    cin >> input >> K;

    int N = input.size();
    int max_num = pow(2, N);

    vector<string> result;

    // 모든 이진수 생성
    for (int i = 0; i < max_num; ++i) {
        string bin = "";

        for (int j = N - 1; j >= 0; --j) {
            bin += (i / (int)pow(2, j)) % 2 ? '1' : '0';
        }

        if (distance(input, bin) == K)
            result.push_back(bin);
    }

    // 결과 출력
    for (auto& s : result)
        cout << s << endl;

    return 0;
}