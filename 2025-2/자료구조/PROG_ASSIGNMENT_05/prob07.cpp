#include <iostream>
#include <vector>

using namespace std;

// n이 행운수인지 판별하는 함수
bool isLucky(int n) {
    vector<int> lucky;

    // 1부터 1000000까지 lucky 벡터에 저장
    for (int i = 1; i <= 1000000; ++i) {
        lucky.push_back(i);
    }

    int idx = 1; // 2번째 수부터 시작

    // 행운수 생성 과정
    while (idx < lucky.size()) {
        int step = lucky[idx]; // 현재 단계에서 제거할 간격

        // 더 이상 제거할 수 없음
        if (step > lucky.size()) {
            break;
        }

        vector<int> temp; // 남아있는 수를 임시로 저장

        for (int i = 0; i < lucky.size(); ++i) {
            // step번째마다 수를 제거
            if ((i + 1) % step != 0) {
                temp.push_back(lucky[i]);
            }
        }

        lucky = temp; // lucky 벡터 갱신
        ++idx; // 다음 단계로 이동
    }

    // n이 lucky에 남아있는지 확인
    for (int x : lucky) {
        if (x == n) {
            return true; // n이 행운수임
        }
    }

    return false; // n이 행운수가 아님
}

int main() {
    int n;
    cin >> n; // 사용자로부터 n 입력받음

    // 행운수일 때
    if (isLucky(n)) {
        cout << "yes" << endl;
    }

    // 행운수가 아닐 때
    else {
        cout << "no" << endl;
    }

    return 0;
}