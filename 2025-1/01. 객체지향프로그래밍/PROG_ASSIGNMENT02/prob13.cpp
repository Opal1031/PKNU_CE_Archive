#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 문자열의 길이를 기준으로 정렬하는 비교 함수
bool compare(string& a, string& b) {
    // 길이가 같으면 사전순 정렬
    if (a.size() == b.size())
        return a < b;

    // 길이가 짧은 순서대로 정렬
    return a.size() < b.size();
}

int main() {
    int n;
    string tmp;
    vector<string> v;

    cin >> n;

    // 벡터에 문자열 저장
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }

    // 정렬 (compare 함수 기준)
    sort(v.begin(), v.end(), compare);

    // 출력
    for (auto& result : v)
        cout << result << endl;

    return 0;
}