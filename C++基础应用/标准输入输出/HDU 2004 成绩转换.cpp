// HDU 2004
// C���Ի�������Ӧ��
// ���߼��жϺͱ�׼�������
#include <iostream>
#include <cmath>
using namespace std;

int v;

int main() {
	while (scanf("%d", &v) != EOF) {
		if (v < 0 || v>100) {
			printf("Score is error!\n");
		}
		else {
			if (v >= 0 && v <= 59) {
				printf("E\n");
			}
			else if (v == 100) {
				printf("A\n");
			}
			else{
				char c = 'D' - (v - 60) / 10;
				printf("%c\n", c);
			}
		}
	}
	return 0;
}
