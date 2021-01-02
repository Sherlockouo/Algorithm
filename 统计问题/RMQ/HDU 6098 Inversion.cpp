#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

// RMQ ������Сֵѯ��

const int MAXM = 18;
const int MAXN = (1<<MAXM)+1;

// typedef __int64 ValueType;
// typedef double ValueType;
typedef int ValueType;
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


ValueType fMax[MAXM][MAXN];
ValueType a[MAXN];


int main() {
	int t;
	int i;
	int n;
	
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d", &n);
		for(i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			a[i] = -a[i];
		}
		RMQ_Init(a, n, fMax);
		
		for(i = 2; i <= n; ++i) {
			int idx = RMQ_Query(a, fMax, 1, i-1);
			int nowl = i + 1, nowr = i + i - 1; 
			while(nowl <= n) {
				if(nowr > n) {
					nowr = n;
				}
				idx = RMQ_MinIndex(a, idx, RMQ_Query(a, fMax, nowl, nowr) );
				
				nowl += i;
				nowr += i;
				
			}
			
			int ans = - a[idx];
			if(i > 2) {
				printf(" ");
			}
			printf("%d", ans);
		} 
		
		puts("");
		
	}
	
	return 0;
} 

/*
122
9
8 5 4 3 7 2 9 10 7

*/
