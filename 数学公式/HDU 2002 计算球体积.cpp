// HDU 2002
// ��ѧ��ʽ
#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.1415927
double R;

int main() {
	while (scanf("%lf", &R) != EOF) {
		printf("%.3lf\n", 4 * PI*R*R*R / 3.0);
	}
	return 0;
}
