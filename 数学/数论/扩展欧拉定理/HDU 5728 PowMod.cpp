/*
ŷ������-ɸѡ��
n�ֽ������ӱ�ʾΪn = p1^e1 * p2^e2 * ... * pk^ek
��n��ŷ������Ϊ f(n) = (p1-1)p1^(e1-1) * (p2-1)p2^(e2-1) * ... * (pk-1)pk^(ek-1)
= n * (1-1/p1) * (1-1/p2) * ... * (1-1/pk)
��������ɸѡ��Ԥ����˳�����f(n)��
Author: WhereIsHeroFrom
Update Time: 2018-3-21
Algorithm Complexity: O(nk)
*/

#include <iostream>
#include <vector>
using namespace std;

const int MAX_NUMBER = 10000010;
const int MAXP = 3163;                // (int)(sqrt(MAX_NUMBER*1.0) + 1);
#define LL long long
#define MOD 1000000007

bool notprime[MAX_NUMBER];
int primes[MAXP];
int eula[MAX_NUMBER];
int sumeula[MAX_NUMBER];

struct factor {
	int prime, count;
	factor() {
	}
	factor(int p, int c) {
		prime = p;
		count = c;
	}
	void print() {
		printf("(%d, %d)\n", prime, count);
	}
};

void eulaFilter() {
	notprime[1] = 1;
	eula[1] = 1;

	// 1.ö��ÿ����
	for (int i = 2; i < MAX_NUMBER; ++i) {
		if (!notprime[i]) {
			// 2.����i��ŷ������i-1
			eula[i] = i - 1;
			if (i < MAXP) {
				primes[++primes[0]] = i;
			}
			for (int j = i + i; j < MAX_NUMBER; j += i) {
				notprime[j] = 1;
				// 3.��������ŷ������Ϊ����*��������(1-1/i)�ĳ˻�
				if (!eula[j]) eula[j] = j;
				eula[j] = eula[j] / i*(i - 1);
			}
		}
	}

	for (int i = 1; i < MAX_NUMBER; ++i) {
		sumeula[i] = (sumeula[i - 1] + eula[i]) % MOD;
	}
}


// ��ʽ�ֽ� - ��n�ֽ�������ݳ˻�����ʽ
// ������
// 252 = (2^2) * (3^2) * (7^1) 
// �� ans = [ (2,2), (3,2), (7,1) ]
void Factorization(int n, vector <factor>& ans) {
	ans.clear();
	if (n == 1) {
		return;
	}
	// �����Գ� 
	for (int i = 1; i <= primes[0]; i++) {
		if (n % primes[i] == 0) {
			factor f(primes[i], 0);
			while (!(n % primes[i])) {
				n /= primes[i];
				f.count++;
			}
			ans.push_back(f);
		}
		if (n == 1) {
			return;
		}
	}
	// ©��֮������ ������MAXP�����������1�� 
	ans.push_back(factor(n, 1));
}


LL Exp(LL a, LL n, LL Mod){
	LL ans = 1;
	while (n){
		if (n & 1) ans = ans*a%Mod;
		a = a*a%Mod;
		n >>= 1;
	}
	return ans;
}



LL f(LL k, LL p) {
	if (k == 1) {
		return 1 % p;
	}
	if (p == 1) {
		return 0;
	}

	if (p == 0) {
		while (1);
	}

	return Exp(k, f(k, eula[p]) + eula[p], p);
}

vector <factor> factorAns;

LL fhy(int n, int m) {
	if (m == 0) return 0;
	if (n == 1) return sumeula[m] % MOD;
	for (int i = 0; i < factorAns.size(); ++i) {
		int p = factorAns[i].prime;
		if (n % factorAns[i].prime == 0) {
			return (fhy(n / p, m)*(p - 1) + fhy(n, m / p)) % MOD;
		}
	}
}

int main() {
	eulaFilter();
	int t, n, m, p;

	while (scanf("%d %d %d", &n, &m, &p) != EOF) {
		Factorization(n, factorAns);
		int k = fhy(n, m);
		printf("%I64d\n", f(k, p));
	}
	return 0;
}