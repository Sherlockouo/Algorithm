#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;


#define MAXN (100010)
#define MAXQ 100010
#define LOGMAXN 17
#define MAXNODE (MAXN*2 + MAXN*LOGMAXN)

// MAXNODE ��ʾ�ܽ�����������¼��������
//         1��MAXN*2           ��һ�ÿ����Ľ����
//         2��MAXN*LOGMAXN     ��N������ÿ�����¼��� LOGMAXN �����

struct treeNode {
    int sum;                 // ���ݺ� 
    int cnt;                 // ���ݸ��� 
    int lson, rson;          // ���Ҷ��ӱ��      
    // int l, r;             // ���������ڵݹ��ʱ����Լ������������Ϊ�˽�ʡ�ռ䲻�豣��
   
    treeNode() {
        reset();
    }
    treeNode(int _s, int _c) {
        sum = _s;
        cnt = _c;
    }
    
    void reset() {
        sum = cnt = 0;
        lson = rson = 0;
    }
   
    void setson(int _lson, int _rson) {
        lson = _lson;
        rson = _rson;
    }
   
}tNode[MAXNODE];     // ��ϯ�����
int T[MAXN];         // T[i]��ʾ��i����ϯ���ĸ�����ţ��±��1-N������ T[0] ָ�����һ��������ȫΪ0�Ŀ�������
int C[MAXN];         // C[i]��ʾ��i����ϯ�޸����ĸ�����ţ������鱾��������״��������
int L;               // L ��ɢ��������ݷ�ΧΪ [1, L]
int totalNodes;

void init() {
    L = 1;
    totalNodes = 0;
}

treeNode *getNode(int id) {
    return &tNode[id];
}

// build chair tree
void build_cmtree(int &x, int l, int r) {
    x = ++totalNodes;
    getNode(x)->reset();
    if(l < r) {
        int mid = (l + r) >> 1;
        treeNode *rt = getNode(x);
        build_cmtree(rt->lson, l, mid);
        build_cmtree(rt->rson, mid+1, r);
    }
}

// insert chair tree
// root      ǰһ����ϯ�����α���
// newroot   ��ǰ��������ϯ�����α���
// pos �����ֵ
// cnt ����ֵ��������һ��ȡ1��-1 �ֱ��ʾ ����һ���� �� ɾ��һ����
int insert_cmtree(int root, int pos, int cnt) {
    int ret = ++totalNodes;
    int l = 1, r = L;
   
    treeNode *newroot = getNode(ret);
    treeNode *oldroot = getNode(root);
   
    // root Ϊ���ľ��� �� newrootΪ�����������ṹ��һ���ģ�
    // ÿ��ͨ��pos��ֵѡ�����������������������root����������ʱ��newrootҲ��������������֮��Ȼ���������α��ڸ������ϵ����λ�ñ���һ��
    newroot->cnt = oldroot->cnt + cnt;
    newroot->sum = oldroot->sum + pos;
    
    while(l < r) {
        int mid = (l + r) >> 1;
        if(pos <= mid) {
            // val��ֵС��l + r����ֵ��˵���޸���������x����������
            // ����x����������Ҫ����һ���µĽ�㣬��x���������̳�y��������
            newroot->setson( ++totalNodes, oldroot->rson );
           
            // ��x���x����������y���y������������������
            newroot = getNode(newroot->lson);
            oldroot = getNode(oldroot->lson);
            // ��������һ��
            r = mid;
        } else {
            // val��ֵ���ڵ���l + r����ֵ��˵���޸���������x����������
            // ����x����������Ҫ����һ���µĽ�㣬��x���������̳�y��������
            newroot->setson( oldroot->lson, ++totalNodes );
                     
            // ��x���x����������y���y������������������
            newroot = getNode(newroot->rson);
            oldroot = getNode(oldroot->rson);
            // ��������һ��
            l = mid + 1;
        }
        // ����������ǰ�����޸���
        newroot->cnt = oldroot->cnt + cnt;
        newroot->sum = oldroot->sum + pos;
    }

    return ret;
}

//###### ǰ�� ��ϯ�� ģ�� 
//############################################################################################## 

/*
LCA ת��Ϊ RMQ
       ����Ҫ��һ��������7�����㣬6����Ϊ��:
              7
              (0,5) (5,2) (2,4) (3,0) (1,3) (3,6)
       1)�������㲻ȷ������ô����0Ϊ����㣬Ȼ��Ӹ���㿪ʼ����һ��������ȱ�����ԭ�б���M������ôһ�α�����Ͼͻ���2M���ߡ�
              (0,5) -> (5,2) -> (2,4) -> (4,2) -> (2,5) -> (5,0) -> (0,3) -> (3,1) -> (1,3) -> (3,6) -> (6,3) -> (3,0)
       2)�������������ߵĶ˵���һ���ģ����Կ���ѹ����һ��һά����E (edge)�У�
              E[i] = 0 5 2 4 2 5 0 3 1 3 6 3 0
         ��E�����ж�Ӧ�������ϵ���ȼ�¼������D (depth)�У�
              D[i] = 0 1 2 3 2 1 0 1 2 1 2 1 0
       3)��ÿ������E�����е�һ�γ��ֵ�λ�ü�¼��I (index)�У�
              I[i] = 0 8 2 7 3 1 10
       4) Ȼ��õ����x��y������������ȣ�
              LCA(x, y) = E[ RMQ_MIN( D, I[x], I[y] ) ]
*/
#define MAXL 18

class Edge {
    public:
        int u, v;
        int next;
        int val;   // ��Щ��Ŀ�ı�����Ȩֵ��
        Edge() {}
        Edge( int _u, int _v, int _val, int _next) {
            u = _u;
            v = _v;
            val = _val;
            next = _next;
        }
}edges[ 2*MAXN ];           // LCA �����������������ȣ���Ҫ�õ�˫��ߣ����Ա���Ϊ 2*(n-1)
int head[ MAXN ], tot;      // �ڽӱ��head��� 
int I[MAXN];                // I�±꣬ÿ�������E�����е�һ�γ��ֵ�λ�� 
int RMQ_N;

class LCAData {
public:
        int E, D;

       LCAData() {

       }
       LCAData( int _e, int _d) {
              E = _e;
              D = _d;
       }
}ld[2*MAXN];

void LCA_init() {
   memset(head, -1, sizeof(head));
   memset(I, -1, sizeof(I));
   tot = 0;
   RMQ_N = 0;
}

void addEdge(int u, int v, int val) {
    edges[tot] = Edge(u, v, val, head[u]);
    head[u] = tot++;
}

// ����E��D���� �ݹ�� 
void LCA_Dfs(int fat, int u, int depth) {
    if(I[u] == -1) I[u] = RMQ_N;

    ld[RMQ_N++] = LCAData(u, depth);
    for( int i = head[u]; i != -1; i = edges[i].next) {
        if(edges[i].v == fat) {
            continue;
        }
        LCA_Dfs(u, edges[i].v, depth + 1);
        ld[RMQ_N++] = LCAData(u, depth);
   }
}

typedef Edge stackItem;

stackItem lcaStack[2*MAXN];
int newhead[MAXN];
int top;

// ����E��D���� �ǵݹ�� 
void LCA_NonDfs(int root) {
    for(int i = 0; i < MAXN; i++) newhead[i] = head[i];
    
    top = 0;
    lcaStack[top++] = stackItem(-1, root, -1, -1);
    while(top) {
        stackItem st = lcaStack[top-1];
        int u = st.v;
        
        if(I[u] == -1) I[u] = RMQ_N;
        ld[RMQ_N++] = LCAData(u, top-1);
        int end = true;
        for( int i = newhead[u]; i != -1; i = edges[i].next) {
            if( edges[i].v == st.u ) {
                continue;
            }
            lcaStack[top++] = stackItem(edges[i].u, edges[i].v, -1, -1);
            newhead[u] = edges[i].next;
            end = false;
            break;
        }
        if(end) top--;
    }
}

// ��RMQģ��ֻ��������Сֵ����Ҫ�����ֵֻ��Ҫ��ԭ����ȡ�෴����Ȼ������ȡ�෴������
class RMQData {
public:
        int index;
        int val;
}rd[2*MAXN];

int Log2[2*MAXN];        // Log2[i] = log2(i)
int f[2*MAXN][MAXL];     // f[i][j] ��ʾ [i, (i + 2^j) - 1]����������Сֵ ��Ӧ�����±�
                         // f[i][j] = min{ f[i][j-1] , f[ i + 2^(j-1) ][j-1] }

void RMQ_Init() {
    int i, j, p;
    
    // ����log��2Ϊ�׵�i�Ķ��� log2(i)
    Log2[1] = 0;
    for(i = 2; i <= RMQ_N; i++) {
        Log2[i] = Log2[i-1];
        if( 1<<(Log2[i] + 1) == i ) {
            Log2[i] ++;
        }
    }
    for(j = 0; j < MAXL; j++) {
        for(i = 0; i < RMQ_N; i++) {
            if(j == 0) {
                f[i][0] = i;
            } else {
                f[i][j] = f[i][j-1];
                p = i + (1<<(j-1));
                if(p < RMQ_N) {
                    if( rd[ f[p][j-1] ].val < rd[ f[i][j] ].val ) {
                        f[i][j] = f[p][j-1];
                }
            }                          
        }
    }
}
}

// ѯ�ʵ�ʱ������������Ϊ2^k������
// f[l][k] �� f[r-2^k+1][k]
// ����k��ȡֵҪ���ܹ�ʹ�� [l,l+2^k-1] �� [r-2^k+1,r] �Ĳ��� Ϊ [l, r]
// ���� kΪ����l+2^k-1 <= r����ֵ��󣬼�2^k <= r-l+1
// k <= log2(r-l+1), ��kΪ����������kΪlog2(r-l+1)����ȡ��
int RMQ_Query(int l, int r) {
    if(l > r) {
        int tmp = l; l = r; r = tmp;
    }
    int k = Log2[r - l + 1];
    return rd[ f[l][k] ].val < rd[ f[r-(1<<k)+1][k] ].val ? f[l][k] : f[r-(1<<k)+1][k];
}


void LCA_To_RMQ() {
    int i;
    for(i = 0; i < RMQ_N; i++) {
        rd[i].val = ld[i].D;
        rd[i].index = i;
    }
    RMQ_Init();
}

int LCA_Query(int x, int y) {
    int l = I[x];
    int r = I[y];
    return ld[ RMQ_Query(l, r) ].E;
}

//###### ǰ�� LCA ģ�� 
//############################################################################################## 


int getIdx(int cap) {
    return cap + 1;
}

void dfs(int fat, int u) {
    for(int e = head[u]; e != -1; e = edges[e].next) {
        int v = edges[e].v;
        int val = edges[e].val;
        
        if(v == fat) continue;
        
        T[v] = insert_cmtree(T[u], getIdx(val), 1);
        dfs(u, v);
    }
}

void calc_cmtree(int root) {
    for(int i = 0; i < MAXN; i++) newhead[i] = head[i];
    
    top = 0;
    lcaStack[top++] = stackItem(-1, root, -1, -1);
    while(top) {
        stackItem st = lcaStack[top-1];
        int end = true;
        for( int i = newhead[st.v]; i != -1; i = edges[i].next) {
            if( edges[i].v == st.u ) {
                continue;
            }
            lcaStack[top++] = stackItem(edges[i].u, edges[i].v, -1, -1);
            newhead[st.v] = edges[i].next;
            end = false;
            
            T[ edges[i].v ] = insert_cmtree(T[edges[i].u], getIdx(edges[i].val), 1);
            break;
        }
        if(end) top--;
    }    
}

int minv(int a, int b) {
    return a < b ? a : b;
}

int getlson(int id) {
    return getNode(id)->lson;
}
int getrson(int id) {
    return getNode(id)->rson;
}

treeNode getSum(int s, int t, int l, int r, int a, int b, int c) {
    if(s == l && t == r) {
        
        treeNode nd;
        nd.sum = getNode(a)->sum + getNode(b)->sum - 2 * getNode(c)->sum;
        nd.cnt = getNode(a)->cnt + getNode(b)->cnt - 2 * getNode(c)->cnt;
        return nd;
    }
    int mid = (l + r) >> 1;
    if(t <= mid) {
        return getSum(s, t, l, mid, getlson(a), getlson(b), getlson(c) );
    }else if(s >= mid + 1) {
        return getSum(s, t, mid+1, r, getrson(a), getrson(b), getrson(c) );
    }else {
        treeNode ndl, ndr;
        ndl = getSum(s, mid, l, mid, getlson(a), getlson(b), getlson(c) );
        ndr = getSum(mid+1, t, mid+1, r, getrson(a), getrson(b), getrson(c) );
        return treeNode(ndl.sum + ndr.sum, ndl.cnt + ndr.cnt);
    }
    
}

int n, m;


 
__int64 getMaxFlow(int totalBudget, int s, int t, int lca) {
    int l = 1, r = L;
    int ans = 0, sum = 0, cnt = 0;
    
    while(l <= r) {
        int mid = (l + r) >> 1;
        treeNode ret = getSum(1, mid, 1, L, T[s], T[t], T[lca]);

        if ( totalBudget >= ret.cnt * mid - ret.sum ) {
            ans = mid;
            sum = ret.sum;
            cnt = ret.cnt;
            l = mid + 1;
        }else {
            r = mid - 1;
        }
    }
    __int64 re;
    if(ans == L) {
        // ������ 
        totalBudget -= (cnt * L - sum);
        // ������������ٽ���һ�η��䣬ÿ���߶����䵽 
        re = (__int64)(totalBudget / cnt) + (L-1);
    }else {
        re = ans - 1;
    }
    return re; 
} 

int main() {
    int tt, cases = 0;
    int i, j;
    scanf("%d", &tt);
    while(tt--) {
        scanf("%d %d", &n, &m);
        LCA_init();
        init();
        L = getIdx(9999);
        
        for(i = 0; i < n-1; i++) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            //u = i+1; v = i+2; c = 9999;
            addEdge( u, v, c );
            addEdge( v, u, c );
        }
        
        // ��1�Ž��Ϊ�����Ը���㹹���߶������߶��������ΪT[1] 
        // ÿ����㶼��һ���߶�����������ǵ�ǰ��㵽������·���ϵ� cap�ĳ��ִ��� �Լ� ·���ܺ� 
        build_cmtree(T[1], 1, L);
        
        RMQ_N = 0;
        LCA_NonDfs(1);
        //LCA_Dfs(-1, 1, 0);
        LCA_To_RMQ();
        //dfs(-1, 1);           
        calc_cmtree(1);       // ���϶��¹�����ϯ��

        printf("Case #%d:\n", ++cases);
        while(m--) {
            int s, t, K, A, B;
            scanf("%d %d %d %d %d", &s, &t, &K, &A, &B);
            
            int has = K / minv(A, B);
            int l = 1, r = L;
            int lca = LCA_Query(s, t);
            int ans = 0, sum = 0, cnt = 0;
            
            // ����һ���������µıߣ���ԭ����ͼ�Ͻ��й�ȣ������ķ�ʽ���й�� 
            __int64 ret = getMaxFlow(has, s, t, lca);
            
            // ����������A-B֮����һ���ߣ�����Ϊ1������A����ʣ��� K - A���д������������������ϴ�ԭͼ������ ������ 
            if( K >= A ) {
                __int64 cap = 1 + (K-A) / minv(A, B);
                __int64 rem =  getMaxFlow( 0, s, t, lca);
                //printf("%I64d %I64d\n", cap, rem);
                if (rem + cap > ret) ret = rem + cap; 
            }
            printf("%I64d\n", ret);
        }
        
    }
    return 0;
}

/*
10
7 8
1 5 2
1 2 3
2 3 4
3 4 1
3 7 5
2 6 6
1 7 100 6 6
1 7 100 101 6
1 7 100 6 2
1 7 2147483646 2147483647 1
1 2 2147483646 2147483647 1
3 2 2147483646 2147483647 1
2 3 2147483646 2147483647 1



10 10
1 2 3
1 4 8
4 3 9
4 5 8
4 7 9
6 2 5
5 8 7
5 9 0
5 10 10
1 5 1 1 10
1 5 10 1 10

ans = 16 9 48 715827886 2147483649 2147483650
*/
