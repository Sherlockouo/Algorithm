#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

typedef int TrieData;                        // �޸ĵ� 1
typedef const char ValueType;                // �޸ĵ� 2

const int NODECACHES = 1000020;              // �޸ĵ� 3
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
    void updateData(TrieData d);
    TrieData getData();
};

void TrieNode::resetData() {
    data_ = TRIEDATA_INIT;
}


void TrieNode::updateData(TrieData d) {
    if (data_ == TRIEDATA_INIT)
        data_ = d;
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

char names[100010][12];
char str[1000];
char cmd[2][1000];
int cmdsize[2];

int main() {

    TrieTree tt(NODECACHES);
    int namesize = 0;
    tt.initialize();

    while (gets(str)) {
        if (strcmp(str, "") == 0) {
            break;
        }
        cmdsize[0] = cmdsize[1] = 0;
        int idx = 0;
        for (int i = 0; str[i]; ++i) {
            if (str[i] == ' ') {
                cmd[idx][cmdsize[idx]] = '\0';
                idx++;
            }
            else {
                cmd[idx][cmdsize[idx]++] = str[i];
            }
        }
        cmd[idx][cmdsize[idx]] = '\0';

        strcpy(names[namesize], cmd[0]);
        tt.insert(strlen(cmd[1]), cmd[1], namesize, TNTT_LEAF);
        namesize++;
    }
    while (scanf("%s", str) != EOF) {
        TrieData v = tt.query(strlen(str), str);
        if (v == TRIEDATA_INIT) {
            printf("eh\n");
        }
        else {
            printf("%s\n", names[v]);
        }
    }

    return 0;
}