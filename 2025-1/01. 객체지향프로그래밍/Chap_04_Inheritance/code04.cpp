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

public:
	Computer() = default;
	Computer(string man, string proc, int ram, int disk, double procSpeed) :
		manufacturer(man), processor(proc), ramSize(ram), diskSize(disk), processorSpeed(procSpeed) {
	}

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
	Notebook(string man, string proc, int ram, int disk, double procSpeed, double screen, double weight) :
		Computer(man, proc, ram, disk, procSpeed), ScreenSize(screen), weight(weight) {
	}


	double getScreenSize() { return ScreenSize; }
	double getWeight() { return weight; }
};

int main() {
	Computer myComputer("Acme", "Intel", 2, 160, 2.4);
	Notebook yourComputer("DellGate", "AMD", 4, 240, 1.8, 15.0, 7.5);

	cout << yourComputer.getRamsize() << endl;
	cout << yourComputer.getDiskSize() << endl;
	cout << yourComputer.getScreenSize() << endl;

	cout << endl;

	cout << "My computer is : \n"
		+ myComputer.toString() << endl;

	cout << endl;

	cout << "Your computer is : \n"
		+ yourComputer.toString() << endl;

	return 0;
}