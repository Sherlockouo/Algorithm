/*
    1 MLE    TrieData  ���� string�������������
    2 TLE    ��Ϊ���������鿪С�ˣ������±�Խ�絼�� ��ʱ
*/

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

using namespace std;

typedef int TrieData;                        // �޸ĵ� 1
typedef const char ValueType;                // �޸ĵ� 2
const int TRIE_WORD_COUNT = 400000;          // �޸ĵ� 3
const int TRIE_WORD_LENGTH = 10;             // �޸ĵ� 4
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
        if (v != TRIE_DATA_INIT)
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
    TrieTree(int nodeCacheCount);
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

    virtual void delete_prefex(int vSize, ValueType v[]);
    virtual void query_prefix(int vSize, ValueType v[], char *ans);
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
        if (hasNode(pkNow, nodeIdx)) {
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



char from[3032], to[3002];
char lines[3010], trans[3010];
int transSize = 0;

char words[2000010][12];
int wordSize = 0;

void processTrans(TrieTree &tt) {
    trans[transSize] = '\0';
    if (transSize > 0) {
        int len = strlen(trans);
        TrieData idx = tt.query_triedata(len, trans);
        if (idx != TRIE_DATA_INIT) {
            strcpy(trans, words[idx]);
        }
        printf("%s", trans);
        transSize = 0;
    }
}

int main() {
    TrieTree tt(TRIE_NODE_CACHES);
    tt.initialize();

    scanf("%s", from);
    while (scanf("%s", to) != EOF) {
        if (strcmp(to, "END") == 0) break;
        scanf("%s", from);
        strcpy(words[wordSize], to);
        tt.insert_word(strlen(from), from, wordSize++);
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