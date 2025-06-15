#include <iostream>

using namespace std;

class Computer {
private:
	string manufacturer;
	string processor;
	int ramSize;
	int diskSize;
	double processorSpeed;

public:
	Computer(string man, string proc, int ram, int disk, double procSpeed);
	virtual ~Computer();

	double computePower();
	double getRamSize();
	double getProcessorSpeed();
	int getDiskSize();
	virtual string toString();
};

class Notebook : public Computer {
private:
	double screenSize;
	double weight;

public:
	Notebook(string man, string proc, int ram, int disk, double procSpeed, double screen, double weight);
	~Notebook() {}

	string toString();
	double getScreenSize();
	double getWeight();
};