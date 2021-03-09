#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;


/*******************************************����������� ģ��*******************************************/
typedef int ValueType;
const int maxn = 100010;
const int inf = -1;
// �� g �������ҵ�ʱ��
// ������ϸ񵥵������� <= 
// ����Ƿǵ�����ǵݼ������� < 
ValueType g[maxn];
int idx[maxn];
int pre[maxn];
int f[maxn];
int gsize;
int path[maxn], pasize;

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

void findPath(int asize) {
    int maxIdx = inf;
    for (int i = asize; i >= 1; --i) {
        if (maxIdx == -1 || f[i] > f[maxIdx]) {
            maxIdx = i;
        }
    }
    pasize = 0;
    while (maxIdx != inf) {
        path[pasize++] = maxIdx;
        maxIdx = pre[maxIdx];
    }

    for (int i = 0; i < pasize / 2; ++i) {
        swap(path[i], path[pasize - 1 - i]);
    }
}

void findLIS(LISType lt, ValueType *a, int asize) {
    gsize = 0;
    idx[0] = inf;
    for (int i = 1; i <= asize; ++i) {
        int ans = findLISIndex(lt, a[i], g, gsize);
        if (ans == -1) {
            ans = ++gsize;
        }
        g[ans] = a[i];            // g[ans]: ����Ϊans����������������һ��ֵ����Сֵ
        idx[ans] = i;             // idx[ans]: ƥ�� g ������±�
        pre[i] = idx[ans - 1];    // pre[i]: ��i������Ϊ���������е����һ������ǰ���� pre[i]
        f[i] = ans;               // f[i]:   ��a[i]��β������������г���
    }
    findPath(asize);
}


/*******************************************����������� ģ��*******************************************/


ValueType a[maxn];

int main() {
    int n, x;
    // n = 500
    int t, cas = 0;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i){
            scanf("%d", &a[i]);
            a[i] -= i;
        }
        findLIS(LIST_NOTSTRICTLY, a, n);
        gsize = n - gsize;
        printf("Case #%d:\n%d\n", ++cas, gsize);

    }
    return 0;
}