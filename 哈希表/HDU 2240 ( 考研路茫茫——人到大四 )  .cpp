#include <iostream>

using namespace std;
struct point
{
    int num;
}p[1000];
int n, a, b, c, lele, yueyue;
char ch[10000];
int hash[221];
int i, rt, bu, fei;
int flag;

int next(int now, int step, int n)
{
    if(now + step <= n - 1)
        return now + step;
    else
        return (n - 1) - (now+step-(n-1));
}
int main()
{
    while(scanf("%d%d%d%d",&n, &a, &b, &c) != EOF)
    {
        for(i = 0; i < n; i++)
        {
            scanf("%s", ch);
            if(ch[0] == 'N')
            {
                p[i].num = -1;
            }else
            {
                sscanf(&ch[1], "%d", &p[i].num);
            }
        }
        lele = yueyue = 0;
        
        flag = 0;

        for(i = 0; i < 70000; i++)
        {
            if(i == 0)
                rt = ( (a % 6) * (c % 6) + b%6 ) % 6 + 1;
            else 
                rt = bu;

            if(i % 2 == 0)
            {
                memset(hash, 0, sizeof(hash));
                fei = rt;
                lele = next (lele, fei, n);
                while(1)
                {
                   if(!hash[lele])
                   {
                       hash[lele] = 1;
                       if(p[lele].num == -1)
                       {
                           if(lele == n-1)
                           {
                               flag = 2;
                               break;
                           }

                          if(lele == yueyue)
                           {
                               yueyue = 0;
                               break;
                           }else
                               break;
                       }else
                           lele = p[lele].num;
                   }else
                   {
                       flag = 1;
                       break;
                   }
                }
                if(flag)
                {
                    break;
                }
            }else
            {
                memset(hash, 0, sizeof(hash));
                fei = rt;
                yueyue = next (yueyue, fei, n); 
                while(1)
                {
                   
                   if(!hash[yueyue])
                   {
                       hash[yueyue] = 1;
                       if(p[yueyue].num == -1)
                       {
                           if(yueyue == n-1)
                           {
                               flag = 3;
                               break;
                           }

                           if(lele == yueyue)
                           {
                               lele = 0;
                               break;
                           }else
                               break;
                       }else
                           yueyue = p[yueyue].num;
                   }else
                   {
                       flag = 1;
                       break;
                   }
                }
                if(flag)
                {
                    break;
                }            
            }
            bu = ( (a % 6) * (rt % 6) + b%6 ) % 6 + 1;

            
        }

        if(flag == 2)
            printf("Lele\n");
        else if(flag == 3)
            printf("Yueyue\n");
        else
            printf("Impossible\n");


    }
}

