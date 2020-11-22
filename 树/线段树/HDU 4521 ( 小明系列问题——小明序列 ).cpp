/*
    ���⣺����N(N <= 10^5)����������a[N](0<=a[i]<=10^5)��һ��d(d <=10^5),��һ��������
���������������������Ĳ����d�������е�����ȡ� 
    ��⣺�߶���+DP��
    ״̬dp[i]��ʾ��i��Ԫ�ؽ�β������i��Ԫ��ѡ�е���󳤶ȡ�
    ״̬ת�Ʒ��̣�dp[i] = {dp[j] + 1 | i-j>d && a[i]-a[j]>0 }
    ��ô���������У����Ԫ��ǰһ��Ԫ��Ϊa[j]������Ҫ���� i - j > d�� 
    ����������������j�У���dp[j]�����ֵΪT����ôdp[i] = T+1��
    ���ǣ����߶���ά��������ֵ���������������+1�������߶���������Ϊ[1, 100001]�� 
    
    �߶�����DP�໥ά�����߶������������� 
    ���룺ѭ��ö��i���� j=i-d-1�����j>=0����dp[j]���뵽�߶���a[i]��λ�á�
    ��ѯ��������[1, a[i]-1]�������ֵT�����û����T=0��Ȼ�����dp[i] = T+1��
     ѭ��N�κ�max{dp[i]| 0<=i<N}�������Ĵ𰸡� 
*/
#include <iostream>

using namespace std;

#define MAXN 100010
#define MAXNODES (1<<18)
#define INF 100000000
/////////////////////////////////////////////////////
//////////////////�߶���-������ֵ//////////////////// 
/////////////////////////////////////////////////////

typedef int TypeVal;
struct Node {
    Node* son[2];
    TypeVal min, max;
    
    Node() {
        reset();
    } 
    
    void reset() {
        min =  INF;
        max = -INF;
        son[0] = son[1] = NULL;
    }
    
    void update(TypeVal v) {
        if(v < min) {
            min = v;
        }
        if(v > max) {
            max = v;
        }
    }
    
    void update(Node* val) {
        if(val->min < min) {
            min = val->min;
        }
        if(val->max > max) {
            max = val->max;
        }
    }
};
typedef Node* NodePtr;

class SegTree {
    NodePtr nodes;

    int nodeCount;
    int intervalLength;
    
    NodePtr get_node(); 
    void insert(NodePtr&, int, int, int, int, TypeVal);
    void query(NodePtr&, int, int, int, int, NodePtr);
public:
    NodePtr treeRoot;
    SegTree () {
        // MAXNODESΪ��MAXN������С2���ݵ����� 
        nodes = new Node[MAXNODES];
    }
    
    ~SegTree() {
        delete [] nodes; 
    } 
    void build_tree(int len);
    void insert_tree(int l, int r, TypeVal val);
    void query_tree(int l, int r, NodePtr ans);
    
    static SegTree& Instance() {
        static SegTree inst;
        return inst;
    }
};

NodePtr SegTree::get_node() {
    return &nodes[nodeCount++];
}

/*
    ������[l, r]���뵽 ��rootΪ��������������Ϊ [treeL, treeR]��  
*/
void SegTree::insert(NodePtr& root, int treeL, int treeR, int l, int r, TypeVal val) {
    // �����޽������Ƿ����� 
    if(treeR < l || r < treeL) {
        return ;
    }
    // ���������δ���壬�������½�� 
    if(root == NULL) {
        root = get_node();
        root->reset();
    }
    // �������Ž� 
    root->update(val);
    
    // Ҷ�ӽ�� 
    if(treeL == l && treeR == r) {
        return ;
    }
    
    int treeMid = (treeL + treeR) >> 1;
    insert(root->son[0], treeL, treeMid, l, r, val);
    insert(root->son[1], treeMid+1, treeR, l, r, val);
}

void SegTree::query(NodePtr& root, int treeL, int treeR, int l, int r, NodePtr ans) {
    // �����޽������Ƿ����� 
    if(treeR < l || r < treeL) {
        return ;
    }
    // ��ǰ�����������ݣ��޷����� 
    if(root == NULL) {
        return ;
    }
    
    // ��ȫ������������ֵ 
    if(l <= treeL && treeR <= r) {
        ans->update(root);
        return ;
    }
    int treeMid = (treeL + treeR) >> 1;
    query(root->son[0], treeL, treeMid, l, r, ans);
    query(root->son[1], treeMid+1, treeR, l, r, ans);
}

void SegTree::build_tree(int len) {
    intervalLength = len;
    nodeCount = 0;
    treeRoot = NULL;
}

void SegTree::insert_tree(int l, int r, TypeVal val) {
    insert(treeRoot, 1, intervalLength, l, r, val);
}

void SegTree::query_tree(int l, int r, Node* ans) {
    query(treeRoot, 1, intervalLength, l, r, ans);
}

int n, d;
int a[MAXN];
int dp[MAXN];

int main() {
    int i, j;
    //freopen("in.txt", "r", stdin);
    //freopen("my.out.txt", "w", stdout); 
    while(scanf("%d %d", &n, &d) != EOF) {
        SegTree& st = SegTree::Instance();
        st.build_tree(100001);
        int Max = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            ++a[i];
            j = i-d-1;
            if(j >= 0) {
                st.insert_tree(a[j], a[j], dp[j]);
            }
            Node node;
            st.query_tree(1, a[i]-1, &node);
            
            dp[i] = 1;
            if(node.max != -INF) {
                dp[i] += node.max;
            }
            
            if( dp[i] > Max ) {
                Max = dp[i];
            }
        }
        printf("%d\n", Max);
    }
    return 0;
} 
