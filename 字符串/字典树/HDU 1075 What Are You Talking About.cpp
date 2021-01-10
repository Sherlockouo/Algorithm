/*
    1 MLE    TrieData  ���� string�������������
    2 TLE    ��Ϊ���������鿪С�ˣ������±�Խ�絼�� ��ʱ
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

typedef int TrieData;                        // �޸ĵ� 1
typedef const char ValueType;                // �޸ĵ� 2

const int NODECACHES = 4000000;              // �޸ĵ� 3
const int TREENODE = 26;                     // �޸ĵ� 4
const int TRIEHASH_BASE = 'a';               // �޸ĵ� 5
const TrieData TRIEDATA_INIT = -1;           // �޸ĵ� 6
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
    if (data_ == TRIEDATA_INIT) {
        data_ = d;
    }
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

char from[3032], to[3002];
char lines[3010], trans[3010];
int transSize = 0;

char words[2000010][12];
int wordSize = 0;

void processTrans(TrieTree &tt) {
    trans[transSize] = '\0';
    if (transSize > 0) {
        int len = strlen(trans);
        TrieData idx = tt.query(len, trans);
        if (idx != TRIEDATA_INIT) {
            strcpy(trans, words[idx]);
        }
        printf("%s", trans);
        transSize = 0;
    }
}

int main() {
    TrieTree tt(NODECACHES);
    tt.initialize();

    scanf("%s", from);
    while (scanf("%s", to) != EOF) {
        if (strcmp(to, "END") == 0) break;
        scanf("%s", from);
        strcpy(words[wordSize], to);
        tt.insert(strlen(from), from, wordSize++, TrieNodeInsertType::TNTT_LEAF);
    }
    scanf("%s", from);
    getchar();
    while (gets(lines)) {
        if (strcmp(lines, "END") == 0) break;
        transSize = 0;
        for (int i = 0; lines[i]; ++i) {
            if (lines[i] >= 'a' && lines[i] <= 'z') {
                trans[transSize++] = lines[i];
            }
            else {
                processTrans(tt);
                printf("%c", lines[i]);
            }
        }

        processTrans(tt);
        puts("");
    }

    return 0;
}