#include <iostream>
#include <string>

using namespace std;

class Computer {
private:
	string manufacturer;
	string processor;
	int ramSize;
	int diskSize;
	double processorSpeed;

	void dummy_method() {}

public:
	double computerPower() { return ramSize * processorSpeed; }
	double getRamsize() { return ramSize; }
	double getProcessorSpeed() { return processorSpeed; }
	int getDiskSize() { return diskSize; }

	string toString() {
		string result = "Mabufacturer : " + manufacturer +
						"\nCPU : " + processor +
						"\nRAM : " + to_string(ramSize) + " megabytes" +
						"\nDisk : " + to_string(diskSize) + " gigabytes" +
						"\nProcessor speed : " + to_string(processorSpeed) + " gigaherts";

		return result;
	}
};

class Notebook : public Computer {
private:
	double ScreenSize;
	double weight;

public:
	double getScreenSize() { return ScreenSize; }
	double getWeight() { return weight; }

	// void faulty_method() {
	// 	dummy_method();
	// 	cout << manufacturer << endl;
	// }
};

int main() {
	Notebook yourNotebook;

	// yourNotebook.manufacturer = "Dell";
	// yourNotebook.processor = "AMD";
	// yourNotebook.ramSize = 16;
	// yourNotebook.diskSize = 512;
	// yourNotebook.processorSpeed = 2.6;

	// yourNotebook.ScreenSize = 15.0;
	// yourNotebook.weight = 1.8;

	cout << yourNotebook.computerPower() << endl;
	cout << yourNotebook.getScreenSize() << endl;

	return 0;
}