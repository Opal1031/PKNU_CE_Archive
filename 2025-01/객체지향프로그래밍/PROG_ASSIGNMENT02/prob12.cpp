#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, tmp;
    vector<int> v;

    cin >> n;

    // ���Ϳ� �ʱⰪ ����
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }

    // ���� �������� ����
    sort(v.begin(), v.end());

    // �ߺ��� ����
    v.erase(unique(v.begin(), v.end()), v.end());

    // ���
    cout << v.size() << ": ";

    for (auto result : v) {
        cout << result << " ";
    }

    return 0;
}