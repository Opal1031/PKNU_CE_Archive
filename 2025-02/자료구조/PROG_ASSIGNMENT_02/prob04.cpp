#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype> // isspace
#include <cassert> // assert

using namespace std;

// 구조체는 5개의 string을 멤버로 가짐
struct Person {
	string name, address;
	string phone, email, web;
};

// 저장된 사람 수를 따로 기억할 필요는 없음
vector<Person> directory;

// 한 줄을 delimiter로 나누어 벡터로 반환하는 함수
vector<string> split_line(string& line, char delimiter) {
	vector<string> tokens;
	stringstream sstream(line);
	string str;

	while (getline(sstream, str, delimiter))
		tokens.push_back(str);

	return tokens;
}

// 문자열 앞뒤 공백 제거 함수
string trim(string str) {
	int s = 0, t = str.length() - 1;

	while (s < str.length() && isspace(str[s]))
		s++;

	while (t >= 0 && isspace(str[t]))
		t--;

	if (s <= t)
		// substr(pos, len) : pos에서 시작하여 len 길이만큼의 substr 반환
		return str.substr(s, t - s + 1);

	else
		return "";
}

// 데이터 파일을 읽어 directory 벡터에 저장하는 함수
void load_data(string file_name) {
	string line;

	ifstream infile(file_name);

	while (getline(infile, line)) {
		vector<string> tokens = split_line(line, '\t');

		// assert : 조건이 false이면 exception이 생성되고 프로그램을 종료
		assert(tokens.size() >= 4 && tokens.size() <= 5);

		Person p;
		p.name = tokens.at(0);
		p.address = tokens.at(1);
		p.phone = tokens.at(2);
		p.email = tokens.at(3);
		if (tokens.size() == 5)
			p.web = tokens.at(4);

		directory.push_back(p);
	}

	infile.close();
}

// Person 구조체의 내용을 출력하는 함수
// 참조에 의한 호출 : 불필요한 객체의 복사를 피하기 위함
void print_person(Person& p) {
	cout << p.name << ":" << endl;
	cout << "		Address: " << p.address << endl;
	cout << "		Phone: " << p.phone << endl;
	cout << "		Email: " << p.email << endl;
	cout << "		Web: " << p.web << endl;
}

// directory 벡터의 모든 내용을 출력하는 함수
void list_directory() {
	for (auto& person : directory)
		print_person(person);
}

// 이름이 prefix로 시작하는 사람을 찾아 출력하는 함수
void search_directory(string& prefix) {
	int count = 0;

	for (auto& p : directory) {
		// compare(pos, len, str) : pos에서 시작하여 len 길이만큼의 substr과 str 비교 (같으면 0, 사전순으로 작으면 음수, 크면 양수 반환)
		if (p.name.compare(0, prefix.size(), prefix) == 0) {
			print_person(p);
			count++;
		}

		else if (p.name.compare(0, prefix.size(), prefix) > 0)
			break;
	}

	if (count == 0)
		cout << "No person '" << prefix << "' exists." << endl;
}

// 새로운 사람의 정보를 입력받아 Person 구조체로 반환하는 함수
Person get_person_info(string name) {
	Person p;
	string line;

	p.name = name;
	cout << "		Address: ";
	getline(cin, line);
	p.address = trim(line);
	cout << "		Phone: ";
	getline(cin, line);
	p.phone = trim(line);
	cout << "		Email: ";
	getline(cin, line);
	p.email = trim(line);
	cout << "		Web: ";
	getline(cin, line);
	p.web = trim(line);

	return p;
}

// 새로운 사람을 directory 벡터에 추가하는 함수
void add_person(string name) {
	Person p = get_person_info(name);

	auto it = directory.begin();

	// 더 큰 이름이 나오거나 벡터의 끝에 도달할 때까지 검색
	while (it != directory.end() && it->name < name)
		it++;

	// it가 가리키는 위치에 p(새로운 사람) 삽입
	it = directory.insert(it, p);
}

// 이름이 name인 사람을 directory 벡터에서 삭제하는 함수
void delete_person(string name) {
	string answer;

	// it++을 for문에서 하지 않는 이유 : erase로 인해 it가 가리키는 위치가 바뀔 수 있기 때문
	for (auto it = directory.begin(); it != directory.end();) {
		if (it->name.compare(0, name.size(), name) == 0) {
			cout << "Want to delete '" << it->name << "'? : ";
			cin >> answer;

			if (answer == "yes" || answer == "y") {
				cout << "'" << it->name << "' deleted." << endl;
				it = directory.erase(it);
			}

			else
				++it;
		}

		else if (it->name.compare(0, name.size(), name) > 0)
			break;

		else
			++it;
	}
}

// directory 벡터의 내용을 데이터 파일에 저장하는 함수
void save_directory() {
	ofstream outfile("address.tsv");

	for (auto& p : directory)
		outfile << p.name << "\t"
		<< p.address << "\t"
		<< p.phone << "\t"
		<< p.email << '\t'
		<< p.web << endl;

	outfile.close();
}

// 여러 검색어가 모두 포함된 항목을 출력하는 함수
void search_terms_in_directory(string& prefix) {
	vector<string> terms;
	stringstream ss(prefix);
	string term;

	// '&'로 검색어 분리 및 공백 제거
	while (getline(ss, term, '&')) {
		term = trim(term);

		// 공백이 아닌 경우에만 terms 벡터에 추가
		if (!term.empty())
			terms.push_back(term);
	}

	int count = 0;

	for (auto& p : directory) {
		// 모든 검색어가 하나라도 포함되어 있는지 확인
		bool flag = true;

		for (auto& t : terms) {
			// 모든 필드를 하나의 문자열로 결합
			string all_fields = p.name + " " + p.address + " " + p.phone + " " + p.email + " " + p.web;

			// 검색어가 포함되어 있지 않으면 all_found를 false로 설정하고 반복 종료
			if (all_fields.find(t) == string::npos) {
				flag = false;

				break;
			}
		}

		// 모든 검색어가 포함된 경우에만 출력
		if (flag) {
			print_person(p);
			count++;
		}
	}

	if (count == 0)
		cout << "There are no items containing all of '" << prefix << "'" << endl;
}

int main() {
	load_data("address.tsv");
	string command, arguments;

	while (1) {
		cout << "$  ";
		cin >> command;

		if (command == "exit")
			break;

		if (command == "list")
			list_directory();

		else if (command == "find") {
			getline(cin, arguments);
			string name = trim(arguments);

			if (name.length() <= 0)
				continue;

			search_directory(name);
		}

		else if (command == "add") {
			getline(cin, arguments);
			string name = trim(arguments);

			if (name.length() <= 0)
				continue;

			add_person(name);
		}

		else if (command == "delete") {
			getline(cin, arguments);
			string name = trim(arguments);

			if (name.length() <= 0)
				continue;

			delete_person(name);
		}

		else if (command == "save")
			save_directory();

		// 복수의 검색어가 모두 포함된 항목을 출력
		else if (command == "search") {
			getline(cin, arguments);

			// 공백 제거 -> 명령어 함수에서 string으로 받기 위해 trim 사용
			string prefix = trim(arguments);

			if (prefix.length() <= 0)
				continue;

			search_terms_in_directory(prefix);
		}
	}

	return 0;
}