#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
	// 정수 개수
	int* num = new int;
	cin >> *num;

	// 배열, 인덱스, 합, 평균, 분산, 표준편차
	int* data = new int[num[0]];
	int* idx = new int(0);
	int* sum = new int(0);
	double* avg = new double(0);
	double* var = new double(0);
	double* stddev = new double(0);

	// 배열 및 합
	for (; *idx < *num; (*idx)++) {
		cin >> data[*idx];
		(*sum) += data[*idx];
	}

	// 배열 정렬 및 평균
	sort(data, data + *num);
	*avg = static_cast<double>(*sum) / *num;

	// 분산 및 표준편차
	*idx = 0;

	for (; *idx < *num; (*idx)++) {
		*var += (pow(static_cast<double>(data[*idx]) - (*avg), 2));
	}

	*var /= *num;
	*stddev = sqrt(*var);

	// 결과 출력
	cout << data[0] << " " << data[(*num) - 1] << " " << (*avg) << " " << (*stddev);
	
	// 동적 메모리 해제
	delete num;
	delete[] data;
	delete idx;
	delete sum;
	delete avg;
	delete var;
	delete stddev;

	return 0;
}