#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAXN 1000010
int p[MAXN];
char strTmp[MAXN];

int Min(int a, int b) {
	return a < b ? a : b;
}

void ManacherPre(char *str) {
	strcpy(strTmp, str);
	int i;
	for (i = 0; strTmp[i]; ++i) {
		str[2 * i] = '$';
		str[2 * i + 1] = strTmp[i];
	}
	str[2 * i] = '$';
	str[2 * i + 1] = '\0';
}

void Manacher(char *str) {
	int ct = 0, r = 0;
	p[0] = 1;
	for (int i = 1; str[i]; ++i) {
		// 1.����p[i]��ʼֵ 
		if (i < r) {
			p[i] = Min(p[2 * ct - i], r - i);
		}
		else {
			p[i] = 1;
		}
		// 2.����p[i]������Ӧ�ﵽp[i]���ֵ 
		while (i - p[i] >= 0 && str[i - p[i]] == str[i + p[i]])
			++p[i];

		// 3.����ct
		if (p[i] + i > r) {
			ct = i;
			r = p[i] + i;
		}
	}
}

char str[MAXN];

bool solve() {
	if (strlen(str) < 3) {
		return false;
	}
	ManacherPre(str);
	Manacher(str);
	int len = strlen(str);
	int i, j;

	// ö���������Ĵ������м���Ǹ��������� 
	for (i = 3; i <= len - 4; ++i) {
		int L = 1, R = len - 2;
		for (j = p[i]; j > 1; j -= 2) {
			int lct = (i - j + 1) / 2;
			int rct = (i + j - 1 + len - 1) / 2;

			if (j != p[i]) {
				if (str[L] != str[R]) {
					break;
				}
				L += 2;
				R -= 2;
			}

			// 2.���/�ұߵĴ�Ϊ�� 
			if (1 == p[lct] || 1 == p[rct]) {
				continue;
			}

			// 3.��ߵĴ����ǻ��Ĵ�
			if (lct - p[lct] != -1) {
				continue;
			}
			// 4.�ұߵĴ����ǻ��Ĵ� 
			if (rct + p[rct] != len) {
				continue;
			}
			//printf("%d %d %d\n", i, lct, rct);
			return true;
		}
	}
	return false;
}
int main() {
	int i, t;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", str);
		printf("%s\n", solve() ? "Yes" : "No");
	}
	return 0;
}
/*
1212
cdcabacfc
*/