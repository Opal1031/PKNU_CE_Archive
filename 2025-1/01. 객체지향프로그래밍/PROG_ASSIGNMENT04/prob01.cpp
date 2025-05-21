#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class OrderedVecInt {
private:
	int capacity = 0, size_ = 0; // ���� �迭�� ���� & ����� ������ ����
	int* arr = nullptr; // ���� �迭�� ���� �ּ�, ó������ ���̰� 0�� �迭

	// ù ��° ���Ұ� ���Ե� �� ���̸� 1�� �����,
	// �� �������ʹ� �ʿ� �� ���̸� 2��� �ø���.

	// ���ĵ� ��ġ�� ����
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
	// �⺻ �����ڸ� ��������� �⺻������ ������ ��
	OrderedVecInt() = default;

	// ����� ���� �Ҹ��� -> �������� �Ҵ�� �޸𸮸� �����ϴ� ����
	~OrderedVecInt() {
		delete[] arr;
	}

	// �뷮 ���� �� 2�� Ȯ��
	void insert(int val) {
		// �ʿ�� ���̸� 2��� �ø�
		if (size_ == capacity)
			resize();

		// ���� ��ġ ã��(��������)
		int pos = 0;

		while (pos < size_ && arr[pos] < val)
			pos++;

		// �ڿ������� �ϳ��� �б�
		for (int i = size_; i > pos; --i)
			arr[i] = arr[i - 1];

		arr[pos] = val;
		size_++;
	}

	// Ư�� ���� ã�� ����
	bool remove_by_val(int val) {
		int index = -1;

		// �ε��� ã��
		for (int i = 0; i < size_; i++) {
			if (arr[i] == val) {
				index = i;
				break;
			}
		}

		// remove failed
		if (index == -1)
			return false;

		// �� ĭ�� ����
		for (int i = index; i < size_ - 1; i++)
			arr[i] = arr[i + 1];

		size_--;
		return true;
	}

	// �ε��� ��ġ ����
	bool remove_by_index(int idx) {
		// �ε��� ���� Ȯ��
		if (idx < 0 || idx >= size_)
			return false;

		for (int i = idx; i < size_ - 1; i++)
			arr[i] = arr[i + 1];

		size_--;
		return true;
	}

	// ����ó�� ���� ����
	int& operator[](int idx) {
		return arr[idx];
	}

	// ����� ��� ���� ��ȯ
	int size() const {
		return size_;
	}
};

int main() {
	srand(time(0));

	int n, k;
	OrderedVecInt vec;

	cin >> n;

	// ���� k�� �����Ѵ�. �������� ���ĵǾ� ����Ǿ�� �Ѵ�.
	for (int i = 0; i < n; i++) {
		int k = rand() % 1000;
		vec.insert(k);
	}

	// indexing ������ []�� �����Ѵ�.
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << endl;

	// �Ű������� �־��� ������ ã�� �����Ѵ�
	if (vec.remove_by_val(vec[2]))
		cout << "Remove done" << endl; // �׷� ���� �����ϸ� true
	else
		cout << "Remove failed" << endl; // �ƴϸ� false�� ��ȯ

	if (vec.remove_by_index(4))
		cout << "RemoveIndex done" << endl;
	else
		cout << "RemoveIndex failed" << endl;

	// size()�� ����� ������ ������ ��ȯ�Ѵ�.
	// ����� ���Ҹ� ������ �� �ִ�. �� ��� ������ ��Ʈ���� �� �ִ�.
	for (int i = 0; i < vec.size(); i++)
		vec[i] -= 10;

	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << endl;

	return 0;
}