#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 65536

typedef int ValueType;

struct treeNode {
    ValueType lazy;
    ValueType sum;
    int len;
    // int l, r; ����˵㲻�ô棬�����ڵݹ��ʱ����Ϊ�������� 
    treeNode() {
    }
    treeNode(ValueType _sum, ValueType _lazy, int _len) {
        sum = _sum;
        lazy = _lazy;
        len = _len;
    }
    void giveLazyToSon(treeNode *lson, treeNode *rson) {
        lson->updateByValue(lazy);
        rson->updateByValue(lazy);
        lazy = 0;
    }
    void updateByValue(ValueType _val) {
        lazy += _val;
        sum += _val * len;
    }
    void updateFromSon(treeNode *lson, treeNode *rson) {
        sum = lson->sum + rson->sum;
    }
    
}nodes[MAXN*2];

ValueType srcArray[MAXN];

void segtree_build(int p, int l, int r) {
    nodes[p] = treeNode( srcArray[l], 0, (r-l+1) );
    if (l < r) {
        int mid = (l + r) >> 1;
        segtree_build(p<<1, l, mid);
        segtree_build(p<<1|1, mid+1, r);
        nodes[p].updateFromSon( &nodes[p<<1], &nodes[p<<1|1] );
    }
}

// [x, y]������ÿ���㶼����һ��ֵval 
void segtree_add(int p, int l, int r, int x, int y, ValueType val) {
    if(y < l || x > r || x > y) return ;
    if(x <= l && r <= y) {
        nodes[p].updateByValue(val);
        return ;
    } 
    nodes[p].giveLazyToSon( &nodes[p<<1], &nodes[p<<1|1] );
    int mid = (l + r) >> 1; 
    segtree_add(p<<1, l, mid, x, y, val);
    segtree_add(p<<1|1, mid+1, r, x, y, val);
    nodes[p].updateFromSon( &nodes[p<<1], &nodes[p<<1|1] );
}

// ѯ������[x, y]����ֵ�ĺ�
void segtree_query(int p, int l, int r, int x, int y, ValueType& sum) {
    if(y < l || x > r || x > y) return ;
    if(x <= l && r <= y) {
        sum += nodes[p].sum;
        return;
    }
    nodes[p].giveLazyToSon( &nodes[p<<1], &nodes[p<<1|1] );
    int mid = (l + r) >> 1; 
    segtree_query(p<<1, l, mid, x, y, sum);
    segtree_query(p<<1|1, mid+1, r, x, y, sum);
    nodes[p].updateFromSon( &nodes[p<<1], &nodes[p<<1|1] );
} 

#define INVALID_NODE -1

struct treeChain {
    // �����ʷֽṹ 
    // father �ý���Ӧ���ĸ��� 
    // son    �����ϵ��ӽ��
    // depth  ��Ӧ�������
    // size   �Ըý��Ϊ���������Ľ����� 
    int father, son, depth, size;
    
    // top    ��ǰ�����������������ͷ
    // idx    ��ǰ���͸������������� ��ɢ��� �����е� �±� 
    int top, idx; 
    treeChain() {
    }
    treeChain(int _fat, int _dep) {
        father = _fat;
        depth = _dep;
        size = 1;
        son = INVALID_NODE;
    }
    
    void Print() {
        // base info
        printf(" father = %d son = %d depth = %d size = %d top = %d idx = %d\n", father, son, depth, size, top, idx);
    }
}TC[MAXN];
int treeChainIdx;

struct edgeData {
    int u, v, val;
    int next;
    edgeData() {
    }
    edgeData(int _u, int _v, int _val, int _next) {
        u = _u;
        v = _v;
        val = _val;
        next = _next;
    } 
}edge[2*MAXN];
int head[MAXN], edgeCount;

void graphInit() {
    edgeCount = 0;
    treeChainIdx = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, int val = 0) {
    edge[ edgeCount ] = edgeData(u, v, val, head[u]);
    head[u] = edgeCount ++;
}

void addEdge2(int u, int v, int val = 0) {
    addEdge(u, v, val), addEdge(v, u, val);
}
 
void treeChain_preDfs(int u, int fat, int depth) {         
    TC[u] = treeChain(fat, depth);                         // ��ʼ��u���������ṹ��
    for (int e = head[u]; e != -1; e = edge[e].next) {     // ������ʽǰ���Ǵ洢�߽ṹ 
        int v = edge[e].v;                                 // ö������һ����u�����Ľ��v 
        if(v != fat) {                                     // ����������,���ߵ�ʱ�򽨵�˫��ߣ�����Ҫȥ������"�ر�"����� 
            treeChain_preDfs(v, u, depth+1);               // �ݹ����u������v 
            TC[u].size += TC[v].size;                      // ͳ�ƽ��u��size��Ϣ 
            
            if( TC[u].son == INVALID_NODE || \
                TC[v].size > TC[ TC[u].son ].size ) {
                TC[u].son = v;                             // ���ø����ӽ���size��Ϣ�����ض��� 
            }
        }
    }
}

void treeChain_postDfs(int u) {
    
    if( TC[u].father == INVALID_NODE ) {                   // ��������£�uΪ����� 
        TC[u].top = u;                                     //     �� ����������ͷΪ������ 
    }else {
        TC[u].idx = ++treeChainIdx;                        // (father[u], u)������ӳ�䵽���Ա���±�Ϊ ++treeChainIdx
        if( TC[TC[u].father].son == u ) {                  // ���uΪ�ض��ӣ� 
            TC[u].top = TC[TC[u].father].top;              //     �� ��������ͷ �̳������׵� ��������ͷ
        }else { 
            TC[u].top = u;                                 // ���uΪ����ӣ���������ͷ���ڱ��� 
        }
    }
    
    if( TC[u].son != INVALID_NODE ) {                      // ���ȱ����ض��� 
        treeChain_postDfs(TC[u].son);
    }
    for (int e = head[u]; e != -1; e = edge[e].next) {
        int v = edge[e].v;
        if(v == TC[u].father || v == TC[u].son) continue; // �ų��ض��Ӻ͸�������� 
        treeChain_postDfs(v);                             // �ݹ����u������v
    }
}

void treeChain_build(int n, int* nodeVal) {
    // ��Ϊ�ǵ�Ȩֵ����Ҫ���������0������Ǳ�Ȩֵ����Ҫ 
    addEdge2(0, 1);
    treeChain_preDfs(0, INVALID_NODE, 0);
    treeChain_postDfs(0);
    for(int i = 1; i <= n; i++) {
        srcArray[ TC[i].idx ] = nodeVal[i];
    }
    segtree_build(1, 1, n);    
}

void treeChain_update_func(int n, int l, int r, ValueType data) {
    // ��������Խṹ���߶�������״���� ��������... 
    if (l > r) swap(l, r);
    segtree_add(1, 1, n, l, r, data);
}

ValueType treeChain_query_func(int n, int l, int r) {
    ValueType val = 0;
    segtree_query(1, 1, n, l, r, val);
    return val;
}

void treeChain_update(int n, int x, int y, ValueType data) {
    bool flag = false;
    while(x != y) {
        if(TC[x].top == TC[y].top) {
            // x��y��ͬһ�������ϣ��������������Ա��ӳ�����������ģ�����ֱ�Ӳ������ݽṹ���и��� 
            treeChain_update_func(n, TC[x].idx, TC[y].idx, data);
            return ;
        }else {
            // x �� ��������ͷ һ������ȴ���Ǹ� 
            if(TC[ TC[x].top ].depth < TC[ TC[y].top ].depth) {
                swap(x, y);
            }
            int tx = TC[x].top;
            
            if(x == tx) {
                // x�����������������ͷ ���� Ҷ�ӽ�� 
                treeChain_update_func(n, TC[x].idx, TC[x].idx, data);
                x = TC[x].father;
            }else {
                treeChain_update_func(n, TC[tx].idx+1, TC[x].idx, data);
                x = tx;
            }
        }
    }
    treeChain_update_func(n, TC[x].idx, TC[x].idx, data);    
}

int n, m, Q;
int val[MAXN];
char str[10];

int main() {
    int i;
    while( scanf("%d %d %d", &n, &m, &Q) != EOF ) {
        for(i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
        }
        graphInit(); 
        while(m--) {
            int x, y;
            scanf("%d %d", &x, &y);
            addEdge2(x, y);
        }
        treeChain_build(n, val);
        while( Q-- ) {
            scanf("%s", str);
            if(str[0] == 'I' || str[0] == 'D') {
                int x, y, z;
                scanf("%d %d %d", &x, &y, &z);
                if(str[0] == 'D') {
                    z = -z;
                }
                treeChain_update(n, x, y, z); 
            }else {
                int x;
                scanf("%d", &x);
                printf("%d\n", treeChain_query_func(n, TC[x].idx, TC[x].idx) );
            }
        }
    }
    return 0;
}
/*
9 8 100
1 2 3 4 5 6 7 8 9
1 2
1 3
2 8
2 9
3 4
3 5
5 6
5 7
I 6 9 -5

in :
3 2 51
1 2 3
2 1
2 3
I 1 3 5
Q 1 
Q 2
Q 1 
Q 3
D 1 2 2
Q 1 
Q 3
out :
7 4 8
*/
