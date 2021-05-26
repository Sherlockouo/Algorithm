#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <memory.h>
#include <cmath>
using namespace std;

#pragma warning(disable : 4996)

#define ll unsigned long long
#define MAXP 65540

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
            for (ll j = (ll)i * i; j < MAXP; j += i) {
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
ll XJ[maxn];
ll XJMod[maxn];
ll g[maxn], xp[maxn];

int main() {
    Eratosthenes();
    int t, b, P;
    ll M;
    int cas = 0;

    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %llu", &b, &P, &M);

        if (b == 0 && P == 1 && M == 18446744073709551615ll) {
            printf("Case #%d: 18446744073709551616\n", ++cas);
            continue;
        }

        // 1. ���� P ��ŷ������
        int eula = Phi(P);
        // 2. ��ʼ�� x �׳� Mod P��ŷ������
        XJMod[0] = 1 % eula;
        XJ[0] = 1;
        for (int i = 1; i <= 100000; ++i) {
            XJMod[i] = XJMod[i - 1] * i % eula;
            XJ[i] = XJ[i - 1] * i;
        }
        // 3. ö������ x ���� [1, M]���ж�������
        ll cnt = 0;
        int flag = -1;
        for (ll x = 0; x <= M; ++x) {
            if (x < 10) {
                ll ans = Exp(x, XJ[x], P);
                if (ans == b) {
                    ++cnt;
                }
            }
            else {
                if (XJMod[x] == 0) {
                    flag = x;
                    break;
                }
                ll ans = Exp(x, XJMod[x] + eula, P);
                if (ans == b) {
                    ++cnt;
                }
            }
        }
        if (flag != -1) {
            // 4. ���� [x, M] �ⲿ�� 
            // Ŀǰ��ֵ���� x ^ phi(P) mod P
            // ���� g(x) ���� [0, x] ������ x ^ phi(P) mod P = b �� x �ĸ��� 
            // ���ò�ֿ��Եõ� g(M) - g(x-1) ��������Ҫ��Ľ⡣
            // ��ô i = [0��P-1] ����������ö��ֿ�����ö�ٱ�������
            // �洢�� g[i] �У����� [0, i] �����������ĸ�����
            // Ȼ������ѭ���ڼ�������Ĳ��� 
            ll x = flag;
            for (int i = 0; i < P; ++i) {
                xp[i] = (Exp(i, eula, P) == b ? 1 : 0);
                if (i) {
                    xp[i] += xp[i - 1];
                }
            }
            ll r = (M / P) * xp[P - 1] + xp[M % P];
            ll l = ((x - 1) / P) * xp[P - 1] + xp[(x - 1) % P];
            cnt += r - l;
            //printf("???? %llu\n", r - l);
        }
        /*
        ll gg = 0;
        for (ll x = 0; x <= M; ++x) {
            ll ans = Exp(x, XJ[x], P);
            if (ans == b) {
                ++gg;
            }
        }
        printf("%llu\n", gg);*/
        printf("Case #%d: %llu\n", ++cas, cnt);
    }
    return 0;
}