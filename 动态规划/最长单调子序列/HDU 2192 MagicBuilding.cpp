#include <iostream>
#include <algorithm>

using namespace std;

struct Pair {
    int x, y;
    Pair() {}
    Pair(int _x, int _y) : x(_x), y(_y) {}

    bool operator < (const Pair& p) const {
        if (x == p.x)
            return y < p.y;
        return x < p.x;
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
    if (LIST_NOTSTRICTLY == lt) {
        return a < b;
    }
    else {
        return a <= b;
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

int main() {
    int n, t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        sort(a + 1, a + n + 1);
        for (int i = 1; i <= n / 2; ++i) {
            swap(a[i], a[n + 1 - i]);
        }

        findLIS(LIST_NOTSTRICTLY, a, n, g, gsize, f);
        printf("%d\n", gsize);
    }

    return 0;
}
