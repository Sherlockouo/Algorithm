#include <iostream>

using namespace std;

#define LL long long

int Pow10[100];

void init() {
	Pow10[0] = 1;
	for (int i = 1; i < 10; ++i) {
		Pow10[i] = Pow10[i - 1] * 10;
	}
}

int f[20000];

int getCycle(int K) {
	f[1] = f[2] = 1;
	int pre = 0;
	for (int i = 3; i < 20000; ++i) {
		f[i] = (f[i - 1] + f[i - 2]) % Pow10[K + 1];
		if (f[i] && f[i] % Pow10[K] == 0) {
			printf("%d, ", i - pre);
			pre = i;
		}
	}
	puts("");
	return 1;
}

/*
���Ĵ���ҹ���

K = 1����  15 Ϊ�ף�    Ȼ����� 15,15,15,15,15,15,15,15,30 ѭ��
K = 2, ��  150 Ϊ�ף�   Ȼ����� 150,150,150,300 ѭ��
K = 3����  750 Ϊ�ף�   Ȼ����� 750,750,750,750,750,750,750,750,1500 ѭ��
K = 4����  7500 Ϊ�ף�  Ȼ����� 7500, 7500, 7500, 7500, 7500, 7500, 7500, 7500, 15000 ѭ��
K = 5����  75000 Ϊ�ף� Ȼ����� 75000, 75000, 75000, 75000, 75000, 75000, 75000, 75000, 150000 ѭ��
K = 6����  750000 Ϊ�ף�Ȼ����� 750000, 750000, 750000, 750000, 750000, 750000, 750000, 750000, 1500000 ѭ��
*/

LL data[100][10] = {
	{},
	{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 30 },
	{ 150, 150, 150, 150, 300 },
	{ 750, 750, 750, 750, 750, 750, 750, 750, 750, 1500 },
	// ...
};

int getCycleLen(int K) {
	if (K == 2) {
		return 4;
	}
	else {
		return 9;
	}
}

LL getCycleSum(int K) {
	LL s = 0;
	int l = getCycleLen(K);
	for (int i = 1; i <= l; ++i) {
		s += data[K][i];
	}
	return s;
}

int main() {
	init();
	int t;
	int K, M;

	for (int i = 4; i < 20; ++i) {
		for (int j = 0; j < 10; ++j) {
			data[i][j] = data[i - 1][j] * (LL)10;
		}
	}

	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &K, &M);
		LL ans = data[K][0];
		M -= 1;
		ans += M / getCycleLen(K) * getCycleSum(K);
		int v = M % getCycleLen(K);
		for (int i = 1; i <= v; ++i) ans += data[K][i];
		printf("%I64d\n", ans);
	}

	return 0;
}