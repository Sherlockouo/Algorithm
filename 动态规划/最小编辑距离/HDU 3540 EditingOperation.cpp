#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;

typedef char ValueType;
const int maxn = 1010;
int f[maxn][2];
#define I 1
#define D 1
#define R 1

int min3(int a, int b, int c) {
    return min(min(a, b), c);
}

int minEditCost(int ssize, ValueType *src, int tsize, ValueType *tar, int lim) {
    // f[i][j] ��ʾ src[1...i] ��� tar[1...j] ��׺����С������
    f[0][0] = 0;
    // Դ�� �� �մ��Ĵ���
    for (int i = 1; i <= ssize; ++i) {
        f[i][0] = f[i - 1][0] + D;
    }

    int cur = 1, last = 0;
    int pre = min(lim, ssize);
    int ans = 10000000;

    for (int j = 1; j <= tsize; ++j) {
        f[0][cur] = 0;

        for (int i = 1; i <= pre + 1; ++i) {
            int rcost = (src[i] == tar[j]) ? 0 : R;       // �滻������

            f[i][cur] = min(
                f[i - 1][cur] + D,         // Դ��1����Ϊ�˶���Ŀ�꣬Դ��Ҫɾ��1���ַ�
                f[i - 1][last] + rcost     // Դ��Ŀ�� �� �滻 ���һ���ַ�
                );

            if (i != pre + 1) {
                f[i][cur] = min(
                    f[i][cur], f[i][last] + I            // Ŀ����1����Ϊ�˶���Ŀ�꣬Դ��Ҫ����1���ַ�
                    );
            }
            if (i == ssize) {
                ans = min(ans, f[i][cur]);
            }
            //printf("%d ", f[i][cur]);
        }
        //puts("");
        ++pre;
        while (pre >= ssize || f[pre][cur] > lim) {
            --pre;
        }
        swap(cur, last);
    }
    return ans != 10000000 ? ans : -1;
}

ValueType A[1000010], B[maxn];

int main() {
    int Alen, Blen;
    int lim;
    while (scanf("%s", A + 1) != EOF) {
        scanf("%s %d", B + 1, &lim);
        Alen = strlen(A + 1);
        Blen = strlen(B + 1);

        int dist = minEditCost(Blen, B, Alen, A, lim);
        printf("%d\n", dist);
    }
    return 0;
}

/*
AGAGCTTGCGCACTTGAGCAGCTTGCGCATTGCGCACAGCTTGCGCAGCAAGAGCTTGCGCACTTGAGCAGCTTGCGCATTGCGCACAGCTTGCGCAGCAAGAGCTTGCGCACTTGAGCAGCTTGCGCATTGCGCACAGCTTGCGCAGCA AGGCTGGCGCTAGGGAAAGAGCGCTA
10

XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB
2

AGCCTTGCGA GCTAG
3

*/