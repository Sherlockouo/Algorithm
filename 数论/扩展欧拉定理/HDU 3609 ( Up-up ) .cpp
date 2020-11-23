#include <iostream>
#include <cstring>
#include <vector>
using namespace std;


#define MAXP 65540
#define LL long long

int primes[MAXP];
bool notprime[MAXP];

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

// ŷ������ - ��ȡС��n��������n���ص����ĸ��� 
// ������
// Phi(10) = 4
// �� 1��3��7��9  �ܹ�4�� 
int Phi(int n) {
	if (n == 1) {
		return 1;
	}
	int ans = 1;
	// �����Գ� 
	for (int i = 1; i <= primes[0]; i++) {
		int p = primes[i];
		if (n % p == 0) {
			n /= p;
			ans *= (p - 1);
			while (!(n % p)) {
				n /= p;
				ans *= p;
			}
		}
		if (n == 1) {
			return ans;
		}
	}
	return ans * (n - 1);
}

LL power(LL a, LL b, LL c) {
	a %= c;

	if (b == 0) {
		return 1 % c;
	}
	LL tmp = power(a*a%c, b / 2, c);
	if (b & 1) {
		tmp = tmp * a % c;
	}
	return tmp;
}

LL realUp(LL a, LL k, LL checkVal) {
	if (k == 1) {
		if (a >= checkVal) {
			return -1;
		}
		return a;
	}
	int i;
	LL cnt = realUp(a, k - 1, checkVal);
	if (cnt == -1) {
		return -1;
	}
	LL ans = 1;
	for (i = 0; i < cnt; ++i) {
		ans *= a;
		if (ans >= checkVal) {
			return -1;
		}
	}
	return ans;
}

LL up(LL a, LL k, int mod) {
	if (mod == 1) {
		return 0;
	}
	if (a == 1) {
		return 1 % mod;
	}
	if (k == 1) {
		return a % mod;
	}
	int phi = Phi(mod);
	LL pw = realUp(a, k - 1, phi);

	if (pw == -1) {
		return power(a, up(a, k - 1, phi) + phi, mod);
	}
	else {
		return power(a, pw, mod);
	}
}

int main() {
	LL a;
	int k;
	Eratosthenes();
	while (scanf("%lld %d", &a, &k) != EOF) {
		printf("%lld\n", up(a, k, 100000000));
	}
	return 0;
}
/*
4234234234 200
1231231231231123 200
*/