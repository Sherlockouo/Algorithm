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

const int MAX_NUMBER = 1000010;
const int MAXP = 3163;                // (int)(sqrt(MAX_NUMBER*1.0) + 1);
#define ll long long

bool notprime[MAX_NUMBER];
int primes[MAXP];
ll eula[MAX_NUMBER];

void eulaFilter() {
    int i, j;
    notprime[1] = 1;
    eula[1] = 1;

    // 1.ö��ÿ����
    for (i = 2; i < MAX_NUMBER; ++i) {
        if (!notprime[i]) {
            // 2.����i��ŷ������i-1
            eula[i] = i - 1;
            if (i < MAXP) {
                primes[++primes[0]] = i;
            }
            for (j = i + i; j < MAX_NUMBER; j += i) {
                notprime[j] = 1;
                // 3.��������ŷ������Ϊ����*��������(1-1/i)�ĳ˻�
                if (!eula[j]) eula[j] = j;
                eula[j] = eula[j] / i * (i - 1);
            }
        }
    }
}

int main() {
    eulaFilter();
    int n;
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%lld\n", eula[n + 1]);
    }
    return 0;
}

