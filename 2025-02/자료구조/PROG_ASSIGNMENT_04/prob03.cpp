#include <iostream>
#include <string>

using namespace std;

// Stack 클래스
class Stack {
private:
    struct Node {
        int item;
        Node* next;
    };

    Node* top_node = nullptr;

public:
    // 소멸자(Destructor)
    ~Stack() {
        while (!empty()) {
            pop();
        }
    }

    // stack이 비어있는지 확인
    bool empty() {
        return top_node == nullptr;
    }

    // stack에 item 추가
    void push(int item) {
        Node* newNode = new Node{ item, top_node };
        top_node = newNode;
    }

    // stack에서 top item 제거
    void pop() {
        if (empty())
            throw runtime_error("stack empty");

        Node* tmp = top_node;
        top_node = top_node->next;
        delete tmp;
    }

    // stack의 top item 반환
    int topItem() {
        if (empty())
            throw runtime_error("stack empty");

        return top_node->item;
    }

    // Stack을 문자열로 변환 (역순)
    string toString(int size) {
        string result;
        Node* curr = top_node;

        // 임시 배열 생성
        int* arr = new int[size];
        int idx = 0;

        // Stack의 item을 순서대로 확인
        while (curr && idx < size) {
            arr[idx++] = curr->item;
            curr = curr->next;
        }

        // 역순으로 문자열 생성
        for (int i = idx - 1; i >= 0; --i) {
            result += to_string(arr[i]);
        }

        delete[] arr;

        return result;
    }
};

int main() {
    // 문자열 N과 정수 K 입력 받기
    string N;
    int K;
    cin >> N >> K;

    int len = N.length();
    Stack s;

    // 앞에서부터 큰 수를 남기고,
    // 남은 K만큼 뒤에서 잘라내기

    // N의 각 자리 숫자에 대해 처리
    for (int i = 0; i < len; ++i) {
        // stoi로 한 자리씩 변환
        int digit = stoi(string(1, N[i]));

        // 스택이 비어있지 않고 & K > 0 & 스택 top이 현재 digit보다 작으면 pop
        while (!s.empty() && K > 0 && s.topItem() < digit) {
            s.pop();
            K--;
        }
        s.push(digit);
    }

    // K가 남아있으면 뒤에서 pop
    while (K > 0) {
        s.pop();
        K--;
    }

    // Stack에 남은 숫자를 정답 문자열로 변환
    string result = s.toString(len - K);

    cout << result << endl;

    return 0;
}