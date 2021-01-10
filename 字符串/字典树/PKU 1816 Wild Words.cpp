/*
    1WA  ����±���Ҫ����
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

typedef int TrieData;                        // �޸ĵ� 1
typedef const char ValueType;                // �޸ĵ� 2

const int NODECACHES = 600100;               // �޸ĵ� 3
const int TREENODE = 28;                     // �޸ĵ� 4
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


    void query_match(TrieNode *pkNow, int vSize, ValueType v[], int depth, int *ans, int& ansSize);
private:
    int genNode() {
        TrieNode *pkNode = &(nodes_[nodeId_]);
        pkNode->reset();
        return nodeId_++;
    }

    int getSonIndex(ValueType v) {
        if (v == '?') return 26;
        if (v == '*') return 27;
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

int pre[100010];

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
        if (pkNow->getData() != TRIEDATA_INIT) {
            pre[data] = pkNow->getData();
        }
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

void TrieTree::query_match(TrieNode *pkNow, int vSize, ValueType v[], int depth, int *ans, int& ansSize) {
    if (pkNow == NULL) {
        pkNow = root();
    }
    int sonIndex = getSonIndex('*');
    if (pkNow->hasSon(sonIndex)) {
        TrieNode *pkSon = node(pkNow->getSon(sonIndex));
        for (int i = depth; i <= vSize; ++i) {
            query_match(pkSon, vSize, v, i, ans, ansSize);
        }
    }

    if (depth == vSize) {
        if (pkNow->getData() != TRIEDATA_INIT) {
            ans[ansSize++] = pkNow->getData();
        }
        return;
    }
    sonIndex = getSonIndex(v[depth]);

    if (pkNow->hasSon(sonIndex)) {
        query_match(node(pkNow->getSon(sonIndex)), vSize, v, depth + 1, ans, ansSize);
    }

    sonIndex = getSonIndex('?');
    if (pkNow->hasSon(sonIndex)) {
        query_match(node(pkNow->getSon(sonIndex)), vSize, v, depth + 1, ans, ansSize);
    }


}

char patternStr[10];
char matchStr[100];
int ans[100010], ansSize;
int ansHash[100010], ansCase = 0;

int main() {
    int n, m;
    TrieTree tt(NODECACHES);

    while(scanf("%d %d", &n, &m)!=EOF)
    {
        tt.initialize();
        memset(pre, -1, sizeof(pre));
        for (int i = 0; i < n; ++i) {
            scanf("%s", patternStr);
            tt.insert(strlen(patternStr), patternStr, i, TNTT_LEAF);
        }


        while (m--) {
            ++ansCase;
            scanf("%s", matchStr);
            ansSize = 0;
            tt.query_match(NULL, strlen(matchStr), matchStr, 0, ans, ansSize);

            if (ansSize == 0) {
                printf("Not match\n");
            }
            else {
                for (int i = ansSize - 1; i >= 0; --i) {
                    if (ansHash[ans[i]] < ansCase) {
                        int now = ans[i];
                        ansHash[now] = ansCase;
                        while (pre[now] != -1) {
                            now = pre[now];
                            ans[ansSize++] = now;
                            ansHash[now] = ansCase;
                        }
                    }
                }

                sort(ans, ans + ansSize);
                for (int i = 0; i < ansSize; ++i) {
                    if (i) {
                        if (ans[i] == ans[i - 1]) {
                            continue;
                        }
                        printf(" ");
                    }

                    printf("%d", ans[i]);
                }
                puts("");
            }
        }

    }
    return 0;
}

/*
7 5
t*
?h*s
??e*
*s
?*e
*??uk*
*??uk*
this
the
an
is
ggukjdfgfffgfds

11 50
t*
?h*s
??e*
*??uk*
*s
?*e
*s
*s
*s
*??uk*
*??uk*

*/