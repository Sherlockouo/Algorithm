/*
lazy˼��
    ���ģ��
        ������¡���͡�
        �������ͣ�
            poj 3468 A Simple Problem with Integers
        ���洢
            ��sum��ÿ�����䵱ǰ�ĺ� 
            �ӳٱ��lazy����ʾ��ǰ��������lazy�ĺ�δ�����ۼ� 

        �ӿ�˵��
            giveLazyToSon      �����ӳٱ�Ǹ������ӽ�㣨�����ӽ���updateByValue������lazy���ã�
            updateByValue      ͨ��ĳ��lazyֵ���µ�ǰ�����Ϣ������sum��lazy��
            updateFromSon      ͨ�������ӽ����µ�ǰ�����Ϣ������sum��
            mergeQuery         ѯ��ʱ���ڶԷָ����ӽ����кϲ��ã���ͬ���ʵ�ֲ�ͬ

        ����˵��
            ������              ���þ�̬����   treeNode::segtree_build(1, 1, n);
            ����([x, y], val)�� ���þ�̬����   treeNode::segtree_insert(1, 1, n, x, y, val);
            ѯ��([x, y]):       ���þ�̬����   treeNode::segtree_query(1, 1, n, x, y, ans);

*/ 

#include <iostream>
#include <cmath>
using namespace std;

#define MAXN 131072
typedef __int64 ValueType;

// ����[l, r]��[x, y]�����߶��Ƿ��ཻ
bool is_intersect(int l, int r, int x, int y) {
    return !(r < x || l > y);
}
// ����[x, y]�Ƿ���ȫ����[l, r]
bool is_contain(int l, int r, int x, int y) {
    return x <= l && r <= y;
}

struct treeNode {
    char layer;
    ValueType sum;
    int pid;
    int l, r;
    treeNode() {
        reset(-1, 0, 0, 0);
    }
    void reset(int p, ValueType v, int _l, int _r) {
        sum = v;
        pid = p;
        layer = 0;
        l = _l, r = _r;
    }
    int lson() { return pid << 1; }
    int rson() { return pid<<1|1; }
    
    bool addValue(int v);
    void updateByValue(int v);
    void giveLazyToSon();
    void updateFromSon();

    // ѯ�ʵ�ʱ�򽫽��ϲ�������
    void mergeQuery(int p);

    // ���� 
    static void segtree_build(int p, int l, int r);
    // �����߶�[x, y]��[l, r]
    static void segtree_insert(int p, int l, int r, int x, int y, ValueType val);
    // ����ѯ��[x, y]�ϵ���Ϣ
    static void segtree_query(int p, int l, int r, int x, int y, treeNode& ans);
    

};

/* ȫ�ֱ��� 
    nodes[MAXN*2] �洢���о�̬�߶������(��̬���ڴ�̫��ʱ��)
*/
treeNode nodes[MAXN*2];
ValueType srcArray[65][MAXN];
int maxDepth;

bool treeNode::addValue(int v) {
    if( layer != -1 ) {
        updateByValue( layer + v < maxDepth ? layer + v : maxDepth );
    }
    return layer != -1;
}

void treeNode::updateByValue(int _layer) {
    layer = _layer;
    sum = srcArray[layer][r] - srcArray[layer][l-1];
}

void treeNode::giveLazyToSon() {
    if( layer != -1 ) {
        nodes[ lson() ].updateByValue(layer);
        nodes[ rson() ].updateByValue(layer);
    }
}

void treeNode::updateFromSon() {
    sum = nodes[ lson() ].sum + nodes[ rson() ].sum;
    int ll = nodes[ lson() ].layer;
    int rl = nodes[ rson() ].layer;
    
    // �������� 
    if ( ll  == -1 || rl == -1 ) {
        layer = -1;
    }else {
        layer = ll == rl ? ll : -1;
    }
}

void treeNode::mergeQuery(int p) {
    sum += nodes[p].sum;
}

void treeNode::segtree_build(int p, int l, int r) {
    // �����߶�������ʱ��ֻ��Ҫ֪�����߶�������Ͻ����ĳ��ȣ�
    // ����˵㲻�ô棬�����ڵݹ��ʱ����Ϊ��������
    nodes[p].reset(p, srcArray[0][l], l, r);
    if (l < r) {
        int mid = (l + r) >> 1;
        // �ݹ鴴�����Ҷ��ӽ��
        treeNode::segtree_build(p<<1, l, mid);
        treeNode::segtree_build(p<<1|1, mid+1, r);
        nodes[p].updateFromSon();
    }
}

void treeNode::segtree_insert(int p, int l, int r, int x, int y, ValueType val) {
    if( !is_intersect(l, r, x, y) ) {
        return ;
    }
    if( is_contain(l, r, x, y) ) {
        if( nodes[p].addValue(1) ) {
            return ;
        }
    } 
    nodes[p].giveLazyToSon();
    int mid = (l + r) >> 1; 
    treeNode::segtree_insert(p<<1, l, mid, x, y, val);
    treeNode::segtree_insert(p<<1|1, mid+1, r, x, y, val);
    nodes[p].updateFromSon();
}

void treeNode::segtree_query(int p, int l, int r, int x, int y, treeNode& ans) {
    if( !is_intersect(l, r, x, y) ) {
        return ;
    }
    if( is_contain(l, r, x, y) ) {
        ans.mergeQuery(p);
        return;
    }
    nodes[p].giveLazyToSon();
    int mid = (l + r) >> 1; 
    treeNode::segtree_query(p<<1, l, mid, x, y, ans);
    treeNode::segtree_query(p<<1|1, mid+1, r, x, y, ans);
    nodes[p].updateFromSon();
} 


int n, m;

int main() {
    int i, j;
    int t = 0;
    while( scanf("%d", &n) != EOF ) {
        for(i = 1; i <= n; i++) {
            scanf("%I64d", &srcArray[0][i] );
        }
        maxDepth = 0;
        bool flag = true;
        while(flag) {
            flag = false;
            maxDepth ++;
            for(i = 1; i <= n; i++) {
                ValueType v;
                v = (ValueType)sqrt(1.0 * srcArray[maxDepth-1][i]);
                if ( (v+1) * (v+1) == srcArray[maxDepth-1][i] ) {
                    v++;
                }
                if(v > 1) {
                    flag = true;
                }
                srcArray[maxDepth][i] = v;
            }
        }
        
        for(i = 0; i <= maxDepth; i++) {
            for(j = 1; j <= n; j++) {
                srcArray[i][j] += srcArray[i][j-1];
            }
        }
        
        treeNode::segtree_build(1, 1, n);
        printf("Case #%d:\n", ++t);
        scanf("%d", &m);
        while( m-- ) {
            int op, a, b;
            scanf("%d %d %d", &op, &a, &b); 
            if(a > b) swap(a, b);
            if ( op == 0 ) {
                treeNode::segtree_insert(1, 1, n, a, b, 0);
            }else {
                treeNode ans;
                treeNode::segtree_query(1, 1, n, a, b, ans);
                printf("%I64d\n", ans.sum);
            }
        }
        puts("");
    }
    return 0;
}

/*
10
1 2 3 4 5 6 7 8 9 10
5
0 1 10
1 1 10
1 1 5
0 5 8
1 4 8

Case #1:
19
7
6
*/
