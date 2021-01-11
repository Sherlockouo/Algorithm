/*
    2 MLE �������С��������Ԥ��������һ��ʼ�����˶��ٸ��������֪�ģ� ģ����� TrieNode* �滻�� int
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
#include <vector>
using namespace std;

typedef int TrieData;                        // �޸ĵ� 1
typedef const char ValueType;                // �޸ĵ� 2
const int TRIE_WORD_COUNT = 100000;          // �޸ĵ� 3
const int TRIE_WORD_LENGTH = 36;             // �޸ĵ� 4
const int TRIE_NODE_COUNT = 10;              // �޸ĵ� 5

const TrieData TRIE_DATA_INIT = -1;
const int TRIE_NODE_NULL = -1;
const int TRIE_NODE_CACHES = TRIE_WORD_COUNT * TRIE_WORD_LENGTH;


int trieNodeValueHash(ValueType v) {         // �޸ĵ� 6
    return v - '0';
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
        pkNow->setTrieData(data);
    }
    pkNow->setWord(true);
    
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







const unsigned int MAXDIGITS = 22002;        // ������λ������ 10^MAXDIGITS
const unsigned int MAXN = 9999;             // ÿ��a[i]��ʾ���������  
const unsigned int DLEN = 4;                // MAXN�����λ�� 


class BigNum {
public:
    int a[(MAXDIGITS + DLEN - 1) / DLEN + 1];
    int len;
    BigNum(){ len = 1; memset(a, 0, sizeof(a)); }
    BigNum(const int b);
    BigNum(const char * buffer);
    BigNum(const BigNum & T);
    void Attach(const char * buffer);
    bool Bigger(const BigNum &) const;
    BigNum & operator=(const BigNum &);
    BigNum & Add(const BigNum &);
    BigNum & Sub(const BigNum &);
    BigNum operator+(const BigNum &) const;
    BigNum operator-(const BigNum &) const;
    BigNum operator*(const BigNum &) const;
    BigNum operator/(const int &) const;
    void Print();
    string ToString();
};

BigNum::BigNum(const int b) {
    int c, d = b;
    len = 0;
    memset(a, 0, sizeof(a));
    while (d > MAXN) {
        c = d % (MAXN + 1);
        d = d / (MAXN + 1);
        a[len++] = c;
    }
    a[len++] = d;
}

BigNum::BigNum(const char * buffer) {
    Attach(buffer);
}

void BigNum::Attach(const char * buffer) {
    int i, j;
    int lst[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
    j = len = 0;
    memset(a, 0, sizeof(a));
    for (i = strlen(buffer) - 1; i >= 0; --i, ++j) {
        if (j >= DLEN) {
            j = 0;
            len++;
        }
        a[len] += lst[j] * (buffer[i] - '0');
    }
    len++;
    // ����ǰ���� 
    while (len > 1 && a[len - 1] == 0) len--;
}

BigNum::BigNum(const BigNum & T) : len(T.len)
{
    memcpy(a, T.a, sizeof(a));
}

bool  BigNum::Bigger(const BigNum & T) const {
    int ln;
    if (len > T.len) return true;
    else if (len == T.len){
        ln = len - 1;
        while (ln >= 0 && a[ln] == T.a[ln]) ln--;
        if (ln >= 0 && a[ln] > T.a[ln]) return true;
        else return false;
    }
    else return false;
}

BigNum & BigNum::operator=(const BigNum & n){
    len = n.len;
    memcpy(a, n.a, sizeof(a));
    return *this;
}
BigNum & BigNum::Add(const BigNum & T){
    int i, big;
    big = T.len > len ? T.len : len;
    for (i = 0; i < big; i++)
    {
        a[i] = a[i] + T.a[i];
        if (a[i] > MAXN)
        {
            a[i + 1]++;
            a[i] = a[i] - MAXN - 1;
        }
    }
    if (a[big] != 0) len = big + 1;
    else len = big;
    return *this;
}
BigNum & BigNum::Sub(const BigNum & T){
    int i, j, big;
    big = T.len > len ? T.len : len;
    for (i = 0; i < big; i++)
    {
        if (a[i] < T.a[i])
        {
            j = i + 1;
            while (a[j] == 0) j++;
            a[j--]--;
            while (j > i) a[j--] += MAXN;
            a[i] = a[i] + MAXN + 1 - T.a[i];
        }
        else a[i] -= T.a[i];
    }
    len = big;
    while (len > 1 && a[len - 1] == 0) len--;
    return *this;
}
BigNum BigNum::operator+(const BigNum & n) const{
    BigNum a = *this;
    a.Add(n);
    return a;
}
BigNum BigNum::operator-(const BigNum & T) const{
    BigNum b = *this;
    b.Sub(T);
    return b;
}

BigNum BigNum::operator*(const BigNum & T) const{
    BigNum ret;
    int i, j, up, temp1, temp;
    for (i = 0; i < len; i++)
    {
        up = 0;
        for (j = 0; j < T.len; j++)
        {
            temp = a[i] * T.a[j] + ret.a[i + j] + up;
            if (temp > MAXN)
            {
                temp1 = temp % (MAXN + 1);
                up = temp / (MAXN + 1);
                ret.a[i + j] = temp1;
            }
            else
            {
                up = 0;
                ret.a[i + j] = temp;
            }
        }
        if (up != 0) ret.a[i + j] = up;
    }
    ret.len = i + j;
    while (ret.len > 1 && ret.a[ret.len - 1] == 0) ret.len--;
    return ret;
}
BigNum BigNum::operator/(const int & b) const{
    BigNum ret;
    int i, down = 0;
    for (i = len - 1; i >= 0; i--)
    {
        ret.a[i] = (a[i] + down * (MAXN + 1)) / b;
        down = a[i] + down * (MAXN + 1) - ret.a[i] * b;
    }
    ret.len = len;
    while (ret.a[ret.len - 1] == 0) ret.len--;
    return ret;
}
void BigNum::Print() {
    int i;
    char format[10];
    sprintf(format, "%%0%dd", DLEN);
    printf("%d", a[len - 1]);
    for (i = len - 2; i >= 0; i--)
    {
        printf(format, a[i]);
    }
    putchar('\n');
}

string BigNum::ToString() {
    char c[MAXDIGITS + DLEN + 1], tmp[DLEN + 1];
    char format[10];
    
    sprintf(c, "%d", a[len - 1]);
    sprintf(format, "%%0%dd", DLEN);
    
    for (int i = len - 2; i >= 0; --i) {
        sprintf(tmp, format, a[i]);
        strcat(c, tmp);
        if (len - i > 50) break;
    }

    return string(c);
}

int Min(int a, int b) {
    return a < b ? a : b;
}

BigNum Pre, PrePre, Now;

int main() {
    TrieTree tt;
    tt.initialize();

    tt.insert_word(1, "1", 0);

    // �ֵ��� 1 ��λ�ò��� 0
    Pre = 1;
    PrePre = 1;
    for (int i = 2; i < 100000; ++i) {
        Now = Pre + PrePre;
        // �ֵ��� ���� Now
        PrePre = Pre;
        Pre = Now;

        string s = Now.ToString();
        
        tt.insert_word(Min(40, s.length()), s.c_str(), i);
    }
    int t, cas = 0;
    char ans[100];
    scanf("%d", &t);
    while (t--) {
        scanf("%s", ans);
        printf("Case #%d: %d\n", ++cas, tt.query_triedata(strlen(ans), ans));
    }
    return 0;
}