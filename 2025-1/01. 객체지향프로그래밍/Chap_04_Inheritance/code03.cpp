#include <iostream>

using namespace std;

class Base {
	int baseMem;

public:
	Base() {
		cout << "Constructing base\n";
	}
};

class Derived : public Base {
	int derivedMem;

public:
	Derived() {
		cout << "Constructing derived\n";
	}
};

int main() {
	Derived d;

	return 0;
}