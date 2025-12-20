#include <iostream>
#include <string>

using namespace std;

// Stack 클래스
class Stack {
private:
    struct Node {
        string item;
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
    void push(const string& item, int num) {
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
    int topNum() {
        if (empty())
            throw runtime_error("stack empty");

        return top_node->num;
    }
};

int main() {
    // 문자열 입력 받기
    string line;
    getline(cin, line);

    Stack s;        // Stack 객체 생성
    int cnt = 1;    // 괄호 번호 카운터

    for (char ch : line) {
        // "(" 일 때 stack에 추가하고 번호 출력
        if (ch == '(') {
            s.push("(", cnt);
            cout << cnt << " ";
            cnt++;
        }

        // ")" 일 때
        else if (ch == ')') {
            // stack이 비어있으면 unbalanced 출력 후 종료
            if (s.empty()) {
                cout << "unbalanced" << endl;

                return 0;
            }

            // stack에서 top 번호 출력 후 제거
            cout << s.topNum() << " ";
            s.pop();
        }
    }

    cout << endl;

    return 0;
}