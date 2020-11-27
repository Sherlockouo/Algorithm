/*
    ���⣺N��ѧ����ѧ��i��ȥ�ĵط�ΪP[i]��0 <= P[i] <= 10^5��, ��ʼʱ����ѧ������ѧУ���һ��������������ѡK��վͣ����ͣ����һ������P[i]��ѡ�����ģ�����Ҫ��ͬѧ�³���Ϊ��ʹ����ѧ�����ܾ�����С���������Сֵ��K<=N<=3000����
    ��⣺���ߵ����ԡ�
        ״̬��ʾ��dp[i][j]��ʾ�ڵ�i��վ����õ�j��λ��ʱ����С�ķ�
        ״̬ת�ƣ�dp[i][j] = min{dp[i'][j-1] + cost(i', i)| i'<i}
        
        cost(i', i)�ļ���cost(i', i) = sum{ min{ dist(k,i'), dist(k,i) } | i'<k<i}
        ��ô����һ��2D/1D���⣬ʱ�临�Ӷ�O(n^3)��

        �۲�cost(i', i)�������������뵽��������i'��i֮���ҵ�һ��k��ʹ��[i', k]֮��ĵ㵽i'�ľ���С�ڵ�i�ľ��룻[k+1, i]֮��ĵ��������෴��
        ��ôk��Ϊһ��ת�۵㡣

        ������״̬ת�Ʒ��̣�dp[i][j] = min{dp[i'][j-1] + cost(i', i)| i'<i} 
        i'��Ϊi�ľ��ߣ���������������ԣ���i���󣬾���i'�Ʊ�Ҳ��ͬ������Ҳ����˵�������㵥���ԣ�����
        ��j��ͬʱ����a<bʱ����dp[a][j]��dp[b][j]������a'Ϊa�ľ��ߣ�b'Ϊb�ľ��ߣ���ôa'<b'��������ö�پ��ߵ�ʱ�����ǿ��Լ��ڲ���һ��O(n)���O(1)��

        ͬʱdp[i][j]ֻ��dp[i][j-1]�йأ����еڶ�ά���Բ��ù������顣

        �����и��ӵ㣬��������Ϊ0����Ҳ�������㣬��Ҫ���⴦��
*/

#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 3010
#define MAXV 611111111

int P[MAXN], Sum[MAXN];
int n, k;
int dp[MAXN][2];
int cost[MAXN][MAXN];

void calcSum() {
    int i;
    sort(P+1, P+n+1);
    for(i = 1; i <= n; i++) {
        if(P[i]) {
            break;
        }
    }
    if(i < n+1) {
        int p = i;
        for(i = 1; i+p-1 <= n; i++) {
            P[i] = P[i+p-1];
        }
        n -= (p-1);
    }
    for(i = 1; i <= n; ++i) {
        Sum[i] = Sum[i-1] + P[i];
    }
}

void getCost() {
    int i, j;
    for(i = 1; i <= n; ++i) {
        cost[i][i] = cost[i][i+1] = 0;
        int p = i;
        for(j = i + 2; j <= n; ++j) {
            cost[i][j] = cost[i][j-1] + (j-1-p)*(P[j] - P[j-1]);
            while(p < j) {
                ++p;
                if(2*P[p] < P[i] + P[j]) {
                    cost[i][j] += (P[p] - P[i]) - (P[j] - P[p]);
                }else {
                    --p;
                    break;
                }
            }
            //printf("%d ", cost[i][j]);
        }
        //puts("");
    }
}

int main() {
    int t;
    int i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &k);
        for(i = 1; i <= n; i++) {
            scanf("%d", &P[i]);
            //P[i] = P[i-1] + i*i%12;
        }

        calcSum();
        if(0 == Sum[n] || k >= n) {
            printf("0\n");
            continue;
        }

        getCost();
        int p = 0;
        for(i = 1; i <= n; i++) {
            dp[i][0] = i*P[i] - Sum[i];
        }
        for(j = 2; j <= k; ++j) {
            int pos = j-1;
            for(i = 2; i <= n; i++) {
                dp[i][p^1] = MAXV;
                for(int ii = pos; ii <= i; ++ii) {
                    int v = dp[ii][p] + cost[ii][i];
                    if(v < dp[i][p^1]) {
                        dp[i][p^1] = v;
                        pos = ii;
                    }
                }
            }
            p ^= 1;
        }
        int ans = INT_MAX;
        for(i = k; i <= n; i++) {
            int v = dp[i][p] + (Sum[n]-Sum[i]) - (n-i)*P[i];
            if(v < ans) ans = v;
        }
        printf("%d\n", ans);
    }
    return 0;
}
/*
243
6 2
1 2 4 11 12 14

101
10 3
1 2 4 5 6 8 11 13 18 21

100
3000 198
3000 192
3000 111
3000 134
3000 1111
3000 432
3000 231
700 281
571 123
331 111
999 321
1211 791

35209
36127
63784
52942
2948
11783
30666
585
1004
384
1231
219

*/
