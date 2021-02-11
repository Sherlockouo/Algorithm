/*
	���⣺��һ����ƽ����ߵ�����֮��Ϊ�������ұߵ�����֮��Ϊ������
	���� G(G <= 20) ����������룬�ʷ����������ʹ��ƽƽ��ķ����� 
	
	��⣺��ά 0/1 ����
	
*/


#include <iostream>
#include <cstring>
using namespace std;

#define maxn 510

int a[22];
int lsum, rsum;
long long dp[maxn][maxn];

int main() {
	int C, G;
	int i, j, k;
	while (scanf("%d %d", &C, &G) != EOF) {
		lsum = rsum = 0;
		for(i = 0; i < C; ++i) {
			scanf("%d", &a[i]);
			if(a[i] < 0) {
				lsum += a[i];
			}else if(a[i] > 0) {
				rsum += a[i];
			}
		}
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		int s = 0;
		for(i = 0; i < G; ++i) {
			scanf("%d", &a[i]);
		}
		
		for(i = 0; i < G; ++i) {
			s += a[i];
			for(j = s; j >= 0; --j) {
				for(k = s - j; k >= 0; --k) {
					if( j >= a[i] ) {
						dp[j][k] += dp[j - a[i]][k];
					}
					if( k >= a[i] ) {
						dp[j][k] += dp[j][k - a[i]];
					}
				}
			}
		}
		lsum = -lsum;
		
		long long ans = 0;
		for(j = 0; j <= s; ++j) {
			for(k = 0; k <= s; ++k) {
				if(!dp[j][k]) {
					continue;
				}
				if(lsum + j == rsum + k) {
					ans += dp[j][k];
					printf("%d %d %d %d\n", j, k, dp[j][k], s);
				}
			}
		}
		printf("%lld\n", ans);
		
	} 
	
	return 0;
} 
