/*
	���⣺�� (N-1)! MOD N   (2<=N<=10^9)
	
	��⣺
	1�� N = p�������������� ��Ϊ p-1
	2�� N = p^n�� ���������Ĵ��� (n>1)��
		��� (N-1)! ����  p, 2p, 3p, np ���Ϊ0����ô��Ҫ���㣺
			np <= p^n - 1 
	 	ֻ�е� p=2�� n=2 ʱ��������⣬��Ҫ���⴦���������
		 	p^n - 1 > np �����
	3�� N = p1^n1 p2^n2 ... pk^nk��   
	 	һ�������ҵ������ӣ�ʹ�� mod N ��ֵΪ 0 
	
*/



/*
Eratosthenes����ɸѡ
    ���������ı�����Ȼ�Ǻ���������ʣ���С����ö�٣�������к�����
Author: WhereIsHeroFrom
Update Time: 2018-3-19
Algorithm Complexity: O(n)
*/

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXP 31633
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];

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

// ��ʽ�ֽ� - ��n�ֽ�������ݳ˻�����ʽ
// ������
// 252 = (2^2) * (3^2) * (7^1) 
// �� ans = [ (2,2), (3,2), (7,1) ]
void Factorization(int n, vector <factor>& ans) {
	ans.clear();
	if(n == 1) {
		return ;
	}
	if(n < MAXP) {
		if( !notprime[n] ) {
			ans.push_back( factor(n, 1) );
			return ;
		}
 	}
	// �����Գ� 
	for(int i = 1; i <= primes[0]; i++) {
		if(n % primes[i] == 0) {
			factor f(primes[i], 0);
			while( !(n % primes[i]) ) {
				n /= primes[i];
				f.count ++;
			}
			ans.push_back(f);
			if(ans.size() > 1) {
				return ;
			}
		}
		if(n == 1) {
			return ;
		}
	}
	// ©��֮������ ������MAXP�����������1�� 
	ans.push_back( factor(n, 1) );
}

int main() {
	Eratosthenes();
	int t, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		if(n == 4) {
			printf("2\n");
			continue;
		}
		vector <factor> ans;
		Factorization(n, ans);
		if(ans.size() == 1) {
			if(ans[0].count == 1) {
				printf("%d\n", n - 1);
			}else {
				printf("%d\n", 0);
			}
		}else {
			printf("0\n");
		}
	} 
	return 0;
}

