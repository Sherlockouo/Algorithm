/*
����ͬ��
���ͬ�෽�̵�һ����ת����һ��ʽ��ax + by = c��������̵���ⲽ�����£�
      i) �������a��b�����Լ��d = gcd(a, b)����ôԭ���̿���ת����d(ax/d + by/d) = c������֪��(ax/d + by/d)Ϊ����������d��������b�����̱�Ȼ�޽⣬�㷨�������������ii)��
      ii) ��i)���Ե�֪�������н���һ�����Ա�ʾ�� ax + by = c = gcd(a, b)*c'����ô����������������d = gcd(a, b) = ax + by������ŷ����¶����У�
      d = gcd(a, b) = gcd(b, a%b) = bx' + (a%b)y' = bx' + [a-b*(a/b)]y' = ay' + b[x' - (a/b)y'], ������x = y',  y = x' - (a/b)y'��
      ����gcd(a, b)��һ���ݹ�ļ��㣬���������(x, y)ʱ��(x', y')��ʵ�Ѿ����õݹ��������ˣ��ݹ����Ϊb == 0��ʱ�򣨶Ա�շת�����Ҳ��b == 0��ʱ��ݹ����������ô��ʱ���̵Ľ�x0 = 1, y0 = 0��
*/

/*
��Ԫ
��֪ a �� b������ͬ��ʽ��   ax % b = 1  �� x
1) ��� a �� b �����أ�����Ԫ�����ڣ�
2������ת����   ax + bn = 1 �����һ�����н� x��
3��x = (x % n + n) % n ת������С����������
*/

#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

#define ll long long
#pragma warning(disable : 4996)
const int maxn = 1000005;


int primes[maxn];
bool notprime[maxn];

struct factor {
	int prime, count;
	factor() :prime(0), count(0) {}
	factor(int p, int c) : prime(p), count(c) {}
	void print() {
		printf("(%d, %d)\n", prime, count);
	}
};
// �����������ɸѡ�� 
void Eratosthenes() {
	memset(notprime, false, sizeof(notprime));
	notprime[1] = true;
	primes[0] = 0;
	for(int i = 2; i < maxn; i++) {
		if( !notprime[i] ) {
			primes[ ++primes[0] ] = i;
		    //��Ҫע��i*i�������ͺ��ɸ��������⣬����ת���� __int64 
			for(ll j = (ll)i*i; j < maxn; j += i) {
				notprime[j] = true;
			}
		}
	}
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

// ��չŷ�����
// aX + bY = 1 
ll ExpGcd(ll a, ll b, ll& X, ll& Y) {
    ll q, temp;
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

// a * x % b = 1
// �� x 
ll Inv(ll a, ll b) {
    ll X, Y;
    ExpGcd(a, b, X, Y);
    X = (X % b + b) % b;
    return X;
}

ll Exp(ll a, ll n, ll Mod){
	ll ans = 1;
	while (n){
		if (n & 1) ans = ans * a % Mod;
		a = a * a % Mod;
		n >>= 1;
	}
	return ans;
}

const int mod = 1000000007;

// Kummer ���� 
// LCM(C(n,0), C(n,1), ... , C(n,n))
//       = LCM(1,2,3, ..., n+1) / (n+1)
//

int main() {
    Eratosthenes();
    int t;
    int n;
    
    scanf("%d", &t); 
    while(t--) {
        scanf("%d", &n);
        ++n;
        ll ans = 1;
        for(int i = 1; i <= primes[0]; ++i) {
            ll p = primes[i];
            if(p > n) break;
            // p ^ k <= n
            // k  <= log(p, n);
            int k = (log(n + 0.0) / log(p + 0.0) + 1e-6);
            ans *= Exp(p, k, mod);
            ans %= mod;
        }
        ans *= Inv(n, mod);
        ans %= mod;
        printf("%d\n", (int) ans);
    }
    
    return 0;
}
