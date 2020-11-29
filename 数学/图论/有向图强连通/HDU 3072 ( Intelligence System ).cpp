#include <iostream>

using namespace std;

#define MAXN 50010
#define MAXM 200020
#define INF 1000000000

class Edge {
public:
    int u, v, next;
    int val;
    Edge(){
    }
    Edge(int _u, int _v, int _val, int _n) {
        u = _u;
        v = _v;
        val = _val;
        next = _n;
    }
};

int n;
int head_p[MAXN], tot_p;
int head_n[MAXN], tot_n;
Edge edges_p[MAXM], edges_n[MAXM];

// һЩ������Ϣ
// �������ͼ����ʱ���¼ �������� �ĵ�
int torder[2*MAXN], nowtime;
bool visited[MAXN];

int scc;         // ǿ��ͨ��֧��
int id[MAXN];    // ǿ��ͨ���

void reset() {
    memset(head_p, -1, sizeof(head_p));
    memset(head_n, -1, sizeof(head_n));
    tot_p = 0, tot_n = 0;
}

void addEdge(int u, int v, int val, bool inv) {
    if ( !inv ) {
        // �����
        edges_p[ tot_p ] = Edge(u, v, val, head_p[u]);
        head_p[u] = tot_p ++;
    }else {
        // �����
        edges_n[ tot_n ] = Edge(v, u, val, head_n[v] );
        head_n[v] = tot_n ++;
    }
}

// ��������ͼ����¼ÿ��������ʱ��
void dfs_post(int u) {
    if (visited[u]) {
        return;
    }
    visited[u] = true;
    for(int i = head_p[u]; i != -1; i = edges_p[i].next) {
        int v = edges_p[i].v;
        dfs_post(v);
    }
    torder[ nowtime ++ ] = u;
}

// ������������¼ÿ�������ɱ�����ʱ��
void postTraversal() {
    nowtime = 0;
    memset( visited, false, sizeof(visited) );

    for(int i = 1; i <= n; i++) {
        dfs_post(i);
    }
}

// �������ͼ����¼ÿ�����ǿ��ͨ��֧��� (0 - base)
void dfs_pre(int u) {
    if(visited[u]) {
        return ;
    }
    visited[u] = true;
    id[u] = scc;
    for(int i = head_n[u]; i != -1; i = edges_n[i].next) {
        int v = edges_n[i].v;
        dfs_pre(v);
    }        
}

// ǿ��ͨ��֧
void kosaraju() {
    scc = 0;
    memset( visited, false, sizeof(visited) );

    for(int i = nowtime-1; i >= 0; i--) {
        int u = torder[i];
        if(!visited[u]) {
            dfs_pre(u);
            scc ++;
        }
    }
}

int mat[200][200];

int main() {
    int m;
    int i, j;
    while( scanf("%d %d", &n, &m) != EOF && (n+m) ) {
        reset();

        while(m--) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            x ++;
            y ++;
            addEdge(x, y, z, false);
            addEdge(x, y, z, true);
        }
        postTraversal();
        kosaraju();

        for(i = 0; i < scc; i++) {
            for(j = 0; j < scc; j++) {
                mat[i][j] = INF;
            }
        }
        // ������ͼ
        for(i = 1; i <= n; i++) {
            for(j = head_p[i]; j != -1; j = edges_p[j].next) {
                int to = edges_p[j].v;
                int nu = id[i], nv = id[to];
                if(nu == nv) continue;
                if( edges_p[j].val < mat[nu][nv] ) {
                    mat[nu][nv] = edges_p[j].val;
                }
            }
        }

        int ans = 0;
        for(i = 0; i < scc; i++) {
            if( i == id[1] ) {
                continue;
            }
            int val = INF;
            for(j = 0; j < scc; j++) {
                if( mat[j][i] < val ) {
                    val = mat[j][i];
                }
            }
            ans += val;
        }
        printf("%d\n", ans);
        
    }
    return 0;
}

/*
5 5
0 1 1
1 2 2
2 3 3
3 4 4
2 4 1
*/
