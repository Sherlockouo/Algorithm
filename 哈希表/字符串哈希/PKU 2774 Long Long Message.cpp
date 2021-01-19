#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

//************ ����ɢ�й�ϣģ�� ************
// ��̬��ϣ�����С
const int MAXH = ((1 << 20) - 1);
#define StateType long long 

class Hash {

public:
    Hash();
    virtual ~Hash();

private:
    bool *hashkey_;                   // ״̬hash��key
    StateType *hashval_;              // ״̬hash��val

public:
    // ���ٵ���
    void finalize();
    // ��ʼ������
    void initialize();
    // ���û�ȡ����ֵ�Ĺ�ϣֵ
    int setKey(StateType val);
    // ��ѯ�Ƿ������ֵ�ڹ�ϣ����
    bool hasKey(StateType val);
    // ��ȡ������ϣֵ��ԭֵ
    StateType getValue(int key);
};

Hash::Hash() : hashkey_(NULL), hashval_(NULL) {
    initialize();
}

Hash::~Hash() {
    finalize();
}

void Hash::finalize() {
    if (hashkey_) {
        delete[] hashkey_;
        hashkey_ = NULL;
    }
    if (hashval_) {
        delete[] hashval_;
        hashval_ = NULL;
    }
}
void Hash::initialize() {
    // 1. �ͷſռ�����ڴ�й©
    // 2. ��ʼ����ϣ��key��val
    if (!hashkey_) {
        hashkey_ = new bool[MAXH + 1];
    }
    if (!hashval_) {
        hashval_ = new StateType[MAXH + 1];
    }
    memset(hashkey_, false, (MAXH + 1) * sizeof(bool));
}

int Hash::setKey(StateType val) {
    // 1. ���� λ�� ���� ȡģ��λ�������
    int key = (val & MAXH);
    while (1) {
        if (!hashkey_[key]) {
            // 2. �����Ӧ��keyû�г��ֹ��������û�г�ͻ������key�Ĳ�λ����val��
            hashkey_[key] = true;
            hashval_[key] = val;
            return key;
        }
        else {
            if (hashval_[key] == val) {
                // 3. ���key �Ĳ�λ���ú�valƥ�䣬��˵���ҵ��ˣ����� key��
                return key;
            }
            // 4. û���ҵ����ʵ� key�� ���ж���Ѱַ
            key = (key + 1) & MAXH;
        }
    }
}

bool Hash::hasKey(StateType val) {
    int key = (val & MAXH);
    while (1) {
        if (!hashkey_[key]) {
            return false;
        }
        else {
            if (hashval_[key] == val) {
                return true;
            }
            key = (key + 1) & MAXH;
        }
    }
}

StateType Hash::getValue(int key) {
    if (key < MAXH && hashkey_[key]) {
        return hashval_[key];
    }
    return -1;
}
//************ ����ɢ�й�ϣģ�� ************




//************ �ַ�����ϣģ�� ************
// �ַ�����󳤶�
const int MAXS = 100010;
const int BASE[] = { 133, 233, 12289 };
const int MOD[] = { 1e9 + 7, 1e9 + 9, 19260817 };

#define ll long long
#define ValueType char
#define AUTO_OVERFLOW


// �����Զ�������൱�����е�������ʽ����ȡģ���������ݲ������� 2^64 ȡģ
#ifdef AUTO_OVERFLOW
#define HashType unsigned long long
#else
#define HashType int
#endif // AUTO_OVERFLOW


int valueTypeIndex(ValueType v) {
    return v - 'a' + 1;
}

class StringifyHash {
public:
    StringifyHash();
    virtual ~StringifyHash();

private:
    int base_, mod_;
    HashType *hash_;
    HashType *power_;

public:
    // ������ֻ��Ҫ����һ��
    void initialize_basepower(int b = BASE[0], int p = MOD[0]);
    void initialize(int size, ValueType v[]);
    HashType get(int l, int r);
};

StringifyHash::StringifyHash() : hash_(NULL), power_(NULL) {
    hash_ = new HashType[MAXS];
    power_ = new HashType[MAXS];
}

StringifyHash::~StringifyHash() {
    if (hash_) {
        delete[] hash_;
        hash_ = NULL;
    }
    if (power_) {
        delete[] power_;
        power_ = NULL;
    }
}


void StringifyHash::initialize_basepower(int b /*= BASE[0]*/, int p /*= MOD[0]*/)
{
    base_ = b;
    mod_ = p;
    power_[0] = 1;
    for (int i = 1; i < MAXS; ++i) {
#ifdef AUTO_OVERFLOW
        power_[i] = power_[i - 1] * b;
#else
        power_[i] = (ll)power_[i - 1] * b % p;
#endif
    }
}

void StringifyHash::initialize(int size, ValueType v[]) {
    hash_[0] = 0;
    for (int i = 1; i <= size; ++i) {
#ifdef AUTO_OVERFLOW
        hash_[i] = (hash_[i - 1] * base_ + valueTypeIndex(v[i]));
#else
        hash_[i] = ((ll)hash_[i - 1] * base_ + valueTypeIndex(v[i])) % mod_;
#endif
    }
}

HashType StringifyHash::get(int l, int r) {
#ifdef AUTO_OVERFLOW
    HashType hst = (hash_[r] - hash_[l - 1] * power_[r - l + 1]);
#else
    HashType hst = ((ll)hash_[r] - (ll)hash_[l - 1] * power_[r - l + 1]) % mod_;
    if (hst < 0) hst += mod_;
#endif
    return hst;
}
//************ �ַ�����ϣģ�� ************



//************ ˫��ϣģ�� ************
class DoubleStringifyHash {
private:
    StringifyHash shash_[2];

public:
    void initialize_basepower(int b1 = BASE[0], int p1 = MOD[0], int b2 = BASE[1], int p2 = MOD[1]);
    void initialize(int size, ValueType v[]);
    HashType get(int l, int r);
};



void DoubleStringifyHash::initialize_basepower(int b1 /*= BASE[0]*/, int p1 /*= MOD[0]*/, int b2 /*= BASE[1]*/, int p2 /*= MOD[1]*/){
    shash_[0].initialize_basepower(b1, p1);
    shash_[1].initialize_basepower(b2, p2);
}

void DoubleStringifyHash::initialize(int size, ValueType v[]) {
    shash_[0].initialize(size, v);
    shash_[1].initialize(size, v);
}

HashType DoubleStringifyHash::get(int l, int r) {
    HashType high = shash_[0].get(l, r);
    HashType low = shash_[1].get(l, r);
    return  high << 32 | low;
}
//************ ˫��ϣģ�� ************


// ����һ������ L�� Ȼ���һ���ַ���ȡ���г���Ϊ L �������Ӵ������ַ���ɢ�й�ϣ����һ�������й�ϣ�ַ�������
Hash h;
StringifyHash sh[2];
char str[2][MAXS];
int len[2];

int Min(int a, int b) {
    return a < b ? a : b;
}


bool checkLength(int L) {
    h.initialize();
    for (int i = 1; i + L - 1 <= len[0]; ++i) {
        h.setKey(sh[0].get(i, i + L - 1));
    }
    for (int i = 1; i + L - 1 <= len[1]; ++i) {
        if (h.hasKey(sh[1].get(i, i + L - 1))) {
            return true;
        }
    }
    return false;
}

int main() {
    sh[0].initialize_basepower();
    sh[1].initialize_basepower();

    while (scanf("%s", &str[0][1]) != EOF) {
        scanf("%s", &str[1][1]);
        len[0] = strlen(&str[0][1]);
        len[1] = strlen(&str[1][1]);
        int l = 0, r = Min(len[0], len[1]);


        sh[0].initialize(len[0], str[0]);
        sh[1].initialize(len[1], str[1]);

        int ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (checkLength(mid)) {
                l = mid + 1;
                ans = mid;
            }
            else {
                r = mid - 1;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}