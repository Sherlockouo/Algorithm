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
    for (int i = 1; i <= asize; ++i) {
        int ans = findLISIndex(lt, a[i], g, gsize);
        if (ans == -1) {
            ans = ++gsize;
        }
        g[ans] = a[i];            // g[ans]: ����Ϊans����������������һ��ֵ����Сֵ
        f[i] = ans;               // f[i]:   ��a[i]��β������������г���
    }
}


/*******************************************����������� ģ��*******************************************/

ValueType a[maxn];
int l[maxn], r[maxn];

int power[] = { 1, 10, 100, 1000, 10000, 100000, 1000000 };

int main() {
    int n, k;
    int cas = 0, t;
    while (scanf("%d", &n) != EOF){

        for (int i = 1; i <= n; ++i) {
            char c[20];
            scanf("%s", c);

            int ppos = -1;
            int len = strlen(c);
            for (int j = 0; j < len; ++j) {
                if (c[j] == '.') {
                    ppos = j;
                    break;
                }
            }
            a[i] = 0;
            if (ppos != -1) {
                int x, y;
                sscanf(c, "%d.%d", &x, &y);
                a[i] = x * 1000000 + y * power[6 - (len - ppos - 1)];
            }
            else {
                sscanf(c, "%d", &a[i]);
                a[i] *= 1000000;
            }

        }
        findLIS(LIST_STRICTLY, a, n, g, gsize, f);
        for (int i = 1; i <= n; ++i) {
            l[i] = f[i];
        }

        for (int i = 1; i <= n / 2; ++i) {
            swap(a[i], a[n + 1 - i]);
        }

        findLIS(LIST_STRICTLY, a, n, g, gsize, f);
        for (int i = 1; i <= n; ++i) {
            r[n + 1 - i] = f[i];
        }
        int Min = n;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                int ans = l[i] + r[j];
                Min = min(Min, n - ans);
            }
        }
        printf("%d\n", Min);
    }
    return 0;
}

/*
10
1 10 30 70 50 90 50 20 5 0

7
1 9 6 6 3 4 1

7
1 2 3 2 3 2 1
*/