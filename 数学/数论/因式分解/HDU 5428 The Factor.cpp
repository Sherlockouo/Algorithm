/*
��ʽ�ֽ�
    ����ɸѡ���Գ�sqrt(n)���ڵ��������������Լȥ��

Author: WhereIsHeroFrom
Update Time: 2018-3-21
Algorithm Complexity: O(sqrt(n))
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXP 65540
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
	// �����Գ� 
	for(int i = 1; i <= primes[0]; i++) {
		if(n % primes[i] == 0) {
			factor f(primes[i], 0);
			while( !(n % primes[i]) ) {
				n /= primes[i];
				f.count ++;
			}
			ans.push_back(f);
		}
		if(n == 1) {
			return ;
		}
	}
	// ©��֮������ ������MAXP�����������1�� 
	ans.push_back( factor(n, 1) );
}

int main() {
	int i, j;
	Eratosthenes();
	
	int t, n;
	scanf("%d", &t);
	
	while(t--) {
		vector <int> prim; 
		scanf("%d", &n);
		for(i = 0; i < n; ++i) {
			vector <factor> ans;
			int a;
			scanf("%d", &a);
			Factorization(a, ans);
			for(j = 0; j < ans.size(); ++j) {
				if( ans[j].count >= 2 ) {
					ans[j].count = 2;
				}
				while(ans[j].count--) {
					prim.push_back( ans[j].prime );
					//printf("%d - \n", ans[j].prime);
				}
			}
		}
		sort(prim.begin(), prim.end());
		if(prim.size() < 2) {
			printf("-1\n");
		}else {
			printf("%lld\n", (long long)prim[0] * prim[1]  );
		}
	} 
	
	return 0;
}



