/*
���⣺����N����a[i](0 <= a[i] <= 1000)������������ϼӺͣ���������ϼӺ����к��mС������N,m<=10000����
��⣺01����
    dp[i][j]��ʾǰi������ϼӺͺ�ֵΪj�ķ�������
    dp[i][j] = dp[i-1][j] + dp[i-1][j-a[i]]; (��i���� ѡ/��ѡ �����֮��)
    �߽�������dp[0][0] = 1; (һ��������ȡ���������Ϊ1)
    Ȼ��ö������ dp[n][j] = sum{ dp[n][k] | 0 <= k <= j} >= m ��С��j���Ǵ��ˡ�

    �����������Ƚϴ����dp[i][j]ʱ��һάi���Բ��ù������飻�ڶ�άj�����趨һ����Ԥ�������ֵ��
*/
#include <iostream>
#include <algorithm> 
#include <set>
using namespace std;

#define MAXN 10010 
#define MAXV 100010
int n, m;
int a[MAXN];
int dp[2][MAXV];

int solve() {
    memset(dp, 0, sizeof(dp));
    int i, j, p = 0;
    int maxv = 0, flag = false;
    dp[0][0] = 1;
    for(i = 0; i < n; i++) {
        if(!flag)
            maxv += a[i];
        
        int sum = 0;
        for(j = 0; j <= maxv; j++) {
            dp[p^1][j] = dp[p][j];
            if (j >= a[i]) {
                dp[p^1][j] += dp[p][j-a[i]];
            }
            if(!flag) {
                sum += dp[p^1][j];
                if(sum > m + 1) {
                    flag = true;
                    maxv = j;
                    break;
                }
            }
        }
        p ^= 1;
    }

    int x = 0;
    dp[p][0] --;
    for(i = 0; i <= maxv; i++) {
        x += dp[p][i];
        if(x >= m) {
            break;
        }
    }

    return i;
}

int main() {
    int i, t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            //a[i] = i+1;
        }
        sort(a, a + n);
        printf("Case #%d: %d\n", ++cases, solve()); 
    }
    return 0;
} 
