#include <iostream>
#include <vector>
using namespace std;

void compute_set(vector<int>& A, vector<int>& B) {
    // ���ĵ� �� ���͸� ��ġ�鼭 �ߺ��� �����ϴ� �Լ�
    vector<int> tmp; // �ӽ� ����

    while (true) {
        // A�� ����� ���, ���� �ִ� B�� ��� ��Ҹ� tmp�� �߰��ϰ� ����
        if (A.size() == 0) {
            while (B.size()) {
                tmp.push_back(B[0]);
                B.erase(B.begin());
            }
            break;
        }

        // B�� ����� ���, ���� �ִ� A�� ��� ��Ҹ� tmp�� �߰��ϰ� ����
        else if (B.size() == 0) {
            while (A.size()) {
                tmp.push_back(A[0]);
                A.erase(A.begin());
            }
            break;
        }

        // A�� B�� ù ��° ���Ҹ� ���Ͽ� ���� ���� tmp�� �߰��ϰ� �ش� ���� ����
        if (A[0] < B[0]) {
            tmp.push_back(A[0]);
            A.erase(A.begin());
        }

        // B�� ���� �� ������ B�� ù ��° ���Ҹ� �߰��ϰ� ����
        else if (A[0] > B[0]) {
            tmp.push_back(B[0]);
            B.erase(B.begin());
        }

        // A�� B�� ù ��° ���Ұ� ������ �ߺ��̹Ƿ� �� �� ����
        else {
            A.erase(A.begin());
            B.erase(B.begin());
        }
    }

    // ���յ� ����� A�� ����
    A.insert(A.end(), tmp.begin(), tmp.end());
}

int main() {
    int m, n, k;

    vector<int> first, second;

    cin >> m;

    // m���� ������ ������������ ���ĵǾ� �Էµȴ�.
    for (int i = 0; i < m; i++) {
        cin >> k;

        first.push_back(k);
    }

    cin >> n;

    // n���� ������ ������������ ���ĵǾ� �Էµȴ�.
    for (int i = 0; i < n; i++) {
        cin >> k;

        second.push_back(k);
    }

    compute_set(first, second);

    for (auto item : first)
        cout << item << " ";

    cout << endl;

    return 0;
}