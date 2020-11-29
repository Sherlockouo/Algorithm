/*
���⣺
    1 2 3 4 5 ... N ������վ����ֱ�����С����ҵ����ٶ�Ϊ���٣�������ҷֱ������������ϡ�
    A B ��ʾ�����Ǹ���ҵ�λ�ã���A==B���ʾ�����ڵ�A������վ����B=A+1�����ʾ��A��A+1��·�ϡ�
    C D ��ʾǰ���Ǹ���ҵ�λ�ã���C==D���ʾ�����ڵ�C������վ����D=C+1�����ʾ��C��C+1��·�ϡ�
    ����������ҵ�ʱ���X����ӵ�i����վ����i+1����վ��ʱ��1 <= T <= 10^9����

��⣺
     ���Լ��
     ��ӵ�i������վ����i+1������վ��ʱ���ΪT[i]���ӵ�1������վ����i������վ�ļӺ�ΪS[i] = T[1] + T[2] + ... T[i-1]
     
     ��ô�����г�һЩ����ʽ��
         1 <= Si - Si-1 <= 10^9
     ���� ������Ԫ��G(x, y, z) ��ʾ S[x] - S[y] >= z 
        if(A == B) {
            if(C == D) {
                // S[C] - S[A] = X
                G(C, A, X)
                G(A, C, -X)
            }else {
                // S[C] - S[A] < X < S[D] - S[A]
                G(D, A, X+1);
                G(A, C, 1-X);
            }
        }else {
            if(C == D) {
                // S[D] - S[B] < X < S[D] - S[A]
                G(D, A, X+1);
                G(B, D, 1-X);
            }else {
                // S[C] - S[B] < X < S[D] - S[A]
                G(D, A, X+1);
                G(B, C, 1-X);
            }
        }
    
    ������Ԫ�� G(x, y, z) ���ߣ� y->x (ȨΪz) 
    ��һ���· 
*/

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAXN 4010
#define INF -1000000000
#define ll long long

struct edge {
    int from, to;
    ll val;
    int next;
    edge() {
    }
    edge(int _f, int _t, ll _v, int _n) {
        from = _f;
        to = _t;
        val = _v;
        next = _n;
    }
}E[MAXN*8];

int n;
ll dis[MAXN];
int visitCount[MAXN];
int head[MAXN], tot;

void spfa_init(int s) {
    int i;
    for(i = 0; i <= n; i++) {
        dis[i] = INF;
        visitCount[i] = 0;
    }
    dis[s] = 0;
}

// �����Ƿ���ڻ� 
bool spfa(int s) {
    int i;
    spfa_init(s);
    queue <edge> Q;
    Q.push( edge(-1, s, 0, -1) );
    
    while( !Q.empty() ) {
        edge now = Q.front();
        Q.pop();
        
        int from = now.to;
        ll predist = now.val;
        //printf("!!!!! %d %lld\n", from, predist);
        
        if( visitCount[from]++ > n ) {
            return true;
        }
        
        for(i = head[from]; i != -1; i = E[i].next) {
            int to = E[i].to;
            ll nextdist = E[i].val + predist;
            
            if(dis[to] == INF || nextdist > dis[to]) {
                dis[to] = nextdist;
                Q.push( edge(from, to, nextdist, -1) );
            }
        }    
    }
    
    return false;
}

void edge_init() {
    tot = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, int c) {
    E[tot] = edge(u, v, c, head[u]);
    head[u] = tot++;
}

// Ϊ����S1 - S2 >= w�Ĳ���ʽ���� 
void construct_edge(int S1, int S2, int w) {
    //printf(">>> %d %d %d\n", S2, S1, w);
    addEdge(S2, S1, w); 
}

int m, X;

int main() {
    int i;
    int t = 0, cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d %d %d", &n, &m, &X);
        edge_init();
        for(i = 2; i <= n; i++) {
            construct_edge(i-1, i, INF);
            construct_edge(i, i-1, 1);
        }
        while(m--) {
            int A, B, C, D;
            scanf("%d %d %d %d", &A, &B, &C, &D);
            if(A == B) {
                if(C == D) {
                    construct_edge(C, A, X);
                    construct_edge(A, C, -X);
                }else {
                    construct_edge(D, A, X+1);
                    construct_edge(A, C, 1-X);
                }
            }else {
                if(C == D) {
                    construct_edge(D, A, X+1);
                    construct_edge(B, D, 1-X);
                }else {
                    construct_edge(D, A, X+1);
                    construct_edge(B, C, 1-X);
                }
            }
        }
        int ret = spfa(1);
        printf("Case #%d:", ++t);
        if(!ret) {
            for(i = 2; i <= n; i++) {
                printf(" %d", dis[i]-dis[i-1]);
            }
        }else {
            printf(" IMPOSSIBLE");
        }
        puts("");
    }
    
    
    return 0;
}