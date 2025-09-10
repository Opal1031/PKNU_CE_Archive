#include <iostream>
#include <vector>
using namespace std;

void compute_set(vector<int>& A, vector<int>& B) {
    // 정렬된 두 벡터를 합치면서 중복을 제거하는 함수
    vector<int> tmp; // 임시 벡터

    while (true) {
        // A가 비었을 경우, 남아 있는 B의 모든 요소를 tmp에 추가하고 종료
        if (A.size() == 0) {
            while (B.size()) {
                tmp.push_back(B[0]);
                B.erase(B.begin());
            }
            break;
        }

        // B가 비었을 경우, 남아 있는 A의 모든 요소를 tmp에 추가하고 종료
        else if (B.size() == 0) {
            while (A.size()) {
                tmp.push_back(A[0]);
                A.erase(A.begin());
            }
            break;
        }

        // A와 B의 첫 번째 원소를 비교하여 작은 값을 tmp에 추가하고 해당 원소 제거
        if (A[0] < B[0]) {
            tmp.push_back(A[0]);
            A.erase(A.begin());
        }

        // B의 값이 더 작으면 B의 첫 번째 원소를 추가하고 제거
        else if (A[0] > B[0]) {
            tmp.push_back(B[0]);
            B.erase(B.begin());
        }

        // A와 B의 첫 번째 원소가 같으면 중복이므로 둘 다 제거
        else {
            A.erase(A.begin());
            B.erase(B.begin());
        }
    }

    // 병합된 결과를 A에 저장
    A.insert(A.end(), tmp.begin(), tmp.end());
}

int main() {
    int m, n, k;

    vector<int> first, second;

    cin >> m;

    // m개의 정수가 오름차순으로 정렬되어 입력된다.
    for (int i = 0; i < m; i++) {
        cin >> k;

        first.push_back(k);
    }

    cin >> n;

    // n개의 정수가 오름차순으로 정렬되어 입력된다.
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