// HDU 2003
// �����������ֵ���� fabs ��Ӧ��
#include <iostream>
#include <cmath>
using namespace std;

double R;

int main() {
	while (scanf("%lf", &R) != EOF) {
		printf("%.2lf\n", fabs(R));
	}
	return 0;
}