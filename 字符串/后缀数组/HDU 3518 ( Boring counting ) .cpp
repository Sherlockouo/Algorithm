#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 4010

int bucket[MAXN];         // Ͱ��������
int wx[MAXN], wy[MAXN];   // ���������� 
int key[MAXN];
int src[MAXN];

int sa[MAXN], rank[MAXN]; // ��׺���顢�������� 
int height[MAXN];         // ǰ׺����

void debug_print(int *src, int size) {
	for (int i = 0; i < size; i++) printf("%d ", src[i]);
	puts("");
}


int da_cmp(int *x, int a, int b, int l) {
	return x[a] == x[b] && x[a + l] == x[b + l];
}

// ��������
// �������ã���y[i]������key[i]Ϊ��ֵ��������  (key, y)Ϊһ����ֵ�� 
// �������������������sa������
void calculateSA(int *key, int *sa, int *y, int n, int m) {
	int i, j, *tmp = bucket;
	// ��m��Ͱ�ÿ� 
	for (i = 0; i < m; i++) tmp[i] = 0;
	// ͳ��ÿ��Ͱ����Ҫ���õ�Ԫ�صĸ��� 
	for (i = 0; i < n; i++) tmp[key[i]] ++;
	// �����е�Ͱ������ 
	for (i = 1; i < m; i++) tmp[i] += tmp[i - 1];
	// ��¼ÿ��Ͱ�ж�Ӧ�ĺ�׺��� 
	for (i = n - 1; i >= 0; i--) sa[--tmp[key[i]]] = y[i];
}

// �����㷨

// val[i] Դ�ַ���, ��Ҫ��֤val[n-1]һ�����ֵ�����С���ַ� 
// sa[i] ��ʾ�ֵ������ڵ�i���ĺ�׺Ϊsuffix(sa[i])
// n Դ�ַ����ĳ���
// m Դ�ַ����ϵ�����ַ�+1 
void doublingAlgorithm(int *src, int *sa, int n, int m) {
	int i, j, p;
	int *x = wx, *y = wy, *t;
	memset(sa, 0, sizeof(sa));

	// 1.��һ���ַ������к�׺���л�������
	for (i = 0; i < n; i++) {
		x[i] = src[i], y[i] = i;
	}
	calculateSA(x, sa, y, n, m);

	for (j = 1, p = 1; p < n; j *= 2, m = p) {

		for (p = 0, i = n - j; i < n; i++) y[p++] = i;
		for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;


		for (i = 0; i < n; i++) key[i] = x[y[i]];
		calculateSA(key, sa, y, n, m);


		// ͨ��sa������������������з���
		// ������Ҫ�Ƚ�����������׺sa[i-1]��sa[i]�Ƿ����
		// �����ȣ�x[ sa[i] ] = x[ sa[i-1] ];
		// ����  x[ sa[i] ] Ϊ֮ǰû�г��ֹ���һ���µı�� 
		for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
			x[sa[i]] = da_cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;

	}
}

void lcprefix(int *src, int *sa, int n) {
	int i, j, k = 0;

	for (i = 0; i < n; i++) rank[sa[i]] = i;
	// h[i] >= h[i-1] - 1;
	for (i = 0; i < n; i++) {
		if (k) {
			k--;
		}
		for (j = sa[rank[i] - 1]; src[i + k] == src[j + k]; k++);
		height[rank[i]] = k;
	}
	// height[0] = 0  ������� 
	// height[1] = 0  ��Ϊ������0λ���ַ�����Զ�ǽ�β���Ǹ���С�ַ��������ֵ�����С��������׺�Ĺ���ǰ׺�ض�Ϊ�ռ� 
}

char str1[MAXN];

int ABS(int v) {
	return v < 0 ? -v : v;
}

int Min(int a, int b) {
	return a < b ? a : b;
}

int Max(int a, int b) {
	return a > b ? a : b;
}


int main() {
	//doublingAlgorithm(test, sa, 9, 3); while(1);
	int i, j, k;
	while (scanf("%s", str1) != EOF) {
		if (strcmp(str1, "#") == 0) break;
		//for(i = 0; i < 1000; i++) str1[i] = i&1?'a':'b';
		//str1[i] = 0;

		int p = 0;
		for (i = 0; str1[i]; i++) {
			src[p++] = 1 + (str1[i] - 'a');
		}
		src[p++] = 0;
		doublingAlgorithm(src, sa, p, 28);
		lcprefix(src, sa, p);
		//debug_print(height, p);
		//debug_print(sa, p);

		int c = 0;
		for (int l = 1; l < p; l++) {
			int flag = 1;
			int min = p + 1, max = -1;
			for (i = 2; i < p; i++) {
				if (height[i] >= l) {
					if (!flag) continue;

					min = Min(min, Min(sa[i], sa[i - 1]));
					max = Max(max, Max(sa[i], sa[i - 1]));
					if (max - min >= l) {
						c++;
						flag = 0;
					}
				}
				else {
					flag = 1;
					min = p + 1;
					max = -1;
				}
			}
		}

		printf("%d\n", c);

	}
	return 0;
}
/*
aaaaaaaaa
aa
*/
