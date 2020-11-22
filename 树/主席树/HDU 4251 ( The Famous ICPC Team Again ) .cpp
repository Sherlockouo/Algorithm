#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

#define MAXN 100010
#define MAXQ 100010
#define LOGMAXN 17
#define MAXNODE 1990000

// MAXNODE ��ʾ�ܽ�����������¼��������
//         1��MAXN*2           ��һ�ÿ����Ľ����
//         2��MAXN*LOGMAXN     ��N������ÿ�����¼��� LOGMAXN �����

struct treeNode {
    int data;                // ������ 
    int lson, rson;          // ���Ҷ��ӱ��       
    // int l, r;             // ���������ڵݹ��ʱ����Լ������������Ϊ�˽�ʡ�ռ䲻�豣�� 
    
    treeNode() {
        reset();
    }
    
    void reset() {
        data = 0;
        lson = rson = 0;
    }
    
    void setson(int _lson, int _rson) {
        lson = _lson;
        rson = _rson;
    }
    
}tNode[MAXNODE];     // ��ϯ����� 
int T[MAXN];         // T[i]��ʾ��i����ϯ���ĸ�����ţ��±��1-N������ T[0] ָ�����һ��������ȫΪ0�Ŀ������� 
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
    getNode(x)->reset();     // ���ڶ�case�������������
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
    newroot->data = oldroot->data + cnt;
    
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
        }else {
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
        newroot->data = oldroot->data + cnt;
    }

    return ret;
}

//ǰ�����ܣ�ģ���� ####################################################################################### 
//########################################################################################################

int a[MAXN], b[MAXN], bs;
int n, m;

int getIdx(int val) {
    int l = 1, r = L;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(val == b[mid]) return mid;
        
        if(val > b[mid]) {
            l = mid + 1;
        }else {
            r = mid - 1;
        }
    }
}

void build() {
    int i;
    // �������� 
    build_cmtree(T[0], 1, L);
    for(i = 0; i < n; i++) {
        T[i+1] = insert_cmtree(T[i], getIdx(a[i]), 1);
    }    
}

int query(int s, int t, int l, int r, int k) {
    if(l == r) {
        return l;
    }
    int mid = (l + r) >> 1;
    int cnt = getNode(getNode(t)->lson)->data - getNode(getNode(s)->lson)->data;
    if(k > cnt) {
        return query(getNode(s)->rson, getNode(t)->rson, mid+1, r, k-cnt);
    }else {
        return query(getNode(s)->lson, getNode(t)->lson, l, mid, k);
    }
}

int main() {
    //printf("%d\n", sizeof( treeNode ) );
    int i;
    int t, cases = 0;
    while( scanf("%d", &n) != EOF ) {
        //n = 100000;
        init();
        bs = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            //a[i] = i;
            b[++bs]    = a[i];
        }
        sort(&b[1], &b[1] + bs);
        for(i = 2; i <= bs; i++) {
            if(b[i] != b[i-1]) {
                b[++L] = b[i];
            }
        }
        build(); //printf("%d\n", totalNodes);
        printf("Case %d:\n", ++cases);
        scanf("%d", &m);
        for(i = 0; i < m; i++) {
            int A, B;
            scanf("%d %d", &A, &B);
            int idx = query(T[A-1], T[B], 1, L, (B-A)/2+1 );
            printf("%d\n", b[idx]);
        }

    }
    return 0;
}
