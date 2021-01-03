#include <iostream>
#include <cstring>
#include <cstdlib>
#include <map>

using namespace std;

// RMQ ������Сֵѯ��

const int MAXM = 18;
const int MAXN = (1<<MAXM)+1;

typedef long long ValueType;
// typedef double ValueType;
// typedef int ValueType;
int lg2K[MAXN];

int RMQ_MinIndex(ValueType A[], int l, int r) {
    return A[r] < A[l] ? r : l;
}

// f[i][j] = opt(f[i-1][j], f[i-1][j + 2^{i-1}]);
void RMQ_Init(ValueType A[], int ALen, int(*f)[MAXN]) {
	int i, j, k = 0;
	for (i = 1; i <= ALen; i++) {
		lg2K[i] = k - 1;
		if ((1 << k) == i) k++;
	}
	for (i = 0; i < MAXM; i++) {
		for (j = 1; j <= ALen; j++) {
			if (i == 0) {
				f[i][j] = j;
			}
			else {
				f[i][j] = f[i-1][j];
				int ridx = j + (1 << (i - 1));
				if (ridx <= ALen) {
					f[i][j] = RMQ_MinIndex(A, f[i-1][j], f[i-1][ridx]);
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
int RMQ_Query(ValueType A[], int(*f)[MAXN], int a, int b) {
	if (a == b) {
		return a;
	}
	else if (a > b) {
		a = a^b, b = a^b, a = a^b;
	}
	int k = lg2K[b - a + 1];
	return RMQ_MinIndex(A, f[k][a], f[k][b - (1 << k) + 1]);
}


ValueType MaxVal[MAXN];
int fMax[MAXM][MAXN];

int a[MAXN], pre[MAXN], dp[MAXN], idp[MAXN];
const int HASH = 1000000;
int tmphash[HASH*2 + 10];

int Min(int l, int r) {
	return l < r ? l : r;
}

void init(int n) {
	memset(tmphash, 0, sizeof(tmphash));
	for(int i = 1; i <= n; ++i) {
		pre[i] = tmphash[ a[i] ];
		tmphash[ a[i] ] = i;
 	}
 	
 	dp[0] = 0;
 	for(int i = 1; i<= n; ++i) {
 		dp[i] = Min(dp[i-1] + 1, i - pre[i]);
 		MaxVal[i] = - dp[i];
 		idp[i] = i - dp[i] + 1;
	}
}

int MinIndex(int target, int l, int r) {
	int ans = r + 1;
	while(l <= r) {
		int m = (l + r) >> 1;
		if(idp[m] >= target) {
			ans = m;
			r = m - 1;
		}else {
			l = m + 1;
		}
	}
	return ans;
}

int main() {
	int n, m;
	int i;
	
	while(scanf("%d %d", &n, &m) != EOF) {
		for(i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			a[i] += HASH;
		}
		init(n);
		// for(i = 1; i<= n; ++i) printf("%d ", pre[i]);
		// for(i = 1; i<= n; ++i) printf("%d ", idp[i]);
		
		RMQ_Init(MaxVal, n, fMax);
		
		while(m--) {
			int l, r;
			scanf("%d %d", &l, &r);
			++l;
			++r;
			
			int mi = MinIndex(l, l, r);
			//printf("mi = %d\n", mi);
			
			int ans = mi - l;
			if(mi <= r) {
				int dpval = - MaxVal[ RMQ_Query(MaxVal, fMax, mi, r) ];
				
				if(dpval > ans) ans = dpval;
			}
			printf("%d\n", ans);
		}
	}
	
	return 0;
} 

/*
9 2
2 5 4 1 2 3 6 2 4
0 8
2 6
*/




