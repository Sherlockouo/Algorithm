/*
С�ڵ���N�Һ�N���ص����ĺ�Ϊ phi(N)*N/2;
*/

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;


#define MAXP 65540
#define LL long long
#define MOD 1000000007

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

int n;

int main() {
	Eratosthenes();

	while (scanf("%d", &n) != EOF && n) {
		LL ans = (LL)n * Phi(n) / 2;
		ans = (LL)n*(n - 1) / 2 - ans;
		printf("%d\n", int(ans%MOD));
	}
	return 0;
}