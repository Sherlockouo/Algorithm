#include <iostream>

using namespace std;

#define MAXN 100010
#define MOD 9997

int ans[MAXN];
int dp[MAXN][4];

int main() {
	int i, j;
	ans[0] = 1;
	ans[1] = 2;
	ans[2] = 4;
	ans[3] = 7;
	dp[3][0] = 2, dp[3][1] = 2, dp[3][2] = 2, dp[3][3] = 1;
	for (i = 4; i < MAXN; ++i) {
		dp[i][0] = dp[i - 1][0] + dp[i - 1][1];     // (��׺��"10"��"00"��β�Ĵ�����һ���ַ�"0"��ɺ�׺Ϊ"00"��β��)
		dp[i][1] = dp[i - 1][2] + dp[i - 1][3];     // (��׺��"11"��"001"��β�Ĵ�����һ���ַ�"0"��ɺ�׺Ϊ"10"��β��)
		dp[i][2] = dp[i - 1][2] + dp[i - 1][3];     // (��׺��"11"��"001"��β�Ĵ�����һ���ַ�"1"��ɺ�׺Ϊ"11"��β��)
		dp[i][3] = dp[i - 1][0];                  // (��׺��"00"��β�Ĵ�����һ���ַ�"1"��ɺ�׺Ϊ"001"��β��)
		for (j = 0; j < 4; ++j) {
			dp[i][j] %= MOD;
			ans[i] += dp[i][j];
			ans[i] %= MOD;
		}
	}
	int n;
	while (scanf("%d", &n) != EOF && n >= 0) {
		printf("%d\n", ans[n]);
	}
	return 0;
}