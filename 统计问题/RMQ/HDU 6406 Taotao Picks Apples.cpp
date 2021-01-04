#include <iostream>
#include <cstring>
#include <cstdlib>
#include <map>

using namespace std;

// RMQ ������Сֵѯ��

const int MAXM = 18;
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

// RMQ ����Сֵ��b[i]= -a[i]����b[i]�����ֵ
int a[MAXN], b[MAXN];

// dp[i] ���� i ���Ԫ��ȡ��ʱ������ĵ����������еĳ���
int dp[MAXN];

bool check(int l, int r, int val) {
    return -b[RMQ_Query(b, f, l, r)] > val;
}

// �� [l, r] �������ҵ��±���ӽ� l �� > value ����
// �������䣬������� [l, mid] �ڵ����ֵ�ܹ��ҵ�������С���䣻
// ����ģ��� l>rʱ�����Ҳ���ʱ��ֱ�ӷ������ֵ n+1
int getFirstBiggerThan(int l, int r, int value) {
    int ans = n + 1;
    while (l <= r) {
        int mid = (l + r) >> 1;

        if (check(l, mid, value)) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return ans;
}

int pre[MAXN];
int has[MAXN];
int sum[MAXN];

void preProcess() {
    memset(has, 0, sizeof(has));
    a[0] = 0;
    sum[0] = 0;

    a[n + 1] = 2000000000;
    int now = 0;

    for (int i = 1; i <= n + 1; ++i) {
        pre[i] = now;
        sum[i] = sum[i - 1];
        if (a[i] > a[now]) {
            now = i;
            has[now] = 1;
            ++sum[now];
        }
    }

}

int main() {
    int t;
    int Q;
    int i;

    scanf("%d", &t);

    while (t--) {

        scanf("%d %d", &n, &Q);
        a[0] = 0;
        a[n + 1] = 2000000000;
        for (i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        for (i = 0; i <= n + 1; ++i) {
            b[i] = -a[i];
        }
        RMQ_Init(b, n + 1, f);
        preProcess();
        int total = sum[n + 1] - 1;

        dp[n + 1] = 0;
        for (i = n; i >= 1; --i) {
            int ans = getFirstBiggerThan(i + 1, n + 1, a[i]);
            dp[i] = dp[ans] + 1;
        }

        while (Q--) {
            int p, q;
            scanf("%d %d", &p, &q);

            int ans;
            if (has[p]) {
                if (q <= a[pre[p]]) {
                    // �� p ��ֵ ȡ����
                    ans = sum[pre[p]] + dp[getFirstBiggerThan(p + 1, n + 1, a[pre[p]])];
                }
                else {
                    // �� p ��ֵ ȡ�õ�
                    ans = sum[p] + dp[getFirstBiggerThan(p + 1, n + 1, q)];
                }
            }
            else {
                if (q <= a[pre[p]]) {
                    ans = total;
                }
                else if (q > a[pre[p]]) {
                    ans = sum[pre[p]] + 1 + dp[getFirstBiggerThan(p + 1, n + 1, q)];
                }
            }

            printf("%d\n", ans);
        }
    }



    return 0;
}

/*
10000000
13 100
1 5 6 4 8 5 3 7 8 9 8 6 10
1 9

*/