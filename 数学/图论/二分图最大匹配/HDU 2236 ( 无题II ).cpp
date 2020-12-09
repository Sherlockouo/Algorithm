#include <iostream>

using namespace std;

int map[101][101];
int visit[101], pre[101];
int t, n, i, j, flag, Max, k;
int MaxH, MinH;
int dfs(int low, int high, int t)
{
    int i;
    int buf;
    for(i = 1 ; i <= n; i++)
    { 
        if(map[t][i] >= low && map[t][i] <= high && !visit[i])
        {
            visit[i] = 1;
            buf = pre[i];
            pre[i] = t;
            if(buf == -1 || dfs(low, high, buf))
                return 1;
            pre[i] = buf;
        }
    }
    return 0;
}

int low, high, mid;
int hash[101];
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        MaxH = 0;
        MinH = 100;
        memset(hash, 0, sizeof(hash));

        for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= n; j++)
            {
                scanf("%d", &map[i][j]);
                if(map[i][j] > MaxH)
                    MaxH = map[i][j];
                if(map[i][j] < MinH)
                    MinH = map[i][j];
                hash[ map[i][j] ] = 1;
            }
        }
        

        low = 0;
        high = MaxH - MinH;
        flag = 0;
        int ma, mi;
        for(mid = low; mid <= high; mid++)
        {
            
            for(j = MinH; mid+j <= MaxH;j++)
            {
                if(hash[j] && hash[j+mid])
                {
                    memset(pre, -1, sizeof(pre));
                    Max = 0;
                    for(k = 1; k <= n; k++)
                    {
                        memset(visit, 0, sizeof(visit));
                        if(dfs(j, j+mid, k))
                            Max++;
                        else 
                            break;
                    }
                    if(Max == n)
                    {
                        ma = -1;
                        mi = 200;
                        for(k = 1; k <= n; k++)
                        {
                            int ty =  map[pre[k]][k];
                            if(ty > ma)
                                ma = ty;
                            if(ty < mi)
                                mi = ty;
                        }
                        if(ma == j+mid && mi == j)
                        {
                            flag = 1;
                            break;
                        }
                    }
                }
            }
            if(flag)
                break;
        }
        printf("%d\n", mid);
    }

    return 0;
}
