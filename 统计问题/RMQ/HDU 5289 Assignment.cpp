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
		for (j = 1; j + (1<<i) - 1 <= ALen; j++) {
			if (i == 0) {
				f[i][j] = j;
			}
			else {
				f[i][j] = RMQ_MinIndex(A, f[i-1][j], f[i-1][j + (1 << (i - 1))]);
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


ValueType MinVal[MAXN], MaxVal[MAXN];
ValueType fMin[MAXM][MAXN], fMax[MAXM][MAXN];

int Query(int l, int r) {
	int minval =  MinVal[ RMQ_Query(MinVal, fMin, l, r) ];
	int maxval = -MaxVal[ RMQ_Query(MaxVal, fMax, l, r) ];
	return maxval - minval;
}

int main() {
	int n, m, k;
	int i;
	int t;
	scanf("%d", &t);
	 
	while( t-- ) {
		scanf( "%d", &n );
		scanf("%d", &k);
		for(i = 1; i <= n; ++i) {
			scanf("%d", &MinVal[i]);
			MinVal[i] += 1;
			MaxVal[i] = - MinVal[i];
		}
		RMQ_Init(MinVal, n, fMin);
		RMQ_Init(MaxVal, n, fMax);
		
		long long MM = 0;
		for(i = 1; i <= n; ++i) {
			int l = i, r = n;
			
			int ansr = -1;
			while(l <= r) {
				int mid = (l + r) >> 1;
				
				int val = Query(i, mid);
				if(val < k) {
					ansr = mid;
					l = mid + 1;
				}else {
					r = mid - 1;
				}
			}
			
			if(ansr != -1) {
				MM += ansr - i + 1;
			}

		} 
		
		printf("%lld\n", MM);
	} 
	
	
	return 0;
}

/*
6 1 0
1 2 3 4 5 6
*/

