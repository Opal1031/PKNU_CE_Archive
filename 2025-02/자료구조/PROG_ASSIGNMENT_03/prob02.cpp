#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Node {
	string word;
	int count = 0;

	Node* next;
};
Node* head = nullptr;

void read_file();				// 파일에서 단어 읽어와서 연결 리스트에 추가하는 함수
void print_list();				// 연결 리스트 출력 함수

void add_first(string item);	// 맨 앞에 새로운 노드 삽입하는 함수
Node* remove_after(Node* prev);	// 어떤 노드 뒤의 노드 삭제하는 함수

void count_up(string word);		// 단어가 이미 연결 리스트에 있으면 count 증가, 없으면 새 노드 추가
void remove_word();				// count가 10 이하인 단어를 가진 노드 삭제하는 함수
void ordered_list_by_dict();	// 단어를 사전 순으로 정렬하는 함수 (오름차순)
void ordered_list_by_count();	// 단어 빈도 수에 따라 정렬하는 함수 (내림차순)

int main() {
	read_file();
	ordered_list_by_dict();
	print_list();

	cout << "\n============================================================\n" << endl;

	remove_word();
	print_list();

	cout << "\n============================================================\n" << endl;

	ordered_list_by_count();
	print_list();

	return 0;
}

// 파일에서 단어 읽어와서 연결 리스트에 추가하는 함수
void read_file() {
	ifstream file("harry.txt");

	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string token;

		while (ss >> token)
			count_up(token);
	}
}

// 연결 리스트 출력 함수
void print_list() {
	Node* p = head;
	int node_count = 0;

	while (p != nullptr) {
		cout << p->word << ": " << p->count << endl;
		node_count++;
		p = p->next;
	}

	cout << "\nTotal words: " << node_count << endl;
}

// 맨 앞에 새로운 노드 삽입하는 함수
void add_first(string item) {
	Node* tmp = new Node;

	tmp->word = item;
	tmp->count = 1;
	tmp->next = head;

	head = tmp;
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

// 단어가 이미 연결 리스트에 있으면 count 증가, 없으면 새 노드 추가
void count_up(string word) {
	Node* p = head;

	while (p != nullptr) {
		// 단어가 이미 있는 경우 count 증가
		if (p->word == word) {
			p->count++;

			return;
		}

		// 단어가 없는 경우 다음 노드로 이동
		p = p->next;
	}

	// 단어가 없는 경우 새로운 노드 추가
	add_first(word);
}

// count가 10 이하인 단어를 가진 노드 삭제하는 함수
void remove_word() {
	Node* curr = head;
	Node* prev = nullptr;

	while (curr != nullptr) {
		if (curr->count <= 10) {
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

// 단어를 사전 순으로 정렬하는 함수 (오름차순)
void ordered_list_by_dict() {
	if (head == nullptr || head->next == nullptr)
		return;

	Node* sorted = nullptr;
	Node* tail = nullptr;

	while (head != nullptr) {
		// 최소 단어를 가진 노드 찾기
		Node* minPrev = nullptr;
		Node* minNode = head;

		Node* prev = head;
		Node* curr = head->next;

		while (curr != nullptr) {
			if (curr->word < minNode->word) {
				minPrev = prev;
				minNode = curr;
			}

			prev = curr;
			curr = curr->next;
		}

		// minNode를 원래 연결 리스트에서 분리
		if (minPrev == nullptr)
			head = minNode->next;

		else
			minPrev->next = minNode->next;

		minNode->next = nullptr;

		// sorted 연결 리스트의 맨 뒤에 추가
		if (sorted == nullptr) {
			sorted = minNode;
			tail = minNode;
		}

		else {
			tail->next = minNode;
			tail = minNode;
		}
	}

	// head를 정렬된 연결 리스트로 변경
	head = sorted;
}

// 단어 빈도 수에 따라 정렬하는 함수 (내림차순)
void ordered_list_by_count() {
	if (head == nullptr || head->next == nullptr)
		return;

	Node* sorted = nullptr;
	Node* tail = nullptr;

	while (head != nullptr) {
		// 최대 count를 가진 노드 찾기
		Node* maxPrev = nullptr;
		Node* maxNode = head;

		Node* prev = head;
		Node* curr = head->next;

		while (curr != nullptr) {
			if (curr->count > maxNode->count) {
				maxPrev = prev;
				maxNode = curr;
			}

			prev = curr;
			curr = curr->next;
		}

		// maxNode를 원래 연결 리스트에서 분리
		if (maxPrev == nullptr)
			head = maxNode->next;

		else
			maxPrev->next = maxNode->next;

		maxNode->next = nullptr;

		// sorted 연결 리스트의 맨 뒤에 추가
		if (sorted == nullptr) {
			sorted = maxNode;
			tail = maxNode;
		}

		else {
			tail->next = maxNode;
			tail = maxNode;
		}
	}

	// head를 정렬된 연결 리스트로 변경
	head = sorted;
}