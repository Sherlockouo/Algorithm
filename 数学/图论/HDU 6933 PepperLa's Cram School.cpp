/*
���⣺N���㣬����������ȣ����Ǳ�һ��ʼ���ǲ�ͨ�ģ�ֻ�б���ͨ����ͨ�У�
������������̾����������������Ҫ�ö���������ͨ��

ͼ�ۣ���Ϊ���������������ȣ����Ը�������̾���ͼ��Ȼ����GCD >= 1�ģ�
����֮�������ľ�������С�������㣬����֮��ı߱�ȻҪ��ͨ��
Ȼ��ֻҪͳ����С�ı߼��ɣ���Ϊ��˫��ͼ���������� / 2��

*/

#include <iostream>

using namespace std;

#define MAXN 1010

int n;
int Map[MAXN][MAXN];

int main() {
	int i, j;
	int cnt;
	while (scanf("%d", &n) != EOF) {
		int Min = 10000000, cnt = 0;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				scanf("%d", &Map[i][j]);
				if (i == j) continue;
				if (Map[i][j] < Min) {
					Min = Map[i][j];
					cnt = 1;
				}
				else if (Map[i][j] == Min) {
					++cnt;
				}
			}
		}
		printf("%d\n", cnt / 2);
	}

	return 0;
}

/*
5
0 1 2 1 1
1 0 3 2 2
2 3 0 1 2
1 2 1 0 1
1 2 2 1 0
*/