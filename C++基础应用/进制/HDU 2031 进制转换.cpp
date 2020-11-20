// HDU 2031
// ��������ֽ���ת����Ӧ��
// ȡģ�����������ƣ��������
// ע�⿼�� ������0 �����
#include <iostream>
#include <cstring>
using namespace std;

int val, R;
int sta[100];

void Print(int v) {
	if (v >= 10 && v <= 16) {
		printf("%c", v - 10 + 'A');
	}
	else {
		printf("%d", v);
	}
}
int main() {
	int i;
	while (scanf("%d %d", &val, &R) != EOF) {
		if (val == 0) {
			puts("0");
			continue;
		}
		else if (val < 0) {
			val = -val;
			printf("-");
		}

		sta[0] = 0;
		while (val) {
			sta[++sta[0]] = val % R;
			val /= R;
		}
		for (i = sta[0]; i > 0; --i) {
			Print(sta[i]);
		}
		puts("");
	}

	return 0;
}