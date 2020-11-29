#include <iostream>

using namespace std;

#define MAXN 55
#define LL __int64
// ���� �������� ���ɵĴ�����
// (446744082487542857LL) 
#define MOD    (446744082487542857LL)
#define DELTA  (100000000000000000LL)

/*
��˹��Ԫ - ͬ�෽��
һ��ֻҪ����һ����/���ұ�Ȼ�н�
1���ⲻ����ĳ���������
2��������и�������ҪԤ�ȼ���ƫ����
*/

// ����(a + b) % n
LL AddMod(LL a, LL b, LL mod) {
	// ��֤�������� a, b�� (-MOD, MOD)��Χ��
	a += b;
	if (a >= mod) a -= mod;
	while (a < 0) {
		a += mod;
	}
	return a;
}

//���� (a * b) % mod
LL ProductMod(LL a, LL b, LL mod) {
	if (!a || !b || mod == 1) {
		return 0;
	}
	LL sum = 0;
	bool negtive = (b < 0);
	if (b < 0) b = -b;
	while (b) {
		if (b & 1) {
			sum = AddMod(sum, a, mod);
		}
		a = AddMod(a, a, mod);
		b >>= (LL)1;
	}
	sum = (sum * (negtive ? -1 : 1) + mod);
	if (sum >= mod) sum -= mod;
	return sum;
}

LL GCD(LL a, LL b) {
	if (!b) {
		return a;
	}
	return GCD(b, a%b);
}

LL ExpGcd(LL a, LL b, LL &X, LL &Y) {
	LL q, temp;
	if (!b) {
		q = a; X = 1; Y = 0;
		return q;
	}
	else {
		q = ExpGcd(b, a % b, X, Y);
		temp = X;
		X = Y;
		Y = temp - (a / b) * Y;
		return q;
	}
}



class GaussMatrix {
public:
	int r, c;
	LL d[MAXN][MAXN];
	LL x[MAXN];       // ĳ���⼯ 
	LL  xcnt;          // �⼯���� 

	LL ABS(LL v) {
		return v < 0 ? -v : v;
	}

	void swap_row(int ra, int rb) {
		for (int i = 0; i <= c; i++) {
			LL tmp = d[ra][i];
			d[ra][i] = d[rb][i];
			d[rb][i] = tmp;
		}
	}
	void swap_col(int ca, int cb) {
		for (int i = 0; i < r; i++) {
			LL tmp = d[i][ca];
			d[i][ca] = d[i][cb];
			d[i][cb] = tmp;
		}
	}

	void getAns(LL mod) {
		for (int i = c - 1; i >= 0; i--) {
			LL tmp = d[i][c];
			// d[i][i] * x[i] + (d[i][i+1]*x[i+1] + ... + d[i][c]*x[c]) = K*mod + tmp;
			for (int j = i + 1; j < c; j++) {
				tmp -= ProductMod(d[i][j], x[j], mod);
				tmp = (tmp % mod + mod) % mod;
			}
			// d[i][i] * x[i] = K * mod + tmp;
			// d[i][i] * x[i] + (-K) * mod = tmp;
			// a * x[i] + b * (-K) = tmp;
			LL X, Y;
			ExpGcd(d[i][i], mod, X, Y);
			x[i] = ProductMod(X % mod, tmp, mod);
		}
	}

	// -1 ��ʾ�޽� 
	LL gauss(LL mod) {
		int i, j, k;
		int col, maxrow;

		// ö���У������� 
		for (i = 0, col = 0; i < r && col < c; i++) {
			//debug_print();
			maxrow = i;
			// �ҵ�i��r-1����colԪ�������Ǹ�ֵ 
			for (j = i + 1; j < r; j++) {
				if (ABS(d[j][col]) > ABS(d[maxrow][col])){
					maxrow = j;
				}
			}
			// �����к͵�i�н��� 
			if (maxrow != i) {
				swap_row(i, maxrow);
			}
			if (d[i][col] == 0) {
				// ������һ�еĵ�ǰcolֵ ����0����������һ��
				col++;
				i--;
				continue;
			}

			for (j = i + 1; j < r; j++) {
				if (d[j][col]) {
					// ��ǰ�еĵ�col�������Ϊ0���������Ԫ
					// ���ڵ�i�����µĵ�col�е�����Ԫ�ض���Ϊ0 
					LL lastcoff = d[i][col];
					LL nowcoff = d[j][col];
					for (k = col; k <= c; k++) {
						d[j][k] = (ProductMod(d[j][k], lastcoff, mod) - ProductMod(d[i][k], nowcoff, mod));
						if (d[j][k] < 0) d[j][k] += mod;
						else if (d[j][k] >= mod) d[j][k] -= mod;
					}
				}
			}
			col++;
		}
		// i��ʾ��i������еľ���Ԫ�ض�Ϊ0 
		// ���� (0 0 0 0 0 0 d[j][c]) (d[j][c] != 0) ������������޽� 
		for (j = i; j < r; j++) {
			if (d[j][c]) {
				return -1;
			}
		}
		// ���ɱ�Ԫ�� Ϊ (������ - �����е���Ŀ)
		int free_num = c - i;

		// �����У���֤���ľ���Ϊ�ϸ������ǣ��������������µ��ж�Ϊ0 
		for (i = 0; i < r && i < c; i++) {
			if (!d[i][i]) {
				// �Խ���Ϊ0 
				for (j = i + 1; j < c; j++) {
					// �ڸ�������ҵ�һ����Ϊ0��Ԫ�����ڵ��У�����i����һ�� 
					if (d[i][j]) break;
				}
				if (j < c) {
					swap_col(i, j);
				}
			}
		}
		xcnt = (((LL)1) << (LL)free_num);

		getAns(mod);
		return xcnt;
	}

	void debug_print() {
		int i, j;
		printf("-------------------------------\n");
		for (i = 0; i < r; i++) {
			for (j = 0; j <= c; j++) {
				printf("%I64d ", d[i][j]);
			}
			puts("");
		}
		printf("-------------------------------\n");
	}
};

LL v[MAXN][MAXN];

int main() {
	int t;
	int i, j, k;
	int cases = 1;
	int n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (i = 0; i < n + 1; i++) {
			for (j = 0; j < n; j++) {
				scanf("%I64d", &v[i][j]);
				v[i][j] += DELTA;
				v[i][j] = (v[i][j] % MOD + MOD) % MOD;
				// ����ֵ�п����Ǹ�����ͬ��������Ŀ϶�Ϊ�Ǹ���
				// ���Գ�ʼ����Ҫ����һ��������֤��һ�����ڵ���0
			}
		}
		GaussMatrix M;
		M.r = M.c = n;
		for (i = 0; i < M.r; i++) {
			for (j = 0; j <= M.c; j++) {
				if (j < M.c) {
					M.d[i][j] = ProductMod(2, ((v[i + 1][j] - v[i][j]) % MOD + MOD) % MOD, MOD);
					if (M.d[i][j] < 0) M.d[i][j] += MOD;
				}
				else {
					LL s = 0;
					for (k = 0; k < M.r; k++) {
						s += (ProductMod(v[i + 1][k], v[i + 1][k], MOD) - ProductMod(v[i][k], v[i][k], MOD));
						s %= MOD;
						if (s<0) s += MOD;
					}
					M.d[i][j] = s;
				}
			}
		}

		M.gauss(MOD);
		printf("Case %d:\n", cases++);
		for (i = 0; i < M.c; i++) {
			if (i) printf(" ");
			printf("%I64d", M.x[i] - DELTA);
		}
		puts("");

	}
	return 0;
}


/*
10
2
1 0
-1 0
0 1

3
2 2 3
0 2 3
1 3 3
1 2 4

*/