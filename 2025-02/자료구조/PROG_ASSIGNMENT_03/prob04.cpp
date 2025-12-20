#include <iostream>

using namespace std;

struct Node {
	string data;

	Node* prev, * next;
};
Node* head = nullptr, * tail = nullptr;

void ordered_insert(string item);
void remove_dup();
void print_list_twice();

int main() {
	int n;
	string word;

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> word;
		ordered_insert(word);
	}

	print_list_twice();
	remove_dup();
	print_list_twice();

	return 0;
}

// head와 tail이 가리키는 이중 연결 리스트에 문자열들이 사전식 순서로 정렬된 순서를 유지하도록 새로운 문자열 item을 삽입한다.
void ordered_insert(string item) {
	// newNode : 새로 삽입할 노드
	Node* newNode = new Node{ item, nullptr, nullptr };

	// 리스트가 비어있는 경우
	if (head == nullptr) {
		head = newNode;
		tail = newNode;

		return;
	}

	// 두 개의 포인터를 이용하여 삽입 위치 탐색
	Node* prev = nullptr;
	Node* curr = head;

	while (curr != nullptr && curr->data < item) {
		prev = curr;
		curr = curr->next;
	}

	// 맨 앞에 삽입하는 경우
	if (prev == nullptr) {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}

	// 맨 뒤에 삽입하는 경우
	else if (curr == nullptr) {
		prev->next = newNode;
		newNode->prev = prev;
		tail = newNode;
	}

	// 중간에 삽입하는 경우
	else {
		prev->next = newNode;
		newNode->prev = prev;
		newNode->next = curr;
		curr->prev = newNode;
	}

	return;
}

// 이중 연결 리스트에 저장된 문자열들 중에서 모든 중복된 문자열을 찾아 하나만 남기고 제거한다.
void remove_dup() {
	Node* curr = head;

	// 현재 노드와 그 다음 노드를 비교하여 중복된 문자열 제거 (다음 노드를 제거함)
	while (curr != nullptr && curr->next != nullptr) {
		if (curr->data == curr->next->data) {
			// dupNode : 중복된 노드
			Node* dupNode = curr->next;

			curr->next = dupNode->next;

			// 다음 노드가 존재하는 경우 prev 포인터 갱신
			if (dupNode->next != nullptr)
				dupNode->next->prev = curr;

			// 다음 노드가 존재하지 않는 경우 tail 갱신
			else
				tail = curr;
		}

		// 중복이 아닌 경우 curr 포인터 이동
		else
			curr = curr->next;
	}
}

void print_list_twice() {
	Node* p = head;
	while (p != nullptr) {
		cout << p->data << " ";
		p = p->next;
	}

	cout << endl;

	Node* q = tail;
	while (q != nullptr) {
		cout << q->data << " ";
		q = q->prev;
	}

	cout << endl;
}