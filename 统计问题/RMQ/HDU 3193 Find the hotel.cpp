#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>

using namespace std;

// RMQ ������Сֵѯ��

const int MAXM = 16;
const int MAXN = (1 << MAXM) + 1;

// typedef long long ValueType;
// typedef double ValueType;
typedef int ValueType;
int lg2K[MAXN];

int RMQ_MinIndex(ValueType A[], int l, int r) {
    return A[r] < A[l] ? r : l;
}

// f[i][j] = opt(f[i-1][j], f[i-1][j + 2^{i-1}]);
void RMQ_Init(ValueType A[], int ALen, int(*f)[MAXN]) {
    int i, j, k = 0;
    for (i = 1; i <= ALen; i++) {
        lg2K[i] = k - 1;
        if ((1 << k) == i) k++;
    }
    for (i = 0; i < MAXM; i++) {
        for (j = 1; j + (1 << i) - 1 <= ALen; j++) {
            if (i == 0) {
                f[i][j] = j;
            }
            else {
                f[i][j] = RMQ_MinIndex(A, f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
}

/*
�����䳤��Ϊ2^k����X��ʾ������Ϊ[a, a + 2^k)��Y��ʾ������Ϊ(b - 2^k, b]��
����Ҫ����һ����������X���Ҷ˵������ڵ���Y����˵�-1���� a+2^k-1 >= b-2^k��
��2^(k+1) >= (b-a+1), ����ȡ��������2Ϊ�ף����� k+1 >= lg(b-a+1)����k >= lg(b-a+1) - 1��
kֻҪ��Ҫȡ��С��������������������( lg(x)������2Ϊ��x�Ķ��� )��
*/
int RMQ_Query(ValueType A[], int(*f)[MAXN], int a, int b) {
    if (a == b) {
        return a;
    }
    else if (a > b) {
        a = a^b, b = a^b, a = a^b;
    }
    int k = lg2K[b - a + 1];
    return RMQ_MinIndex(A, f[k][a], f[k][b - (1 << k) + 1]);
}


int n;
int f[MAXM][MAXN];

struct val {
    int p, d;

    void read() {
        scanf("%d %d", &p, &d);
    }
    void print() {
        printf("%d %d\n", p, d);
    }
    bool operator < (const val& o) {
        if (p == o.p) {
            return d < o.d;
        }
        return p < o.p;
    }

    bool operator != (const val& o) {
        return p != o.p || d != o.d;
    }
}V[MAXN], ans[MAXN];

int a[MAXN], L;
int idx[MAXN];

int main() {
    int i;
    while (scanf("%d", &n) != EOF) {
        for (i = 0; i < n; ++i) {
            V[i].read();
        }
        sort(V, V + n);
        L = 0;
        for (i = 0; i < n; ++i) {
            if (i == 0 || V[i].p != V[i - 1].p) {
                a[++L] = V[i].d;
            }
            idx[i] = L;
        }
        RMQ_Init(a, L, f);

        int s = 0;
        for (i = 0; i < n; ++i) {
            if (idx[i] == 1 || a[RMQ_Query(a, f, 1, idx[i] - 1)] >= V[i].d) {
                ans[s++] = V[i];
            }
        }
        printf("%d\n", s);
        for (i = 0; i < s; ++i) ans[i].print();
    }


    return 0;
}

/*
9
8 9
15 10
10 15
15 9
15 9
15 8
15 7
15 11
15 12

8
9 1
8 2
7 5
7 4
7 3
7 2
6 4
5 5

*/
