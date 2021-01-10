/*
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;


char mobiles[][6] = {
    "",
    "",
    "abc", // 2
    "def", // 3
    "ghi", // 4
    "jkl", // 5
    "mno", // 6
    "pqrs",// 7
    "tuv", // 8
    "wxyz" // 9
};

typedef int TrieData;                        // �޸ĵ� 1
typedef const char ValueType;                // �޸ĵ� 2

const int NODECACHES = 60020;                // �޸ĵ� 3
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
    void updateData(TrieData& d);
    TrieData getData();
};

void TrieNode::resetData() {
    data_ = TRIEDATA_INIT;
}


void TrieNode::updateData(TrieData& d) {
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
    virtual TrieData query_dfs(TrieNode* pkNode, int vSize, ValueType v[], int vDepth);
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

TrieData TrieTree::query_dfs(TrieNode* pkNow, int vSize, ValueType v[], int vDepth) {
    if (vDepth == 0) {
        pkNow = Node(root_);
    }
    if (vSize == vDepth) {
        return pkNow->getData();
    }

    int clen = strlen(mobiles[v[vDepth] - '0']);
    TrieData s = 0;
    for (int i = 0; i < clen; ++i) {
        char c = mobiles[v[vDepth] - '0'][i];
        int sonIdx = getSonIndex(c);
        if (!pkNow->hasSon(sonIdx)) {
            continue;
        }
        s += query_dfs(Node(pkNow->getSon(sonIdx)), vSize, v, vDepth + 1);
    }
    return s;
}

void TrieTree::delete_prefex(int vSize, ValueType v[]) {
    // ɾ����Ӧǰ׺�������ַ���
    TrieNode *pkNow = Node(root_);
    TrieNode *pkPre = NULL;
    for (int i = 0; i < vSize; ++i) {

        int sonIdx = getSonIndex(v[i]);
        if (!pkNow->hasSon(sonIdx)) {
            return;
        }
        pkPre = pkNow;
        pkNow = Node(pkNow->getSon(sonIdx));
    }
    if (pkPre) {
        int sonIdx = getSonIndex(v[vSize - 1]);
        pkPre->setSon(sonIdx, TRIENODE_NULL);
    }
}

char cmd[2][55];
int n, m;

char digits[5010][10];
char words[5010][10];

int main() {
    TrieTree tt(NODECACHES);

    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; ++i) {
            scanf("%s", digits[i]);
        }

        for (int i = 0; i < m; ++i) {
            scanf("%s", words[i]);
        }

        tt.initialize();

        for (int i = 0; i < m; ++i) {
            tt.insert(strlen(words[i]), words[i], 1, TrieNodeInsertType::TNTT_INSIDE);
        }

        for (int i = 0; i < n; ++i) {
            int len = strlen(digits[i]);


            printf("%d\n", tt.query_dfs(NULL, len, digits[i], 0));
        }
    }
    return 0;
}