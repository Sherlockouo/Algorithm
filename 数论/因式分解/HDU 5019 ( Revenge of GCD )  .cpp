#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXP 1000010
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];

LL gcd(LL a, LL b) {
	return b ? gcd(b, a%b) : a;
}

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

// �����������ɸѡ�� 
void Eratosthenes() {
	memset(notprime, false, sizeof(notprime));
	notprime[1] = true;
	primes[0] = 0;
	for (int i = 2; i < MAXP; i++) {
		if (!notprime[i]) {
			primes[++primes[0]] = i;
			//��Ҫע��i*i�������ͺ��ɸ��������⣬����ת���� __int64 
			for (LL j = (LL)i*i; j < MAXP; j += i) {
				notprime[j] = true;
			}
		}
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

LL G, X, Y, K;

int main() {
	Eratosthenes();
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%I64d %I64d %I64d", &X, &Y, &K);
		G = gcd(X, Y);
		vector <LL> ans;
		for (LL i = 1; i*i <= G; i++) {
			if (G % i == 0) {
				ans.push_back(i);
				if (G / i != i) {
					ans.push_back(G / i);
				}
			}
		}

		if (K > ans.size()) {
			printf("-1\n");
		}
		else {
			sort(ans.begin(), ans.end());
			printf("%I64d\n", ans[ans.size() - K]);
		}
	}
	return 0;
}