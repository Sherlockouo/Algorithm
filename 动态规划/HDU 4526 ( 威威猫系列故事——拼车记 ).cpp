/*
    ���⣺
        N����(N <= 100)��K(K <= 100)�����⳵�� 
        ÿ��������ʱ��T[i]���ܹ������˵���Z[i]; (T[i]<=S, Z[i]<=4)
        ÿ�����Ļ���ΪD��ÿ���˵ȵ�ʱ��L�������Ļ��ѣ� 
         
         ���ܷ���Sʱ���ڽ�����N���˶����ߣ������ٻ��ѣ��⳵����+�ȴ����ѣ���
        ������ܣ����impossible��
       
    ��⣺dp[K][N]����״̬��
    dp[i][j] ��ʾǰi�����⳵����j���˵���С���ۡ�
    
    dp[i][j] = min{ dp[i-1][j], min{ dp[i-1][j-k] + k*T[i] + D | 0<k<=Z[i]}}
*/


#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 110

int N, K, D, S;
int T[MAXN], Z[MAXN];
int dp[MAXN][MAXN];

int main() {
    int t;
    int i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d %d", &N, &K, &D, &S); 
        for(i = 1; i <= K; ++i) {
            scanf("%d %d", &T[i], &Z[i]);
        }
        memset(dp, -1, sizeof(dp));
        dp[0][0] = 0;
        for(i = 1; i <= K; ++i) {
            for(j = 0; j <= N; ++j) {
                dp[i][j] = dp[i-1][j];
                for(k = 1; k <= Z[i]; k++) {
                    if(j-k < 0) continue;
                    int &prev = dp[i-1][j-k];
                    if(prev == -1) continue;
                    if(prev + k*T[i] + D < dp[i][j] || dp[i][j] == -1) {
                        dp[i][j] = prev + k*T[i] + D;
                    }
                } 
            }
        }
        if(dp[K][N] == -1) {
            printf("impossible\n");
        }else {
            printf("%d\n", dp[K][N]);
        }
        
    }
    return 0;
} 

