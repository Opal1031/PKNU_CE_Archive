#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, tmp;
    vector<int> v;

    cin >> n;

    // 벡터에 초기값 저장
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }

    // 벡터 오름차순 정렬
    sort(v.begin(), v.end());

    // 중복값 제거
    v.erase(unique(v.begin(), v.end()), v.end());

    // 출력
    cout << v.size() << ": ";

    for (auto result : v) {
        cout << result << " ";
    }

    return 0;
}