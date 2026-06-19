#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 다항식의 항을 나타내는 구조체
struct Term {
	int coef;
	int expo;
	Term* next = nullptr;

	Term() {}
	Term(int c, int e) : coef(c), expo(e) {}
	Term(int c, int e, Term* p) : coef(c), expo(e), next(p) {}
};

// 다항식을 나타내는 구조체
struct Polynomial {
	char name;
	Term* first = nullptr;
	int size = 0;

	Polynomial() {}
	Polynomial(char name) : name(name) {}
};

// 다항식 poly를 벡터에 추가하는 함수
vector<Polynomial> polys;

// 다항식 poly에 새로운 하나의 항 (c, e)를 추가하는 함수
void add_term(Polynomial& poly, int c, int e) {
	// 차수가 0인 항은 추가하지 않음
	if (c == 0)
		return;

	// 두 개의 포인터 p, q를 이용하여 삽입 위치 탐색
	Term* p = poly.first, * q = nullptr;
	while (p != nullptr && p->expo > e) {
		q = p;
		p = p->next;
	}

	// 동일 차수의 항이 존재하는 경우
	if (p != nullptr && p->expo == e) {
		p->coef += c;

		// 더했더니 계수가 0이 되는 경우
		if (p->coef == 0) {
			// q의 다음 노드를 삭제
			if (q == nullptr)
				poly.first = p->next;

			else
				q->next = p->next;

			poly.size--;
			delete p;
		}

		return;
	}

	// 동일 차수의 항이 존재하지 않는 경우
	// 맨 앞에 삽입하는 경우
	if (q == nullptr)
		poly.first = new Term(c, e, poly.first);

	// q의 뒤, p의 앞에 삽입하는 경우 (p는 null일 수도 있음)
	else
		q->next = new Term(c, e, p);

	poly.size++;
}

// 벡터에서 다항식을 찾는 함수
vector<Polynomial>::iterator find_poly(char name) {
	for (auto it = polys.begin(); it != polys.end(); it++) {
		if (it->name == name)
			return it;
	}

	return polys.end();
}

// 항을 출력하는 함수
void print_term(Term* pTerm, bool isFirst) {
	int coef = pTerm->coef;
	int expo = pTerm->expo;

	// 추가 : 계수의 부호에 따라 연산자 출력
	if (coef < 0) {
		cout << (isFirst ? "-" : " - "); // 첫 항이면 -만 출력, 아니면 공백 포함 - 출력
		coef = -coef; // 음수를 양수로 변환
	}

	else if (!isFirst)
		cout << " + ";

	// 추가 : 계수가 1인 경우 생략하는 조건 (단, 상수항인 경우는 출력)
	if (coef != 1 || expo == 0)
		cout << coef;

	// 추가 : 차수가 0인 경우 x^0 생략하는 조건
	if (expo == 0)
		return;

	cout << "x";

	// 추가 : 차수가 1인 경우 x^1 생략하는 조건
	if (expo != 1)
		cout << "^" << expo;
}

// 다항식을 출력하는 함수
void print_poly(Polynomial& p) {
	cout << p.name << " = ";

	Term* t = p.first;

	// 추가 : 항이 하나도 없는 경우 0 출력
	// 수정 : 연산자 출력은 print_term에서 처리
	bool isFirst = true;

	if (t == nullptr) {
		cout << "0" << endl;
		return;
	}

	while (t != nullptr) {
		print_term(t, isFirst);
		isFirst = false;
		t = t->next;
	}

	cout << endl;
}

// 입력받은 다항식을 찾아서 출력하는 함수
void handle_print(char name) {
	auto it = find_poly(name);

	if (it == polys.end())
		cout << "No such polynomial exists." << endl;

	else
		print_poly(*it);
}

// 항의 값을 계산하는 함수
int calc_term(Term* term, int x) {
	int result = term->coef;

	for (int i = 0; i < term->expo; i++) {
		result *= x;
	}

	return result;
}

// 다항식의 값을 계산하는 함수
int calc_poly(Polynomial poly, int x) {
	int result = 0;

	Term* t = poly.first;

	while (t != nullptr) {
		result += calc_term(t, x);
		t = t->next;
	}

	return result;
}

// 입력받은 다항식의 계산값을 출력하는 함수
void handle_calc(char name, int x) {
	auto it = find_poly(name);

	if (it == polys.end())
		cout << "No such polynomial exists." << endl;

	else
		cout << calc_poly(*it, x) << endl;
}

// 다항식을 삭제하는 함수
void clear_poly(Polynomial& p) {
	Term* t = p.first, * tmp;

	while (t != nullptr) {
		tmp = t;
		t = t->next;
		delete tmp;
	}

	p.first = nullptr;
}

// 다항식을 벡터에 추가하는 함수
void insert_polynomial(Polynomial p) {
	auto it = find_poly(p.name);

	// 추가 : 다항식에 항이 없으면 0으로 간주
	if (p.first == nullptr) {
		add_term(p, 0, 0);
	}

	if (it == polys.end())
		polys.push_back(p);

	else {
		clear_poly(*it);
		*it = p;
	}
}

// 이미 존재하는 다항식에 새로운 항을 추가하는 함수
void handle_add(char name, int c, int e) {
	auto it = find_poly(name);

	if (it == polys.end()) {
		cout << "No such polynomial exists." << endl;
		return;
	}

	else
		add_term(*it, c, e);
}

// 두 다항식을 더하는 함수
void add_poly(char h, char f, char g) {
	auto poly1 = find_poly(f);
	auto poly2 = find_poly(g);

	if (poly1 == polys.end() || poly2 == polys.end()) {
		cout << "No such polynomial exists." << endl;
		return;
	}

	Polynomial result(h);

	// poly1의 모든 항을 result에 추가
	for (Term* t = poly1->first; t != nullptr; t = t->next) {
		add_term(result, t->coef, t->expo);
	}

	// poly2의 모든 항을 result에 추가
	for (Term* t = poly2->first; t != nullptr; t = t->next) {
		add_term(result, t->coef, t->expo);
	}

	insert_polynomial(result);
}

// 두 다항식을 곱하는 함수
void multiply_poly(char h, char f, char g) {
	auto poly1 = find_poly(f);
	auto poly2 = find_poly(g);

	if (poly1 == polys.end() || poly2 == polys.end()) {
		cout << "No such polynomial exists." << endl;
		return;
	}

	Polynomial result(h);

	// poly1의 각 항과 poly2의 각 항을 곱해서 result에 추가
	for (Term* term1 = poly1->first; term1 != nullptr; term1 = term1->next) {
		for (Term* term2 = poly2->first; term2 != nullptr; term2 = term2->next) {
			int coef = term1->coef * term2->coef;
			int expo = term1->expo + term2->expo;

			add_term(result, coef, expo);
		}
	}

	insert_polynomial(result);
}

int main() {
	string command, arg1, arg2, arg3;

	while (1) {
		cout << "$ ";
		cin >> command;

		if (command == "print") {
			cin >> arg1;

			handle_print(arg1[0]);
		}

		else if (command == "calc") {
			cin >> arg1 >> arg2;

			handle_calc(arg1[0], stoi(arg2));
		}

		else if (command == "define") {
			cin >> arg1;

			Polynomial pol(arg1[0]);
			insert_polynomial(pol);
		}

		else if (command == "add") {
			cin >> arg1 >> arg2 >> arg3;

			handle_add(arg1[0], stoi(arg2), stoi(arg3));
		}

		// addpoly
		else if (command == "addpoly") {
			cin >> arg1 >> arg2 >> arg3;

			add_poly(arg1[0], arg2[0], arg3[0]);
		}

		// multiplypoly
		else if (command == "multiplypoly") {
			cin >> arg1 >> arg2 >> arg3;

			multiply_poly(arg1[0], arg2[0], arg3[0]);
		}

		else if (command == "exit") {
			break;
		}
	}
}