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
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

#define ll long long
#pragma warning(disable : 4996)

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

ll Exp(ll a, ll n, ll Mod) {
    ll ans = 1;
    while (n) {
        if (n & 1) ans = ans * a % Mod;
        a = a * a % Mod;
        n >>= 1;
    }
    return ans;
}

const int maxn = 100005;

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
    for (int i = 2; i < maxn; i++) {
        if (!notprime[i]) {
            primes[++primes[0]] = i;
            //��Ҫע��i*i�������ͺ��ɸ��������⣬����ת���� __int64 
            for (ll j = (ll)i * i; j < maxn; j += i) {
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
const int mod = 9901;

int main() {
    Eratosthenes();
    int a, b;
    while ( scanf("%d %d", &a, &b) != EOF ) {
        if(!a) {
            if(b == 0) printf("1\n");
            else printf("0\n");
            continue;
        }

        vector <factor> v;
        Factorization(a, v);
        ll ans = 1;
        for(int i = 0; i < v.size(); ++i) {
            if( (v[i].prime - 1) % mod == 0 ) {
                ans *= ((ll)v[i].count * b + 1) % mod;
                ans %= mod;
                continue;
            }
            ans *= ( Exp(v[i].prime, (ll)v[i].count * b + 1, mod) - 1);
            ans %= mod;
            ans *= Inv(v[i].prime - 1, mod);
            ans %= mod;
        }
        ans = (ans % mod + mod) % mod;
        printf("%d\n", (int)ans);
    }
    return 0;
}
