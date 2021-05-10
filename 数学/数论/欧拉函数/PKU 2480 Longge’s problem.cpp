/*
ŷ������
    n�ֽ������ӱ�ʾΪn = p1^e1 * p2^e2 * ... * pk^ek
    ��n��ŷ������Ϊ f(n) = (p1-1)p1^(e1-1) * (p2-1)p2^(e2-1) * ... * (pk-1)pk^(ek-1)
Author: WhereIsHeroFrom
Update Time: 2018-3-21
Algorithm Complexity: O(sqrt(n))
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

#define MAXP 65540
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];

// �����������ɸѡ�� 
void Eratosthenes() {
	memset(notprime, false, sizeof(notprime));
	notprime[1] = true;
	primes[0] = 0;
	for(int i = 2; i < MAXP; i++) {
		if( !notprime[i] ) {
			primes[ ++primes[0] ] = i;
		    //��Ҫע��i*i�������ͺ��ɸ��������⣬����ת���� __int64 
			for(LL j = (LL)i*i; j < MAXP; j += i) {
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
	if(n == 1) {
		return 1;
	}
	int ans = 1; 
	// �����Գ� 
	for(int i = 1; i <= primes[0]; i++) {
		int p = primes[i];
		if(n % p == 0) {
			n /= p;
			ans *= (p - 1);
			while( !(n % p) ) {
				n /= p;
				ans *= p;
			}
		}
		if(n == 1) {
			return ans;
		}
	}
	return ans * (n - 1);
}

int main() {
	Eratosthenes();
    int n;
	while(scanf("%d", &n) != EOF) {
	    int sqrtn = sqrt(n + 0.0) + 1e-8;
        LL ans = 0; 
        for(int k = 1; k <= sqrtn; ++k) {
            
            if(n % k == 0) {
                ans += (LL)k * Phi(n/k);
                if(k != n/k) {
                    ans += (LL)n/k * Phi(k);
                }
            } 
        } 
        printf("%lld\n", ans);
    }
	return 0;
}



