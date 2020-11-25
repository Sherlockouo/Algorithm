#include <iostream>
#include <algorithm>
using namespace std;

#define inf -1

int n, m;
int dp[501][5001];

struct Prod {
    int P, Q, V;
}pt[501];

bool cmp(Prod a, Prod b) {
    return (a.Q-a.P) > (b.Q - b.P);
}

int main() {
    int i, j;
    while(scanf("%d %d", &n, &m) != EOF) {
        for(i = 1; i <= n; i++) {
            scanf("%d %d %d", &pt[i].P, &pt[i].Q, &pt[i].V);
        }
        sort(pt+1, pt+1+n, cmp);
        for(i = 0; i <= n; i++) {
            for(j = 0; j <= m; j++)
                dp[i][j] = inf;
        }
        int Max = 0;
        dp[0][m] = 0;

        for(i = 1; i <= n; i++) {
            for(j = 0; j <= m; j++) {
                dp[i][j] = dp[i-1][j];
            }
            for(j = m; j >= pt[i].Q && j >= pt[i].P; j--) {
                if(dp[i-1][j] != inf) {
                    if(dp[i-1][j] + pt[i].V > dp[i][ j - pt[i].P ]) {
                        dp[i][ j - pt[i].P ] = dp[i-1][j] + pt[i].V;
                        
                        if(dp[i][ j - pt[i].P ] > Max)
                            Max = dp[i][ j - pt[i].P ];
                    }
                }
            }
        }
        printf("%d\n", Max);
    }
    return 0;
}

/*
2 10
10 15 10
5 10 5
3 10
2 10 5
3 5 6
5 7 3
*/
