// HDU 2024
// ���������:
// 1. ���ֿո�(��tab)�Ƿ�
// 2. ���ַ�����������
// 3. �м䲻�ܳ��ֿո�
// 4. �ַ�����ֻ�� ���֡�_����д��ĸ��Сд��ĸ
#include <iostream>
using namespace std;

#define __UNDEFINE 100000
char str[100];

bool isnum(char c) {
	return c >= '0' && c <= '9';
}

bool is_space_or_tab(char c) {
	return c == ' ' || c == '\t';
}

bool judge_char(char c) {
	if (isnum(c)) return true;
	if (c >= 'a' && c <= 'z') return true;
	if (c >= 'A' && c <= 'Z') return true;
	if (c == '_') return true;
	return false;
}

bool judge(const char* str) {
	int i;
	int s, t;
	s = __UNDEFINE;
	t = 0;
	for (i = 0; str[i]; ++i) {
		if (!is_space_or_tab(str[i])) {
			if (s == __UNDEFINE) {
				s = i;
			}
			t = i;
		}
		else {
			return false;
		}
	}
	// ȫ�ǿո�
	if (s > t) {
		return false;
	}
	// ���ַ�����������
	if (isnum(str[s])) {
		return false;
	}
	for (i = s; i <= t; ++i) {
		// �м䲻�ܳ��ֿո�
		if (is_space_or_tab(str[i])) {
			return false;
		}
		if (!judge_char(str[i])) {
			return false;
		}
	}
	return true;
}

int main() {
	int t;
	scanf("%d", &t);
	getchar();
	while (t--) {
		gets(str);
		printf("%s\n", judge(str) ? "yes" : "no");
	}
	return 0;
}