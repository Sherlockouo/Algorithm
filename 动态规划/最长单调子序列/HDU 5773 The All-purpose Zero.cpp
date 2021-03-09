#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

using namespace std;

struct Pair {
    int w, s;

    bool operator <= (const Pair& p) const {
        return (w < p.w) && (s > p.s);
    }
    bool operator < (const Pair& p) const {
        return (w < p.w);
    }
};

/*******************************************����������� ģ��*******************************************/
typedef int ValueType;
const int maxn = 1000010;
// �� g �������ҵ�ʱ��
// ������ϸ񵥵������� <= 
// ����Ƿǵ�����ǵݼ������� < 
ValueType g[maxn];
int f[maxn];
int gsize;

enum LISType {
    LIST_STRICTLY = 0,            // �ϸ񵥵�
    LIST_NOTSTRICTLY = 1,         // ���ϸ񵥵�
};

bool cmpLIS(LISType lt, ValueType a, ValueType b) {
    if (LIST_STRICTLY == lt) {
        return a <= b;
    }
    else if (LIST_NOTSTRICTLY == lt) {
        return a < b;
    }
}

int findLISIndex(LISType lt, ValueType val, ValueType *g, int& gsize) {
    int l = 1, r = gsize, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (cmpLIS(lt, val, g[mid])) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return ans;
}

void findLIS(LISType lt, ValueType *a, int asize, ValueType *g, int& gsize, int* f) {
    gsize = 0;
    g[0] = -10000000;
    int zeroCnt = 1;
    for (int i = 1; i <= asize; ++i) {
        if (a[i]) {
            int ans = findLISIndex(lt, a[i], g, gsize);
            if (ans == -1) {
                ans = ++gsize;
            }
            g[ans] = a[i];            // g[ans]: ����Ϊans����������������һ��ֵ����Сֵ
        }
        else {
            ++gsize;
            for (int j = gsize + 1; j >= 1; --j) {
                g[j] = g[j - 1] + 1;
            }

            /*for (int j = 1; j <= gsize; ++j) {
                printf("%d ", g[j]);
            } puts("");*/
        }
    }
}


/*******************************************����������� ģ��*******************************************/

ValueType a[maxn];

int main() {
    int t;
    int n, cas = 0;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        findLIS(LIST_STRICTLY, a, n, g, gsize, f);
        printf("Case #%d: %d\n", ++cas, gsize);
    }

    return 0;
}

/*
7
1 3 5 8 0 7 8

6
0 1 2 3 4 5 

6
0 0 0 0 0 0

7
3 2 0 1 0 0 0

10
0 0 0 0 1 0 2 0 3 0

9
0 3 0 2 0 1 0 0 0 

7
1 3 5 8 0 7 8
*/