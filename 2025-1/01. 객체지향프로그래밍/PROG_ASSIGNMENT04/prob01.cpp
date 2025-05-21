#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class OrderedVecInt {
private:
	int capacity = 0, size_ = 0; // 동적 배열의 길이 & 저장된 정수의 개수
	int* arr = nullptr; // 동적 배열의 시작 주소, 처음에는 길이가 0인 배열

	// 첫 번째 원소가 삽입될 떄 길이를 1로 만들고,
	// 그 다음부터는 필요 시 길이를 2배로 늘린다.

	// 정렬된 위치에 삽입
	void resize() {
		int new_capacity;

		if (capacity == 0)
			new_capacity = 1;
		else
			new_capacity = capacity * 2;

		int* new_arr = new int[new_capacity];

		for (int i = 0; i < size_; i++)
			new_arr[i] = arr[i];

		delete[] arr;
		arr = new_arr;
		capacity = new_capacity;
	}

public:
	// 기본 생성자를 명시적으로 기본값으로 정의한 것
	OrderedVecInt() = default;

	// 사용자 겅의 소멸자 -> 동적으로 할당된 메모리를 해제하는 역할
	~OrderedVecInt() {
		delete[] arr;
	}

	// 용량 부족 시 2배 확장
	void insert(int val) {
		// 필요시 길이를 2배로 늘림
		if (size_ == capacity)
			resize();

		// 삽입 위치 찾기(오름차순)
		int pos = 0;

		while (pos < size_ && arr[pos] < val)
			pos++;

		// 뒤에서부터 하나씩 밀기
		for (int i = size_; i > pos; --i)
			arr[i] = arr[i - 1];

		arr[pos] = val;
		size_++;
	}

	// 특정 값을 찾아 삭제
	bool remove_by_val(int val) {
		int index = -1;

		// 인덱스 찾기
		for (int i = 0; i < size_; i++) {
			if (arr[i] == val) {
				index = i;
				break;
			}
		}

		// remove failed
		if (index == -1)
			return false;

		// 한 칸씩 당기기
		for (int i = index; i < size_ - 1; i++)
			arr[i] = arr[i + 1];

		size_--;
		return true;
	}

	// 인덱스 위치 삭제
	bool remove_by_index(int idx) {
		// 인덱스 범위 확인
		if (idx < 0 || idx >= size_)
			return false;

		for (int i = idx; i < size_ - 1; i++)
			arr[i] = arr[i + 1];

		size_--;
		return true;
	}

	// 벡터처럼 접근 가능
	int& operator[](int idx) {
		return arr[idx];
	}

	// 저장된 요수 개수 반환
	int size() const {
		return size_;
	}
};

int main() {
	srand(time(0));

	int n, k;
	OrderedVecInt vec;

	cin >> n;

	// 정수 k를 삽입한다. 정수들을 정렬되어 저장되어야 한다.
	for (int i = 0; i < n; i++) {
		int k = rand() % 1000;
		vec.insert(k);
	}

	// indexing 연산자 []를 제공한다.
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << endl;

	// 매개변수로 주어진 정수를 찾아 삭제한다
	if (vec.remove_by_val(vec[2]))
		cout << "Remove done" << endl; // 그런 값이 존재하면 true
	else
		cout << "Remove failed" << endl; // 아니면 false를 반환

	if (vec.remove_by_index(4))
		cout << "RemoveIndex done" << endl;
	else
		cout << "RemoveIndex failed" << endl;

	// size()는 저장된 정수의 개수를 반환한다.
	// 저장된 정소를 수정할 수 있다. 이 경우 정렬이 흐트러질 수 있다.
	for (int i = 0; i < vec.size(); i++)
		vec[i] -= 10;

	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << endl;

	return 0;
}