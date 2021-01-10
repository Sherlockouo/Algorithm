/*
    ���Ҹ������ַ����ֵ����ж��ٸ�ǰ׺
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

typedef int TrieData;                        // �޸ĵ� 1
typedef const char ValueType;                // �޸ĵ� 2

const int NODECACHES = 300020;              // �޸ĵ� 3
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


public:
    virtual void insert(int vSize, ValueType v[], TrieData data, TrieNodeInsertType tntt);
    virtual TrieData query(int vSize, ValueType v[]);                     // �޸ĵ� 8
    virtual void delete_prefex(int vSize, ValueType v[]);

private:
    int genNode() {
        TrieNode *pkNode = &(nodes_[nodeId_]);
        pkNode->reset();
        return nodeId_++;
    }
    TrieNode *Node(int idx) {
        return &(nodes_[idx]);
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
    TrieNode *pkNow = Node(root_);
    for (int i = 0; i < vSize; ++i) {
        // 1. ���Ҷ�Ӧ��ĸ���ڵ��ӽ���Ƿ���ڣ�û���򴴽�
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            pkNow->setSon(sonIdx, genNode());
        }
        // 2. �����ӽ��
        pkNow = Node(pkNow->getSon(sonIdx));

        // 3. ������ڲ��������ͣ�����±��
        if (tntt == TrieNodeInsertType::TNTT_INSIDE) {
            pkNow->updateData(data);
        }
    }
    // 4. �����Ҷ�Ӳ������ͣ�����±��
    if (tntt == TrieNodeInsertType::TNTT_LEAF) {
        pkNow->updateData(data);
    }

}

TrieData TrieTree::query(int vSize, ValueType v[]) {
    // ���Ҷ�Ӧ�ֵ��У��Ƿ����ַ�����ǰ׺���� v[]
    TrieNode *pkNow = Node(root_);
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return TRIEDATA_INIT;
        }
        pkNow = Node(pkNow->getSon(sonIdx));
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
    TrieNode *pkNow = Node(root_);
    for (int i = 0; i < vSize; ++i) {
        int sonIdx = getSonIndex(v[i]);
        // ���ü������������н��ɾ��
        TrieNode *pkSon = Node(pkNow->getSon(sonIdx));
        pkSon->updateData(-nCnt);
        if (pkSon->getData() == TRIEDATA_INIT) {
            pkNow->setSon(sonIdx, TRIENODE_NULL);
            return;
        }
        pkNow = pkSon;
    }
}

struct barcodes {
    int idx;
    double val;
    void read(int _i){
        idx = _i;
        scanf("%lf", &val);
    }
    bool operator < (const barcodes& o) {
        return val < o.val;
    }
}B[8];

int main() {
    int t;
    int i;
    int n, m, K;

    TrieTree tt(NODECACHES);

    while (scanf("%d %d", &n, &m) != EOF) {
        tt.initialize();

        
        for (int i = 0; i < n; ++i) {
            char ch[35];
            scanf("%s", ch);
            tt.insert(strlen(ch), ch, 1, TrieNodeInsertType::TNTT_INSIDE);
        }

        long long ans = 0;
        while (m--) {
            scanf("%d", &K);
            char s[100];
            int slen = 0;

            for (int i = 0; i < K; ++i) {
                for (int j = 0; j < 8; ++j) {
                    B[j].read(7-j);
                }
                sort(B, B + 8);
                int ans = 0;
                for (int j = 1; j < 8; ++j) {
                    double l = B[j].val * 95;
                    double r = B[j - 1].val * 105;
                    if (l - r > 1e-10) {
                        ans = j;
                        break;
                    }
                }
                // ���� 1 �Ĳ���
                char c = 0;
                for (int j = ans; j < 8; ++j) {
                    c |= (1 << B[j].idx);
                }
                s[slen++] = c;
            }
            s[slen] = '\0';
            ans += tt.query(slen, s);

        }

        printf("%lld\n", ans);
    }

    return 0;
}