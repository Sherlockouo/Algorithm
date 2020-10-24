// HDU 2026
// ASCII ��Ļ���Ӧ��
// ��Сд��ĸת��
#include <iostream>
using namespace std;

char str[200];

bool isspace(char c) {
	return c == ' ' || c == '\t';
}

int main() {
	int i;
	while (gets(str)) {
		bool space = true;
		for (i = 0; str[i]; ++i) {
			if (!isspace(str[i])) {
				if (space) {
					space = false;
					if (str[i] >= 'a' && str[i] <= 'z') {
						str[i] = str[i] - 'a' + 'A';
					}
				}
			}
			else {
				space = true;
			}
		}
		puts(str);
	}
}