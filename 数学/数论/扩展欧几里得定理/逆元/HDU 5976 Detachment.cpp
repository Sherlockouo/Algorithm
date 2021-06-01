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

const int mod =  1e9 + 7;
ll f[100010];

ll g(ll k) {
    return (k + 2) * (k - 1) / 2;
}

int main() {
    int t;
    int a, b;
    f[0] = 1;
    for(int i = 1; i < 100000; ++i) {
        f[i] = f[i-1] * i % mod;
    }
    
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n); 
        if(n == 4) {
            printf("4\n");
            continue;
        }
        ll l = 2, r = 100000;
        ll k = 0;
        while(l <= r) {
            ll mid = (l + r) >> 1;
            if( g(mid) <= n ) {
                k = mid;
                l = mid + 1;
            }else {
                r = mid - 1;
            }
        }
        ll val = (k*k + k*3) / 2 - n;
        int ans;
        if(val == 1) {
            ans = f[k+2] * Inv(k+1, mod) % mod * Inv(2, mod) % mod;
        }else 
            ans = f[k+1] * Inv(val, mod) % mod;
        printf("%d\n", ans);
    }
    return 0;
}

/*
20
1000 53
87 123456789
*/
