#include <iostream>

using namespace std;

int dir[12][2] = {
    {-1, -2},
    {-2, -1},
    {-2, 1},
    {-1, 2},

    {1, 2},
    {2, 1},
    {2, -1},
    {1, -2},

    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};

int map[81][81];
int V[2510][503];
int visit[2510], pre[ 2510 ];

int val( int x, int y, int m ) {
    return x * m + y;
}

int dfs( int key ) {
    int i;
    for( i = 1; i <= V[key][0]; i ++ ) {
        int to = V[key][i];
        if( !visit[ to ] ) {
            visit[ to ] = 1;
            int k = pre[ to ];
            pre[ to ] = key;
            if( k == -1 || dfs(k) )
                return 1;
            pre[ to ] = k;
        }
    }
    return 0;
}

int main() {
    int i, j, k;
    int n, m;
    int cas = 1;
    while( scanf( "%d %d", &n, &m ) != EOF && (n||m) ) {
        for( i = 0; i < n; i ++ ) {
            for( j = 0; j < m; j ++ ) {    
    
                int now = val(i, j, m );
                V[ now ][0] = 0;

                scanf( "%d", &map[i][j] );
            }
        }
        for( i = 0; i < n; i ++ ) {
            for( j = 0; j < m; j ++ ) {
                int now = val(i, j, m );
            

                if( map[i][j] == -1 )
                    continue;

                for( k = 0; k < 12; k ++ ) {
                    if( map[i][j] & (1<<k) ) {
                        int x = i + dir[k][0];
                        int y = j + dir[k][1];

                        if( x < 0 || y < 0 || x >= n || y >= m )
                            continue;
                        if( map[x][y] == -1 )
                            continue;

                        int to = val( x, y, m );
                        V[now][ ++V[now][0] ] = to;
                        V[ to ][ ++V[to][0] ] = now;
                    }
                }
            }
        }

        int Max = 0;
        memset( pre, -1, sizeof( pre ));
        for( i = 0; i < n*m; i ++ ) {
            memset( visit, 0, sizeof( visit ) );
            Max += dfs(i);
        }
        printf("%d. %d\n", cas++, Max/2 );
    }
    return 0;
}

