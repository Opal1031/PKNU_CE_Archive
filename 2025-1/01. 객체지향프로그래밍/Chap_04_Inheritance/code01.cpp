#include <iostream>

using namespace std;

class Computer {
public:
	string manufacturer;
	string processor;
	int ramSize;
	int diskSize;
	double processorSpeed;

	double computerPower() { return ramSize * processorSpeed; }
	double getRamsize() { return ramSize; }
	double getProcessorSpeed() { return processorSpeed; }
	int getDiskSize() { return diskSize; }
};

class Notebook : public Computer {
public:
	double ScreenSize;
	double weight;

	double getScreenSize() { return ScreenSize; }
	double getWeight() { return weight; }
};

int main() {
	Notebook yourNotebook;

	yourNotebook.manufacturer = "Dell";
	yourNotebook.processor = "AMD";
	yourNotebook.ramSize = 16;
	yourNotebook.diskSize = 512;
	yourNotebook.processorSpeed = 2.6;

	yourNotebook.ScreenSize = 15.0;
	yourNotebook.weight = 1.8;

	cout << yourNotebook.computerPower() << endl;
	cout << yourNotebook.getScreenSize() << endl;

	return 0;
}