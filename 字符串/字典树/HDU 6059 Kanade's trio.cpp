/*
    6   TLE   ����������ر��ʱ
    ������ 500000 * 64 �����飬ȡԪ�ص�ʱ��ǳ���ʱ��
*/
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

typedef int TrieData;
typedef long long AnsType;                   // �޸ĵ� 1
typedef int ValueType;                       // �޸ĵ� 2
const int MAXBIT = 30;                       // �޸ĵ� 3
const int NODECACHES = MAXBIT * 500010;      // �޸ĵ� 4
const int TREENODE = 2;                      // �޸ĵ� 5
const int TRIEHASH_BASE = 0;                 // �޸ĵ� 6
const int TRIEDATA_INIT = 0;                 // �޸ĵ� 7
const int TRIENODE_NULL = -1;

#define samebit(i) ((v & ((ValueType)1 << i)) ? 1 : 0)
#define diffbit(i) ((v & ((ValueType)1 << i)) ? 0 : 1)


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
        /*if (sonIdx < 0 || sonIdx >= TREENODE) {
        return false;
        }*/
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
    TrieNode *root() const { return node(root_); }
    TrieNode *node(int idx) const { return &(nodes_[idx]); }

    // ���� 1 ��ֵΪ v ����
    virtual void insert_value(ValueType v);
    // ɾ�� 1 ��ֵΪ v ����
    virtual void delete_value(ValueType v);
    // ��ѯֵΪ v �����ĸ���
    virtual TrieData query_value(ValueType v);
    // ��ѯ�ֵ����к͸�����ֵ XOR �������Ǹ���
    virtual void query_xor_max(ValueType v, AnsType &ans);

    AnsType jik();
    AnsType ijk();
private:
    int genNode() {
        TrieNode *pkNode = &(nodes_[nodeId_]);
        pkNode->reset();
        return nodeId_++;
    }

    bool hasSon(TrieNode *pkNow, int sonIdx) {
        if (pkNow->hasSon(sonIdx)) {
            // û��ɾ���������ֱ�� return ����
            return true;

            TrieNode *pkSon = node(pkNow->getSon(sonIdx));
            if (pkSon->getData() != TRIEDATA_INIT) {
                return true;
            }
        }
        return false;
    }

    void addSon(TrieNode *pkNow, int sonIdx) {
        if (!pkNow->hasSon(sonIdx)) {
            pkNow->setSon(sonIdx, genNode());
        }
    }

    int sonCount(TrieNode *pkNow, int sonIdx) {
        if (!hasSon(pkNow, sonIdx)) {
            return 0;
        }
        TrieNode *pkSon = node(pkNow->getSon(sonIdx));
        return pkSon->getData();
    }
private:
    int nodeId_;
    int root_;
    TrieNode *nodes_;
};

TrieTree::TrieTree(int nodeCacheCount) : nodes_(NULL), root_(0), nodeId_(0) {
    nodes_ = new TrieNode[nodeCacheCount];
}

TrieTree::~TrieTree() {
    if (nodes_) {
        delete[] nodes_;
    }
}

// �����λ��ʼ���� 01�ֵ���
void TrieTree::insert_value(ValueType v) {
    TrieNode *pkNow = root();
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int sonIdx = samebit(i);
        addSon(pkNow, sonIdx);
        pkNow = node(pkNow->getSon(sonIdx));
        pkNow->updateData(1);
    }
}

// ��ѯ 01�ֵ��� �� v ���ֳ��ֵĸ���
TrieData TrieTree::query_value(ValueType v) {
    TrieNode *pkNow = root();
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int sonIdx = samebit(i);
        if (!hasSon(pkNow, sonIdx)) {
            return TRIEDATA_INIT;
        }
        pkNow = node(pkNow->getSon(sonIdx));
    }
    return pkNow->getData();
}

// �����λ��ʼ���� ɾ�� 01�ֵ��� �� v ����һ�� 
void TrieTree::delete_value(ValueType v) {
    TrieData nCnt = query_value(v);
    if (nCnt == TRIEDATA_INIT) {
        return;
    }
    TrieNode *pkNow = root();
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int sonIdx = samebit(i);
        pkNow = node(pkNow->getSon(sonIdx));
        pkNow->updateData(-1);
    }
}

// �Ӹ���㿪ʼ�� 32 ��
// �����������ʣ������Һ͵�ǰ���ĵ�iλ�෴����������Ҳ���������ͬ�ģ�
void TrieTree::query_xor_max(ValueType v, AnsType &ans) {
    TrieNode *pkNow = root();
    ans = 0;
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int sonIdx = diffbit(i);
        if (hasSon(pkNow, sonIdx)) {
            ans |= ((ValueType)1 << i);
        }
        else {
            sonIdx = 1 - sonIdx;
        }
        pkNow = node(pkNow->getSon(sonIdx));
    }
}

int n, A[500010];

int sum[32][2];

AnsType TrieTree::jik() {
    int i, t, k;
    AnsType ans = 0;
    initialize();

    // Ԥ���� ǰi�����У���tλΪ[0,1]�����ĸ����ܺ�
    memset(sum, 0, sizeof(sum));

    for (int i = 1; i <= n; ++i) {
        for (t = 0; t < MAXBIT; ++t) {
            int v = A[i];
            int x = samebit(t);
            sum[t][x] = sum[t][x] + 1;
            sum[t][(1 - x)] = sum[t][(1 - x)];
        }
    }

    for (i = n; i >= 1; i--) {
        int v = A[i];

        TrieNode *pkNow = root();
        for (t = MAXBIT - 1; t >= 0; --t) {

            int sonIdx = samebit(t);
            int ksbit = (sonIdx ^ 1);   // k's  t bit

            int sumtmp = sum[t][sonIdx];
            ValueType tmp = sonCount(pkNow, ksbit);
            if (tmp && sumtmp)
                ans += tmp * sumtmp;

            if (hasSon(pkNow, sonIdx)) {
                pkNow = node(pkNow->getSon(sonIdx));
            }
            else {
                break;
            }
        }

        for (t = 0; t < MAXBIT; ++t) {
            int x = samebit(t);
            sum[t][x] = sum[t][x] - 1;
            sum[t][(1 - x)] = sum[t][(1 - x)];
        }

        insert_value(v);
    }

    return ans;

}

AnsType TrieTree::ijk() {
    AnsType ans = 0;

    initialize();
    memset(sum, 0, sizeof(sum));

    for (int k = 1; k <= n; ++k) {
        int v = A[k];

        TrieNode *pkNow = root();
        for (int t = MAXBIT - 1; t >= 0; --t) {

            int sonIdx = samebit(t);
            int iBit = 1 - sonIdx;

            int sumtmp = sum[t][iBit];
            ValueType tmp = sonCount(pkNow, iBit);
            if (tmp && sumtmp)
                ans += tmp * sumtmp;

            if (hasSon(pkNow, sonIdx)) {
                pkNow = node(pkNow->getSon(sonIdx));
            }
            else {
                break;
            }

        }

        for (int t = 0; t < MAXBIT; ++t) {
            int x = samebit(t);
            sum[t][x] = sum[t][x] + 1;
            sum[t][(1 - x)] = sum[t][(1 - x)];
        }


        insert_value(v);
    }


    int fg;
    fg = 1;
    return ans - jik();
}


int main() {
    int t;
    TrieTree tt(NODECACHES);

    scanf("%d", &t);

    while (t--) {

        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &A[i]);
            //A[i] = rand() * rand();
        }

        /*int c = 0;
        for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
        for (int k = j + 1; k <= n; ++k) {
        if ((A[i]^A[j]) < (A[j] ^ A[k])) ++c;

        }
        }
        }*/


        long long ans = tt.ijk();
        printf("%lld\n", ans);
    }
    return 0;
}

/*

10
13
9 8 7 11 2 3 4 5 6 7 8 9 10

10
9 18 7 11 211 3 1411 8 1119 11110

5
8 7 5 1 6
*/