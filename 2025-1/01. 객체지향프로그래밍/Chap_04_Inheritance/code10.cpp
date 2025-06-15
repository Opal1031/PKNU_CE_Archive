#include <iostream>

using namespace std;

class Base {
public:
	Base() { cout << "Constructing base\n"; }
	virtual ~Base() { cout << "Destructiong base\n"; }
};

class Derived : public Base {
public:
	Derived() { cout << "Constructing derived\n"; }
	~Derived() { cout << "Destructing derived\n"; }
};

int main() {
	Derived* d = new Derived;
	Base* b = d;

	delete b;

	return 0;
}