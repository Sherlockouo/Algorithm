// HDU 2030
// ASCII ��Ļ���Ӧ��
// ���ֵ��׸� ASCII �Ǹ���

#include <iostream>
#include <cstring>
using namespace std;

char str[1000000];

int main() {
	int t, i;
	scanf("%d", &t);
	getchar();
	while (t--) {
		gets(str);
		int cnt = 0;
		for (i = 0; str[i]; ++i) {
			if ((int)str[i] < 0) {
				++i;
				++cnt;
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}