#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
	// ���� ����
	int* num = new int;
	cin >> *num;

	// �迭, �ε���, ��, ���, �л�, ǥ������
	int* data = new int[num[0]];
	int* idx = new int(0);
	int* sum = new int(0);
	double* avg = new double(0);
	double* var = new double(0);
	double* stddev = new double(0);

	// �迭 �� ��
	for (; *idx < *num; (*idx)++) {
		cin >> data[*idx];
		(*sum) += data[*idx];
	}

	// �迭 ���� �� ���
	sort(data, data + *num);
	*avg = static_cast<double>(*sum) / *num;

	// �л� �� ǥ������
	*idx = 0;

	for (; *idx < *num; (*idx)++) {
		*var += (pow(static_cast<double>(data[*idx]) - (*avg), 2));
	}

	*var /= *num;
	*stddev = sqrt(*var);

	// ��� ���
	cout << data[0] << " " << data[(*num) - 1] << " " << (*avg) << " " << (*stddev);
	
	// ���� �޸� ����
	delete num;
	delete[] data;
	delete idx;
	delete sum;
	delete avg;
	delete var;
	delete stddev;

	return 0;
}