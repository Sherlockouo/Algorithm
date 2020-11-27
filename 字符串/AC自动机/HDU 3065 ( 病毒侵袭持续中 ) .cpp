/*
AC�Զ��� ģ�� 
��ģ���ھ���ʵ�ֵ�ʱ����Ҫ�޸����¼����ط���
     1��MAXC �Ĵ�С��ÿ����Ŀ���ַ���������һ��
     2��MAXQ �Ĵ�С��ÿ����Ŀ�Ľ��������һ�� (�ַ�����Ŀ*�ַ�������)
     3��bool isReceiving()����̬��ʵ�֡�
     4��ACNode����cnt��val������һ��ֻ��Ҫ�õ�����һ��������һ������ע�ͣ���ʡ�ռ䡣 
     5������failָ��ʱ����failָ���val״̬���ݸ���ǰ����ʱ����ʱ����+����ʱ����|������������� 
*/ 
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MAXC 26
#define MAXQ 50010

// ���ṹ
struct ACNode {
public:
    ACNode *fail;        // failָ�룬ָ��͵�ǰ����ĳ����׺ƥ����ǰ׺��λ��
    ACNode *next[MAXC];  // �ӽ��ָ��

    // ������Щ������Ҫ��Բ�ͬ��Ŀ�������ʵ���ע�ͣ���Ϊ�����ڴ��Բ���

    int id;              // �����(ÿ�������һ��Ψһ���)
    int val;             // ��ǰ��������failָ��ָ����Ľ�β������Ϣ�ļ���
    int cnt;               // ��Щ����ģʽ���п��ܻ��ж����������ͬ�ģ����Ǽ�����ʱ������

    void reset(int _id) {
        id = _id;
        val = 0;
        cnt = 0;
        fail = NULL;
        memset(next, 0, sizeof(next));
    }

    // ״̬���е� ����̬ �ĸ���
    // ģʽ��Ϊ���ܳ���(��������)��ʱ����н���̬
    bool isReceiving() {
        return false;
    }
};

// �����нṹ
// STL��Ч�ʲ��ҹ�ά����ĳЩOJ��Ч�ʼ��ͣ��Լ���װһ�ױȽϺ�
class ACNodeQueue {
public:
    ACNode *Data[MAXQ];
    int front, rear;

    bool empty() {
        return front == rear;
    }
    void clear() {
        front = rear = 0;
    }
    ACNode *pop() {
        ACNode *p = Data[front++];
        if(front == MAXQ) front = 0;
        return p;
    }
    void push(ACNode *node) {
        Data[rear++] = node;
        if(rear == MAXQ) rear = 0;
    }
};

// ��˹������������������˾ <-> ��Ϧ��
class ACAutoman {
public:
    /*�����ؽṹ*/
    ACNode* nodes[MAXQ];          // ��㻺�棬�����ڴ��ظ�������ͷţ���ʡʱ��
    int nodesMax;                 // ��������С����Զ�ǵ����� 
    ACNode *root;                 // �����ָ��
    int nodeCount;                // �������

    /*������ؽṹ*/
    int ID[256], IDSize;          // �������ĸ�ļ�HASH��ʹ�ý����������������
                                  // ���磺 ID['a']=0   ID['b']=1 ��������

    /*������ؽṹ*/
    ACNodeQueue Q;

public:
    ACAutoman() {
        nodesMax = 0;
    }
    // ��ʼ�������� �������
    void init() {
        nodeCount = 0;
        IDSize = 0;
        root = getNode();
        memset(ID, -1, sizeof(ID));
    }


    // ��ȡ���
    ACNode *getNode() {
        // �ڴ����������Ҫ�����µĽ��
        if(nodeCount >= nodesMax) {
            nodes[nodesMax++] = new ACNode();
        }
        ACNode *p = nodes[nodeCount];
        p->reset(nodeCount++);
        return p;
    }

    // ��ȡ��ĸ��Ӧ��ID
    int getCharID(unsigned char c, int needcreate) {
        if(!needcreate) return ID[c];
        if(ID[c] == -1) ID[c] = IDSize++;
        return ID[c];
    }

    // ��ÿ��ģʽ��str����insert�����������ֵ���
    void insert(char *str, int val) {
        ACNode *p = root;
        int id;
        for(int i = 0; str[i]; i++) {
            // ��ȡ��ĸ��Ӧ�Ĺ�ϣID
            id = getCharID(str[i], true);
            // ����ӽ���Ƿ���ڣ��������򴴽��µ��ӽ��
            if(p->next[id] == NULL) p->next[id] = getNode();
            p = p->next[id];
        }
        // ��������ʵĽ�β����һ�����
        p->val |= val;     // ע���п�������ͬ�Ĵ�
        p->cnt ++;
    }

    // ����ʧ��ָ�롢trieͼ 
    void construct_trie() {
        ACNode *now, *son, *tmp;
        
        root->fail = NULL;
        Q.clear();
        Q.push(root);
        
        // ������ÿһ��Ľ���failָ��
        // ��ÿ����������ϣ���֤�����к�̶��Ѿ�������� 
        while( !Q.empty() ) {
            now = Q.pop();
            
            if(now->fail) {
                // ������Ҫ���������
                // Ŀ���ǽ�failָ���״̬��Ϣ���ݸ���ǰ���
                // now->val += now->fail->val;
                //now->val |= now->fail->val;

                // �����ǰ����Ǹ�����̬����ô�������к�̶��ǻص�����
                if(now->isReceiving()) {
                    for(int i = 0; i < IDSize; i++) {
                        now->next[i] = now;
                    }
                    continue;
                }
            }
            // ���ȣ����ǰѵ�ǰ���now��i�ź�̼�Ϊson[i]
            //   i) ���son[i]�����ڣ�����ָ�� ��ǰ���now��failָ��ָ�����i�ź��(��֤һ���Ѿ��������)��
            //   2) ���son[i]���ڣ�������failָ��ָ�� ��ǰ���now��failָ��ָ�����i�ź��(��֤һ���Ѿ��������)��
            for(int i = 0; i < IDSize; i++) {
                son = now->next[i];
                tmp = (now == root) ? root : now->fail->next[i];
                if(son == NULL) {
                    now->next[i] = tmp;
                }else {
                    son->fail = tmp;
                    Q.push(son);
                }
            }
        }
    }

    // ѯ��str������Щģʽ��
    int query_str(char *str, int *ans) {
        ACNode *p = root, *tmp = NULL;
        int id;
        int cnt = 0;
        
        for(int i = 0; str[i]; i++) {
            id = getCharID(str[i], false);
            if(id == -1) {
                // ��ǰ���ʴ���û�г��ֹ���ֱ�ӻص�ƥ��֮��
                p = root;
                continue;
            }
            p = p->next[id];
            tmp = p;
            while(tmp != root && tmp->cnt != -1) {
                if(tmp->cnt) {
                    ans[ tmp->val ] += tmp->cnt; 
                }
                tmp = tmp->fail;
            }
        }
        return cnt;
    }
}AC;

int N;
char str[2000010];
char mot[1010][55];
int ans[1010];

int main() {
    int i;
    while(scanf("%d", &N) != EOF) {
        getchar();
        AC.init();
        for(i = 1; i <= N; i++) {
            gets(mot[i]);
            AC.insert(mot[i], i);
        }
        AC.construct_trie();
        gets(str);
        memset(ans, 0, sizeof(ans));
        AC.query_str(str, ans);
        for(i = 1; i <= N; i++) {
            if(ans[i]) {
                printf("%s: %d\n", mot[i], ans[i]);
            }
        }
    }
    return 0;
}

/*
5
ab gf
.,;;
/.;
...
o0p
1
...,;;ab gf

*/
