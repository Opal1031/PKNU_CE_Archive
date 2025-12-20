#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    int x, y, w, h;

    Node* next;
};
Node* head = nullptr;

void print_list() {
    Node* p = head;

    while (p != nullptr) {
        cout << p->x << " " << p->y << " " << p->w << " " << p->h << endl;
        p = p->next;
    }
}

void read_file() {
    // rect.txt 파일을 읽어서 사각형들을 파일에 저장된 순서대로
    // head가 가리키는 연결리스트에 저장한다.

    ifstream file("rects.txt");

    int N;
    file >> N;

    for (int i = 0; i < N; i++) {
        // x, y, w, h를 파일에서 읽음
        int x, y, w, h;
        file >> x >> y >> w >> h;

        // 새로운 노드 생성
        Node* newNode = new Node{ x, y, w, h, nullptr };

        // 연결리스트의 마지막에 newNode를 추가
        if (head == nullptr)
            head = newNode;

        else {
            Node* p = head;

            while (p->next != nullptr)
                p = p->next;

            p->next = newNode;
        }
    }
}

void sort_by_area() {
    // head가 가리키는 연결리스트를 면적순으로 정렬한다.

    // 노드의 개수가 0개이거나 1개이면 정렬할 필요가 없다.
    if (head == nullptr || head->next == nullptr)
        return;

    Node* sorted = nullptr;         // 정렬된 연결리스트의 헤드 포인터
    Node* tail = nullptr;           // 정렬된 연결리스트의 꼬리 포인터

    while (head != nullptr) {
        Node* minPrev = nullptr;    // 최소 면적 노드의 이전 노드
        Node* minNode = head;       // 최소 면적 노드

        Node* prev = head;          // 현재 노드의 이전 노드
        Node* curr = head->next;    // 현재 노드

        // 최소 면적 노드 찾기
        while (curr != nullptr) {
            if (curr->w * curr->h < minNode->w * minNode->h) {
                minPrev = prev;
                minNode = curr;
            }

            prev = curr;
            curr = curr->next;
        }

        // 최소 면적 노드를 기존 연결리스트에서 제거
        if (minPrev != nullptr)
            minPrev->next = minNode->next;

        else
            head = minNode->next;

        // 정렬된 연결리스트에 최소 면적 노드 추가
        // 정렬된 연결리스트가 비어있으면 첫 번째 노드로 추가
        if (sorted == nullptr) {
            sorted = minNode;
            tail = minNode;
        }

        // 정렬된 연결리스트가 비어있지 않으면 꼬리에 추가하고 tail 갱신
        else {
            tail->next = minNode;
            tail = minNode;
        }

        // 꼬리 노드의 next를 nullptr로 설정
        minNode->next = nullptr;
    }

    // head를 정렬된 연결리스트로 갱신
    head = sorted;
}

// 어떤 노드 뒤의 노드 삭제하는 함수
Node* remove_after(Node* prev) {
    Node* tmp = prev->next;

    if (tmp == nullptr)
        return nullptr;

    else {
        prev->next = tmp->next;
        return tmp;
    }
}

void remove_rects(int minw, int minh) {
    Node* curr = head;
    Node* prev = nullptr;

    while (curr != nullptr) {
        if (curr->w < minw || curr->h < minh) {
            // 맨 앞 노드를 삭제하는 경우
            if (prev == nullptr) {
                head = curr->next;
                delete curr;
                curr = head;
            }

            // 그 외의 노드를 삭제하는 경우
            else {
                Node* newNode = remove_after(prev);
                delete newNode;
                curr = prev->next;
            }
        }

        // 삭제하지 않는 경우
        else {
            prev = curr;
            curr = curr->next;
        }
    }
}

int main() {
    // (1)
    read_file();    // 파일을 읽어서 파일에 저장된 순서대로 저장된 연결리스트를 구성한다.
    print_list();   // 파일에 저장된 순서대로 출력한다.

    cout << endl;   // 한 줄을 띄운다.

    // (2)
    sort_by_area(); // 연결리스트의 노드들을 면적순으로 정렬한다.
    print_list();   // 정렬된 순서대로 출력한다.

    cout << endl;   // 한 줄을 띄운다.

    // (3)
    int min_w, min_h;

    cout << "w_min = ";
    cin >> min_w;
    cout << "h_min = ";
    cin >> min_h;
    cout << endl;

    remove_rects(min_w, min_h);
    print_list();

    return 0;
}