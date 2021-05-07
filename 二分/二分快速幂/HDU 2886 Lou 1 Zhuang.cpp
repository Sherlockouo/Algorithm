#include <iostream> 
#include <cstdio>
#include <cstring>
#include <memory.h>

using namespace std;
#pragma warning(disable : 4996)

#define ll long long
ll exp(ll a, ll b, ll c) {
    if (b == 0) {
        return 1 % c;
    }
    ll tmp = exp(a * a % c, b >> 1, c);
    if (b & 1) {
        tmp = tmp * a % c;
    }
    return tmp;
}

/*
    ��һ���� N ��ɳ˻������� P

    ��� P % 2009

    �ҹ��ɣ�
        P һ������������ 2 �� 3 ��ɵģ������������������

    N | 2���� | 3����
    - |   -  |   -
    1 |   0  |  0
    2 |   1  |  0
    3 |   0  |  1
    4 |   2  |  0
    5 |   1  |  1
    6 |   0  |  2
    7 |   2  |  1
    8 |   1  |  2
    9 |   0  |  3
   10 |   2  |  2
   11 |   1  |  3
   12 |   0  |  4
   13 |   2  |  3
   14 |   1  |  4
   15 |   0  |  5

   1 2 3 ֱ����� n ���ɡ�
   �� 4 ��ʼ�� 2������  2 1 0 ����ѭ�������� 2 ���� = 2 - (N-4)%3;
             3������ 012�� 123�� 234�� 345 ����һ��һ��ѭ�������� 3 ���� = (N-4) / 3 + (N-4)%3;
*/
int main() {

    int n;
    while (scanf("%d", &n) != EOF) {
        if (n <= 3) {
            printf("%d\n", n);
        }
        else {
            int p2 = 2 - (n - 4) % 3;
            int p3 = (n - 4) / 3 + (n - 4) % 3;
            int ans = exp(2, p2, 2009) * exp(3, p3, 2009) % 2009;
            printf("%d\n", ans);
        }
    }

    return 0;
}

