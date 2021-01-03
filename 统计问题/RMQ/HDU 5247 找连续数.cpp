#include <iostream>
#include <cstring>
#include <cstdlib>
#include <map>

using namespace std;

// RMQ ������Сֵѯ��

const int MAXM = 14;
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




ValueType MinVal[MAXN], MaxVal[MAXN];
int fMin[MAXM][MAXN], fMax[MAXM][MAXN];

ValueType QueryMaxMinDiff(int l, int r) {
	ValueType minval =  MinVal[ RMQ_Query(MinVal, fMin, l, r) ];
	ValueType maxval = -MaxVal[ RMQ_Query(MaxVal, fMax, l, r) ];
	return maxval - minval;
}

map<ValueType, int> mapCnt;

int hashkey[MAXN], hashcase;
ValueType hashvalue[MAXN];
int hashcnt[MAXN];

int HASH(ValueType v) {
	int s = (v & (MAXN-2));
	while(1) {
		if(hashkey[s] < hashcase) {
			hashkey[s] = hashcase;
			hashvalue[s] = v;
			return s;
		}else {
			if(hashvalue[s] == v) {
				return s;
			}
			s = ( (s + 1) & (MAXN-2) );
		}
	} 
}

int main() {
	int n, m;
	int i;
	int cas = 0;
	hashcase = 0;

	while(scanf( "%d %d", &n, &m ) != EOF) {
		for(i = 1; i <= n; ++i) {
			scanf("%lld", &MinVal[i]);
			MaxVal[i] = - MinVal[i];
		}
		RMQ_Init(MinVal, n, fMin);
		RMQ_Init(MaxVal, n, fMax);
		
		
		
		printf("Case #%d:\n", ++cas);

		while(m--) {
			int k, ans = 0;
			mapCnt.clear();
			int totalCnt = 0;
			scanf("%d", &k);
	
			if(k > n) {
				printf("0\n");
				continue;
			}
			++hashcase;
			memset(hashcnt, 0, sizeof(hashcnt));
			 
			for(i = 1; i <= n; ++i) {
				int nowvalue = HASH( MinVal[i] );
				
				if(1 == ++hashcnt[ nowvalue ]) {
					++totalCnt;
				}
				
				if(totalCnt == k) {
					if( QueryMaxMinDiff(i-k+1, i) == k-1 ) {
						++ans; 
					}	
				}
				
				if(i >= k) {
					int prevalue = HASH( MinVal[i - k + 1] );
					if( 0 == --hashcnt[ prevalue ] ) {
						--totalCnt;
					}					
				}

			}
			printf("%d\n", ans);
			
		}
	}
	return 0;
}


