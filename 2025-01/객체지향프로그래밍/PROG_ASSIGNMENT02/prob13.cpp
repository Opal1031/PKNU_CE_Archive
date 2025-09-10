#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ���ڿ��� ���̸� �������� �����ϴ� �� �Լ�
bool compare(string& a, string& b) {
    // ���̰� ������ ������ ����
    if (a.size() == b.size())
        return a < b;

    // ���̰� ª�� ������� ����
    return a.size() < b.size();
}

int main() {
    int n;
    string tmp;
    vector<string> v;

    cin >> n;

    // ���Ϳ� ���ڿ� ����
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }

    // ���� (compare �Լ� ����)
    sort(v.begin(), v.end(), compare);

    // ���
    for (auto& result : v)
        cout << result << endl;

    return 0;
}