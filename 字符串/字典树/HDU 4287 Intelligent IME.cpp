/*
    ģ����Ҫ�޸ĵĵط���
        1��TrieData ��Ϊ�ֵ�����Ȩֵ������������;�ģ�������Ϊ�±꣬������ĳ���������ݣ�����ֱ����һ��Ȩֵ���ڼ��㣻
        2��ValueType ������ʶ�ַ������ͣ������� �ַ�����char�� Ҳ���������� int������ long long �ȵȣ�
        3��TRIE_WORD_COUNT �����ַ�������������
        4��TRIE_WORD_LENGTH �������ַ�����󳤶ȣ�
        5��TRIE_DATA_INIT ���ڶ� TrieData ����ʼֵ��
        6��trieNodeValueHash ͨ�������ϣ����ʵ�� �ַ� �� �±� ��ӳ�䣻
*/


#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
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
const int TRIE_WORD_COUNT = 5020;            // �޸ĵ� 3
const int TRIE_WORD_LENGTH = 7;              // �޸ĵ� 4
const int TRIE_NODE_COUNT = 26;              // �޸ĵ� 5

const TrieData TRIE_DATA_INIT = -1;
const int TRIE_NODE_NULL = -1;
const int TRIE_NODE_CACHES = TRIE_WORD_COUNT * TRIE_WORD_LENGTH;


int trieNodeValueHash(ValueType v) {         // �޸ĵ� 6
    return v - 'a';
}

// �ֵ��������
class TrieNode {
private:
    bool isword_;                 // �Ƿ���1����������
    int num_;                     // �ж��ٸ����ξ���������
    TrieData td_;                 // ÿ������Ȩֵ��������һЩ������;
    int nodes_[TRIE_NODE_COUNT];  // ע���������ǽ���ڴ�ص��±꣬��ȴ�ָ��ĺô��ǣ��ֽ�����һ��

public:
    inline void setNode(int nodeIdx, int node) {
        nodes_[nodeIdx] = node;
    }
    inline int getNode(int nodeIdx) {
        return nodes_[nodeIdx];
    }
    inline bool hasNode(int nodeIdx) {
        // ��㷶Χ�ж�
        if (nodeIdx < 0 || nodeIdx >= TRIE_NODE_COUNT) {
            return false;
        }
        return nodes_[nodeIdx] != TRIE_NODE_NULL;
    }
    inline void reset() {
        resetData();
        memset(nodes_, TRIE_NODE_NULL, sizeof(nodes_));
    }
    inline void resetData(){
        num_ = 0;
        isword_ = false;
        td_ = TRIE_DATA_INIT;
    }
    inline void addNum(int d) {
        num_ += d;
    }
    inline int  getNum() {
        return num_;
    }
    inline void setTrieData(TrieData v){
        if (td_ == TRIE_DATA_INIT)
            td_ = v;
    }
    inline TrieData  getTrieData() {
        return td_;
    }
    inline void setWord(bool isw) {
        isword_ = isw;
    }
    inline bool isWord(){
        return isword_;
    }

};

// �ֵ�����
class TrieTree {
public:
    TrieTree(int nodeCacheCount = TRIE_NODE_CACHES);
    virtual ~TrieTree();
    void initialize() {
        nodeId_ = 0;
        root_ = genNode();
    }

    TrieNode *root() const { return node(root_); }
    TrieNode *node(int idx) const { return &(nodes_[idx]); }

public:
    void insert_word(int vSize, ValueType v[], TrieData data);
    bool query_word(int vSize, ValueType v[]);                // ѯ���Ƿ���ڵ��� v
    int query_prefix_num(int vSize, ValueType v[]);           // ѯ���� v Ϊ�׵�ǰ׺����
    TrieData query_triedata(int vSize, ValueType v[]);        // ѯ�ʵ��� v ��Ȩֵ
    void delete_prefex(int vSize, ValueType v[]);
    void query_prefix(int vSize, ValueType v[], char *ans);


    TrieData query_dfs(TrieNode* pkNow, int vSize, ValueType v[], int vDepth);
private:
    int genNode() {
        TrieNode *pkNode = &(nodes_[nodeId_]);
        pkNode->reset();
        return nodeId_++;
    }

    bool hasNode(TrieNode *pkNow, int nodeIdx) {
        if (pkNow->hasNode(nodeIdx)) {
            TrieNode *pkNode = node(pkNow->getNode(nodeIdx));
            if (pkNode->getNum() > 0) {
                return true;
            }
        }
        return false;
    }

    void checkNode(TrieNode *pkNow, int nodeIdx) {
        if (!pkNow->hasNode(nodeIdx)) {
            pkNow->setNode(nodeIdx, genNode());
        }
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

void TrieTree::insert_word(int vSize, ValueType v[], TrieData data) {
    // �����ַ������ֵ���
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int nodeIdx = trieNodeValueHash(v[i]);
        checkNode(pkNow, nodeIdx);
        pkNow = node(pkNow->getNode(nodeIdx));
        pkNow->addNum(1);
    }
    pkNow->setWord(true);
    pkNow->setTrieData(data);
}

bool TrieTree::query_word(int vSize, ValueType v[]) {
    // ���Ҷ�Ӧ�ֵ��У��Ƿ����ַ������� v[]
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int nodeIdx = trieNodeValueHash(v[i]);
        if (!hasNode(pkNow, nodeIdx)) {
            return false;
        }
        pkNow = node(pkNow->getNode(nodeIdx));
    }
    return pkNow->isWord();
}

int TrieTree::query_prefix_num(int vSize, ValueType v[]) {
    // ���Ҷ�Ӧ�ֵ��У��Ƿ����ַ������� v[]
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int nodeIdx = trieNodeValueHash(v[i]);
        if (!hasNode(pkNow, nodeIdx)) {
            return 0;
        }
        pkNow = node(pkNow->getNode(nodeIdx));
    }
    return pkNow->getNum();
}

TrieData TrieTree::query_triedata(int vSize, ValueType v[]) {
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int nodeIdx = trieNodeValueHash(v[i]);
        if (!hasNode(pkNow, nodeIdx)) {
            return TRIE_DATA_INIT;
        }
        pkNow = node(pkNow->getNode(nodeIdx));
    }
    return pkNow->getTrieData();
}

void TrieTree::delete_prefex(int vSize, ValueType v[]) {
    int cnt = query_prefix_num(vSize, v);
    if (cnt == 0) {
        // ��ѯ��һ�Σ���û�����ǰ׺��û�оͲ���ɾ��
        return;
    }
    // ɾ����Ӧǰ׺�������ַ���
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int nodeIdx = trieNodeValueHash(v[i]);
        // ���ü������������н��ɾ��
        TrieNode *pkSon = node(pkNow->getNode(nodeIdx));
        pkSon->addNum(-cnt);
        pkNow = pkSon;
    }
}

void TrieTree::query_prefix(int vSize, ValueType v[], char *ans) {
    // ���Ҷ�Ӧ�ֵ��У�����ܹ���ʾ v[] ���ַ����洢�� ans ��
    TrieNode *pkNow = root();
    for (int i = 0; i < vSize; ++i) {
        int nodeIdx = trieNodeValueHash(v[i]);
        if (!hasNode(pkNow, nodeIdx)) {
            return;
        }
        pkNow = node(pkNow->getNode(nodeIdx));
        ans[i] = v[i];
        if (pkNow->getNum() == 1) {
            ans[i + 1] = '\0';
            return;
        }
    }
    ans[vSize] = '\0';
}



TrieData TrieTree::query_dfs(TrieNode* pkNow, int vSize, ValueType v[], int vDepth) {
    if (pkNow == NULL) {
        pkNow = root();
    }
    if (vSize == vDepth) {
        return pkNow->getNum();
    }

    int clen = strlen(mobiles[v[vDepth] - '0']);
    TrieData s = 0;
    for (int i = 0; i < clen; ++i) {
        char c = mobiles[v[vDepth] - '0'][i];
        int sonIdx = trieNodeValueHash(c);
        if (!hasNode(pkNow, sonIdx)) {
            continue;
        }
        s += query_dfs(node(pkNow->getNode(sonIdx)), vSize, v, vDepth + 1);
    }
    return s;
}



char cmd[2][55];
int n, m;

char digits[5010][10];
char words[5010][10];

int main() {
    TrieTree tt;

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
            tt.insert_word(strlen(words[i]), words[i], 1);
        }

        for (int i = 0; i < n; ++i) {
            int len = strlen(digits[i]);

            printf("%d\n", tt.query_dfs(NULL, len, digits[i], 0));
        }
    }
    return 0;
}