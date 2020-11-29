// HDU 2047
// �򵥶�̬�滮������
// dp[i][j] ��ʾ����Ϊi�����һ���ַ�Ϊj�ķ�����
// 0 - 'E'    1 - 'O'   2 - 'F'
// dp[i][0] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2];
// dp[i][1] = dp[i-1][0] + dp[i-1][2];
// dp[i][2] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2];

#include <iostream>
using namespace std;

__int64 dp[100][100];
int n;

int main() {
	int i, j;
	dp[1][0] = dp[1][1] = dp[1][2] = 1;
	for (i = 2; i <= 40; ++i) {
		for (j = 0; j < 3; ++j) {
			dp[i][j] = dp[i - 1][0] + dp[i - 1][2];
			if (j != 1)
				dp[i][j] += dp[i - 1][1];
		}
	}
	while (scanf("%d", &n) != EOF) {
		printf("%I64u\n", dp[n][0] + dp[n][1] + dp[n][2]);
	}
	return 0;
}