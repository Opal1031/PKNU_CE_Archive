#include <iostream>
#include <string>
#include <list>

using namespace std;

// Stack 클래스
class Stack {
private:
    struct Node {
        int item;
        int num;

        Node* next;
    };
    Node* top_node;

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

    // stack에 item과 num 추가
    void push(int item, int num) {
        Node* newNode = new Node{ item, num, top_node };

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

    // stack의 top num 반환
    int topNum() {
        if (empty())
            throw runtime_error("stack empty");

        return top_node->num;
    }
};

int main() {
    // 정수 N 입력 받기
    int N;
    cin >> N;

    // Stack 객체와 정수 리스트 생성
    Stack s;
    list<int> arr;

    // N개의 정수 입력 받기
    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;

        arr.push_back(x);
    }

    for (int j = 0; j < N; ++j) {
        // 리스트의 앞에서부터 정수 하나씩 처리
        int cur = arr.front();
        arr.pop_front();

        // stack의 top이 현재 정수 이하인 동안 pop 수행
        while (!s.empty() && s.topItem() <= cur) {
            s.pop();
        }

        // 현재 정수를 stack에 push하고 번호 출력
        int num = s.empty() ? 1 : s.topNum() + 1;
        s.push(cur, num);

        cout << s.topNum() << " ";
    }
}