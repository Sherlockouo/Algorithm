// HDU 2059
// �򵥶�̬�滮
// dp[i] ��ʾ ��ֹ����i�����վ�������յ㣩�ڹ껨�ѵ�����ʱ�䣻
// ����ÿ�ν��г����ڹ�Ŀ���ʻ�����֮ǰʣ�����ʻ�����޹أ�����ÿ�����վ��һ���µ�״̬��ʼ��
// ��ÿ�����վΪС״̬����״̬ת�Ƽ���

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define LL __int64

LL N, C, T;
LL L;
LL Vr, Vt1, Vt2;
LL p[200];
double dp[200];

int main() {
	int t;
	int i, j;
	while (scanf("%I64d", &L) != EOF) {
		dp[0] = 0;
		scanf("%I64d %I64d %I64d", &N, &C, &T);
		scanf("%I64d %I64d %I64d", &Vr, &Vt1, &Vt2);
		for (i = 1; i <= N; ++i) {
			scanf("%I64d", &p[i]);
		}
		p[N + 1] = L;

		for (i = 1; i <= N + 1; ++i) {
			dp[i] = -1;
			for (j = 0; j < i; ++j) {
				double t;
				if (p[i] - p[j] <= C) {
					t = (p[i] - p[j]) * 1.0 / Vt1 + (j ? T : 0);
				}
				else {
					t = C * 1.0 / Vt1 + (j ? T : 0) + (p[i] - p[j] - C) * 1.0 / Vt2;
				}

				if (dp[i] < 0 || dp[j] + t < dp[i]) {
					dp[i] = dp[j] + t;
				}
			}
			//printf("%lf\n", dp[i]);
		}

		if (dp[N + 1] * Vr <= L) {
			printf("What a pity rabbit!\n");
		}
		else {
			printf("Good job,rabbit!\n");
		}
	}


	return 0;
}