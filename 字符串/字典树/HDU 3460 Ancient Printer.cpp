/*
�ֵ��� + ����DP

2 WA   ��Ҷ�ӽ���жϳ������⣬��ĳ���ַ�������һ��ǰ׺ʱ����������Ҷ�ӽ�㣻
�Ƿ���Ҷ�ӽ��Ӧ�ô��Ƿ�ӵ���ӽ�����ж�

2 WA   ���λ��ظ����м����ظ����ξ�Ҫ print ����

*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

typedef int TrieData;                        // �޸ĵ� 1
typedef const char ValueType;                // �޸ĵ� 2

const int NODECACHES = 500020;               // �޸ĵ� 3
const int TREENODE = 26;                     // �޸ĵ� 4
const int TRIEHASH_BASE = 'a';               // �޸ĵ� 5
const TrieData TRIEDATA_INIT = 0;            // �޸ĵ� 6
const int TRIENODE_NULL = -1;

// �ֵ��������
class TrieNode {
private:
    TrieData data_;
    // ע���������ǽ���ڴ�ص��±꣬��ȴ�ָ��ĺô��ǣ��ֽ�����һ��
    int nodes_[TREENODE];

public:
    // ģ���в���Ľӿ�
    inline void setSon(int sonIdx, int son) {
        nodes_[sonIdx] = son;
    }
    inline int getSon(int sonIdx) {
        return nodes_[sonIdx];
    }
    inline bool hasSon(int sonIdx) {
        // ��㷶Χ�ж�
        if (sonIdx < 0 || sonIdx >= TREENODE) {
            return false;
        }
        return nodes_[sonIdx] != TRIENODE_NULL;
    }
    inline void reset() {
        resetData();
        memset(nodes_, TRIENODE_NULL, sizeof(nodes_));
    }

public:
    // ģ���и��ݲ�ͬ�����ͽ��������޸�        // �޸ĵ� 7
    void resetData();
    void updateData(TrieData d);
    TrieData getData();
};

void TrieNode::resetData() {
    data_ = TRIEDATA_INIT;
}


void TrieNode::updateData(TrieData d) {
    data_ += d;
}

TrieData TrieNode::getData() {
    return data_;
}

enum TrieNodeInsertType {
    TNTT_INSIDE = 0,
    TNTT_LEAF = 1,
};

// �ֵ�����
class TrieTree {
public:
    TrieTree(int nodeCacheCount);
    virtual ~TrieTree();
    void initialize() {
        nodeId_ = 0;
        root_ = genNode();
    }

    TrieNode *root() const { return node(root_); }
    TrieNode *node(int idx) const { return &(nodes_[idx]); }

public:
    virtual void insert(int vSize, ValueType v[], TrieData data, TrieNodeInsertType tntt);
    virtual TrieData query(int vSize, ValueType v[]);                     // �޸ĵ� 8
    virtual void delete_prefex(int vSize, ValueType v[]);


    virtual void query_prefix(int vSize, ValueType v[], char *ans);

    void gen_graph(int u, TrieNode *pkNow);
private:
    int genNode() {
        TrieNode *pkNode = &(nodes_[nodeId_]);
        pkNode->reset();
        return nodeId_++;
    }

    int getSonIndex(ValueType v) {
        return v - TRIEHASH_BASE;
    }
private:
    int nodeId_;
    int root_;
    TrieNode *nodes_;
};

TrieTree::TrieTree(int nodeCacheCount) : nodes_(NULL), root_(NULL), nodeId_(0) {
    nodes_ = new TrieNode[nodeCacheCount];
}

TrieTree::~TrieTree() {
    if (nodes_) {
        delete[] nodes_;
    }
}

void TrieTree::insert(int vSize, ValueType v[], TrieData data, TrieNodeInsertType tntt) {
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        // 1. ���Ҷ�Ӧ��ĸ���ڵ��ӽ���Ƿ���ڣ�û���򴴽�
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            pkNow->setSon(sonIdx, genNode());
        }
        // 2. �����ӽ��
        pkNow = node(pkNow->getSon(sonIdx));

        // 3. ������ڲ��������ͣ�����±��
        if (tntt == TNTT_INSIDE) {
            pkNow->updateData(data);
        }
    }
    // 4. �����Ҷ�Ӳ������ͣ�����±��
    if (tntt == TNTT_LEAF) {
        pkNow->updateData(data);
    }

}

TrieData TrieTree::query(int vSize, ValueType v[]) {
    // ���Ҷ�Ӧ�ֵ��У��Ƿ����ַ�����ǰ׺���� v[]
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return TRIEDATA_INIT;
        }
        pkNow = node(pkNow->getSon(sonIdx));
    }
    return pkNow->getData();
}

void TrieTree::delete_prefex(int vSize, ValueType v[]) {
    TrieData nCnt = query(vSize, v);
    if (nCnt == TRIEDATA_INIT) {
        // ��ѯ��һ�Σ���û�����ǰ׺��û�оͲ���ɾ��
        return;
    }
    // ɾ����Ӧǰ׺�������ַ���
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        // ���ü������������н��ɾ��
        TrieNode *pkSon = node(pkNow->getSon(sonIdx));
        pkSon->updateData(-nCnt);
        if (pkSon->getData() == TRIEDATA_INIT) {
            pkNow->setSon(sonIdx, TRIENODE_NULL);
            return;
        }
        pkNow = pkSon;
    }
}

void TrieTree::query_prefix(int vSize, ValueType v[], char *ans) {
    // ���Ҷ�Ӧ�ֵ��У�����ܹ���ʾ v[] ���ַ����洢�� ans ��
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return;
        }
        pkNow = node(pkNow->getSon(sonIdx));
        ans[i] = v[i];
        if (pkNow->getData() == 1) {
            ans[i + 1] = 0;
            return;
        }
    }
    ans[vSize] = 0;
}

// ����DP - 
// 0 dp[i][0] ��ʾ�ӽ��i�����������ӽ��ص�i����Сֵ
// 1 dp[i][1] ��ʾ�ӽ��i�����������ӽ�㣬��������Ҷ�ӽ�����Сֵ 
long long dp[NODECACHES][2];


void TrieTree::gen_graph(int u, TrieNode *pkNow) {
    // ��Ҷ�ӽ��

    dp[u][0] = 0;
    dp[u][1] = -1;

    for (int i = 0; i < TREENODE; ++i) {
        if (pkNow->hasSon(i)) {
            int v = pkNow->getSon(i);
            //printf("(%d -> %d)\n", u, v);
            gen_graph(v, node(v));
            dp[u][0] += (dp[v][0] + 2); // +2 ����Ϊ��ȥ����
        }
    }

    for (int i = 0; i < TREENODE; ++i) {
        if (pkNow->hasSon(i)) {
            int v = pkNow->getSon(i);
            long long s = (dp[u][0] - dp[v][0] - 2 + dp[v][1] + 1);  // ѡ������һ����㣬ȥ�˲�����
            if (dp[u][1] == -1 || s < dp[u][1]) {
                dp[u][1] = s;
            }
        }
    }

    if (dp[u][0] == 0 && dp[u][1] == -1) {
        dp[u][0] = 0;
        dp[u][1] = 0;
    }

    if (pkNow->getData()) {
        dp[u][0] += pkNow->getData();
        dp[u][1] += pkNow->getData();
    }


    //printf("%d %d %d\n", u, dp[u][0], dp[u][1]);

}

char str[100];

int main() {
    int t;
    int N;
    TrieTree tt(NODECACHES);

    while (scanf("%d", &N) != EOF) {
        tt.initialize();
        while (N--) {
            scanf("%s", str);
            tt.insert(strlen(str), str, 1, TrieNodeInsertType::TNTT_LEAF);
        }
        tt.gen_graph(0, tt.root());
        printf("%lld\n", dp[0][1]);
    }

    return 0;
}


/*
6
ade
adfg
bac
bad
baf
c
*/