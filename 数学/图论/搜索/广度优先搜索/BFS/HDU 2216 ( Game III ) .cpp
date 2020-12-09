#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
struct point
{
    int x;
    int y;
    int dx;
    int dy;
    int step;
}temp, tt;
queue<point> q;
int visit[21][21][21][21];
char map[22][22];
int n, m, i, j, flag;
int main()
{
    while(scanf("%d%d", &n, &m ) != EOF)
    {
        memset(visit, 0, sizeof(visit));
        for(i = 1; i <= n ;i++)
        {
            scanf("%s", &map[i][1]);
        }
        temp.step = 0;
        for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= m; j++)
            {
                if(map[i][j] == 'Z')
                {
                    temp.x = i;
                    temp.y = j;
                    map[i][j] = '.';
                }
                if(map[i][j] == 'S')
                {
                    temp.dx = i;
                    temp.dy = j;
                    map[i][j] = '.';
                }
            }
        }
        flag = -1;

        while(!q.empty())
            q.pop();

        q.push(temp);
        while(!q.empty())
        {
            temp = q.front();
            q.pop();

            if(abs(temp.dx - temp.x) + abs(temp.dy - temp.y) <= 1)
            {
                flag = temp.step;
                break;
            }
            tt.step = temp.step + 1;

            for(i = 0; i < 4; i++)
            {
                tt.x = temp.x + dir[i][0];
                tt.y = temp.y + dir[i][1];

                if(tt.x < 1 || tt.y < 1 || tt.x > n || tt.y > m)
                    continue;
                if(map[tt.x][tt.y] != '.')
                    continue;

                tt.dx = temp.dx - dir[i][0];
                tt.dy = temp.dy - dir[i][1];

                if(tt.dx < 1 || tt.dy < 1 || tt.dx > n || tt.dy > m)
                {
                    tt.dx = temp.dx;
                    tt.dy = temp.dy;
                }

                if(map[tt.dx][tt.dy] == 'X')
                {
                    tt.dx = temp.dx;
                    tt.dy = temp.dy;
                }

                if(!visit[tt.x][tt.y][tt.dx][tt.dy])
                {
                      visit[tt.x][tt.y][tt.dx][tt.dy] = 1;
                      q.push(tt);
                }
            }
        }
        if(flag == -1)
            printf("Bad Luck!\n");
        else
            printf("%d\n", flag);
    }
}
