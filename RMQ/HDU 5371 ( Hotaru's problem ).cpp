
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MAXN 200010
int p[MAXN];
int intTmp[MAXN];

int Min(int a, int b) {
	return a < b ? a : b;
}

// RMQ ������Сֵѯ��
#define MAXM 19

// typedef __int64 ValueType;
// typedef double ValueType;
typedef int ValueType;
int lg2K[MAXN];

// n val[]    ��ʾԪ����Ĵ�С��Ԫ��ֵ   -in 
// ret[i][j]  ��ʾ��õ�RMQ����          -out  
void RMQ_Init(int n, ValueType val[], int(*ret)[MAXN]) {
	int i, j, k = 0;
	for (i = 1; i <= n; i++) {
		lg2K[i] = k - 1;
		if ((1 << k) == i) k++;
	}
	for (i = 0; i < MAXM; i++) {
		for (j = 1; j <= n; j++) {
			if (i == 0) {
				ret[i][j] = j;
			}
			else {
				// ret[i][j] = getMinIdx( ret[i-1][j], ret[i-1][ j+(1<<i-1) ] );
				ret[i][j] = ret[i - 1][j];
				int ridx = j + (1 << i - 1);
				if (ridx <= n) {
					int r = ret[i - 1][ridx];
					if (val[r] < val[ret[i][j]]) {
						ret[i][j] = r;
					}
				}
			}
		}
	}
}

/*
�����䳤��Ϊ2^k����X��ʾ������Ϊ[a, a + 2^k)��Y��ʾ������Ϊ(b - 2^k, b]��
����Ҫ����һ����������X���Ҷ˵������ڵ���Y����˵�-1���� a+2^k-1 >= b-2^k��
��2^(k+1) >= (b-a+1), ����ȡ��������2Ϊ�ף����� k+1 >= lg(b-a+1)����k >= lg(b-a+1) - 1��
kֻҪ��Ҫȡ��С��������������������( lg(x)������2Ϊ��x�Ķ��� )��
*/
int RMQ_Query(ValueType val[], int(*rmq)[MAXN], int a, int b) {
	if (a == b) {
		return a;
	}
	else if (a > b) {
		a = a^b, b = a^b, a = a^b;
	}
	int k = lg2K[b - a + 1];
	return val[rmq[k][a]] < val[rmq[k][b - (1 << k) + 1]] ? rmq[k][a] : rmq[k][b - (1 << k) + 1];
}

void ManacherPre(int n, int *str) {
	int i;
	for (i = 0; i < n; ++i) {
		intTmp[i] = str[i];
	}
	for (i = 0; i < n; ++i) {
		str[2 * i] = -1;
		str[2 * i + 1] = intTmp[i];
	}
	str[2 * i] = -1;
}

int Manacher(int n, int *str) {
	int ct = 0, r = 0, maxLen = 1;
	p[0] = 1;
	for (int i = 1; i < n; ++i) {
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
	return maxLen;
}

int a[MAXN];
int val[MAXN];
int ret[MAXM][MAXN];

char str[2000002];

int main() {
	int i, j;
	int t, cases = 0;
	int n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		int N = n;
		n = 0;
		getchar();
		gets(str);
		int s = -1;
		for (i = 0; str[i]; ++i) {
			if (str[i] >= '0' && str[i] <= '9') {
				if (s == -1) s = 0;
				s = s * 10 + str[i] - '0';
			}
			else {
				if (s != -1) {
					a[n++] = s;
					s = -1;
				}
			}
		}
		if (s != -1) {
			a[n++] = s;
			s = -1;
		}

		ManacherPre(n, a);
		n = 2 * n + 1;
		Manacher(n, a);

		for (i = 1; i < n - 1; ++i) {
			if (i & 1) {
				val[i] = 10000000;
			}
			else {
				val[i] = i - p[i] + 1;
			}
		}
		RMQ_Init(n - 2, val, ret);
		int Max = 0;

		for (i = 2; i < n - 1; i += 2) {
			if (Max * 3 <= N && Max * 3 + 3 > N) break;
			int l = i;
			int r = l + p[l] - 1;
			int nowMax = p[l] / 2;

			// 1����ǰ���Ž��֦
			if (nowMax <= Max) {
				continue;
			}
			// 2��������н�
			if (r - p[r] + 1 <= l) {
				Max = nowMax;
				continue;
			}
			for (j = r - 2; j > i; j -= 2) {

				int idx = RMQ_Query(val, ret, i + 2, j);
				if (val[idx] > i) {
					break;
				}
				int nowMax = (j - l) / 2;
				//printf("%d(%d, %d) ", i, nowMax, Max);
				if (nowMax <= Max) {
					break;
				}
				if (j - p[j] + 1 <= l) {
					Max = nowMax;
					break;
				}
			}
			//puts("");
		}
		printf("Case #%d: %d\n", ++cases, Max * 3);
	}
	return 0;
}

/*

*/