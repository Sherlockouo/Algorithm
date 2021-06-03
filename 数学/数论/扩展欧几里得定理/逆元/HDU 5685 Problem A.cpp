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

const int mod = 9973;
const int maxn = 100010;

char str[maxn];
ll pro[maxn];
ll ans[maxn], inv[maxn];

int main() {
    int Q;
    while (scanf("%d", &Q) != EOF) {
        scanf("%s", str + 1);
        ans[0] = 1;
        inv[0] = 1;
        for (int i = 1; str[i]; ++i) {
            ans[i] = ans[i - 1] * (str[i] - 28) % mod;
            inv[i] = inv[i - 1] * Inv(str[i] - 28, mod) % mod;
        }
        while (Q--) {
            int a, b;
            scanf("%d %d", &a, &b);
            if (a > b) {
                swap(a, b);
            }
            int out = ans[b] * inv[a - 1] % mod;
            printf("%d\n", out);
        }
    }
    return 0;
}