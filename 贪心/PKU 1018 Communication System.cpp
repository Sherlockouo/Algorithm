#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
/*
    ���⣺���� n (n <= 100) �����ݣ��� i �������� m[i] ����Ԫ�飬�ֱ�Ϊ (b[i][j], p[i][j]);
    Ҫ��ÿ��ѡ���һ����Ԫ�飬����ʹ�� min(b) / sum(p) ���

    ��⣺̰��

    1�������е�b��������
    2��ö�����е�b��������ڵ���b�ģ���ÿ��������ѡ��һ�� p��С�ģ����������鶼���ҵ��Ļ����ۼӺ�
    3��ͳ�� b / sum(p) ��С�ľ��Ǵ���
*/

int a[10010], atop;
struct v {
    int b, p;
}V[110][110];

#define inf 1000000000

int getminprice(int idx, int m, int minB) {
    int ret = inf;
    for (int i = 0; i < m; ++i) {
        if (V[idx][i].b >= minB) {
            if (V[idx][i].p < ret) ret = V[idx][i].p;
        }
    }
    return ret;
}

double getans(int n, int m, int minB) {
    int i;
    int sump = 0;
    for (i = 0; i < n; ++i) {
        int p = getminprice(i, m, minB);
        if (p == inf) return -inf;
        sump += p;
    }
    return minB * 1.0 / sump;
}

int main() {
    int i, j;
    int n, m;
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        atop = 0;
        for (i = 0; i < n; ++i) {
            scanf("%d", &m);
            int max = 0;
            for (j = 0; j < m; ++j) {
                int b, p;
                scanf("%d %d", &b, &p);
                V[i][j].b = b;
                V[i][j].p = p;
                a[atop++] = b;
            }
        }
        sort(a, a + atop);
        double Max = 0.0;
        for (i = 0; i < atop; ++i) {
            if (i && a[i] == a[i - 1]) continue;
            double ans = getans(n, m, a[i]);
            if (ans > Max) Max = ans;
        }
        printf("%.3lf\n", Max);
    }

    return 0;
}

/*
100
3
3 100 1 200 1 300 1 
3 100 2 200 2 300 2
3 100 3 200 3 300 3

*/