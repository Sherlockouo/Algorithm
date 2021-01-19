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
    int getKey(StateType val);
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

int Hash::getKey(StateType val) {
    return setKey(val);
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
const int BASE[] = { 19260817, 19260817, 12289, 133, 233 };
const int MOD[] = { 1e9 + 7, 1e9 + 9, 19260817 };

#define ll long long
#define ValueType int
#define AUTO_OVERFLOW


// �����Զ�������൱�����е�������ʽ����ȡģ���������ݲ������� 2^64 ȡģ
#ifdef AUTO_OVERFLOW
// 719MS
#define HashType unsigned long long
#else
// Double Hash 1938MS
#define HashType long long
#endif // AUTO_OVERFLOW


int valueTypeIndex(ValueType v) {
    return v;
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
        power_[i] = power_[i - 1] * b;
        if (power_[i] >= p) power_[i] %= p;
#endif
    }
}

void StringifyHash::initialize(int size, ValueType v[]) {
    hash_[0] = 0;
    for (int i = 1; i <= size; ++i) {
#ifdef AUTO_OVERFLOW
        hash_[i] = (hash_[i - 1] * base_ + valueTypeIndex(v[i]));
#else
        hash_[i] = (hash_[i - 1] * base_ + valueTypeIndex(v[i]));
        if (hash_[i] >= mod_) hash_[i] %= mod_;
#endif
    }
}

HashType StringifyHash::get(int l, int r) {
#ifdef AUTO_OVERFLOW
    HashType hst = (hash_[r] - hash_[l - 1] * power_[r - l + 1]);
#else
    HashType hst = (hash_[r] - hash_[l - 1] * power_[r - l + 1]) % mod_;
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
    return  high << 31 | low;
}
//************ ˫��ϣģ�� ************

/*

7������Ҫ��һ��������䣬ʹ���������Ķ���������ÿһλ�Ӻ���ͬ
7 6 7 2 1 4 2

1�����������ն����Ʋ�ֺ��������гɶ�ά����:
1 1 1 0 0 1 0
1 1 1 1 0 0 1
1 0 1 0 1 0 0

2������ÿһ�е�ǰ׺�ͣ��õ����¾���
1 2 3 3 3 4 4
1 2 3 4 4 4 5
1 1 2 2 3 3 3

3��Ҫ�ҵ����������� [i,j] {0 <= k < K | S[k][j] - S[k][i-1] } ����ͬ
���������ֶ���ȥ��һ����Ϊ��׼���õ���
0 0   0  0 0  0  0
0 0   0  1 1  0  1
0 -1 -1 -1 0 -1 -1

4������ת��ɣ�������Զ��������ͬ���У�ɢ�й�ϣ���

*/
#define MAXN 100010

int n, K;
int d[31][MAXN];
int s[31];

StringifyHash sh;
Hash h;
int idx[MAXH + 1];

int main() {

    sh.initialize_basepower();

    while (scanf("%d %d", &n, &K) != EOF) {
        h.initialize();
        int Max = 0;
        memset(d, 0, sizeof(d));
        for (int i = 1; i <= n; ++i) {
            int v;
            scanf("%d", &v);
            if ((1 << K) - 1 == v) {
                Max = 1;
            }
            for (int j = 0; j < K; ++j) {
                d[K - j][i] = (v & (1 << j)) ? 1 : 0;
            }
        }

        int Min = 0;
        for (int i = 1; i <= K; ++i) {
            for (int j = 1; j <= n; ++j) {
                d[i][j] += d[i][j - 1];
            }

            for (int j = 1; j <= n; ++j) {
                if (i > 1) {
                    d[i][j] -= d[1][j];
                    if (d[i][j] < Min) {
                        Min = d[i][j];
                    }
                }
            }
        }
        for (int i = 1; i <= n; ++i) d[1][i] = 0;

        for (int i = 1; i <= K; ++i) {
            for (int j = 0; j <= n; ++j) {
                d[i][j] -= Min;
            }
        }

        /*for (int i = 1; i <= K; ++i) {
        for (int j = 0; j <= n; ++j) {
        printf("%d ", d[i][j]);
        }
        puts("");
        }*/


        for (int i = 0; i <= n; ++i) {
            for (int j = 1; j <= K; ++j) {
                s[j] = d[j][i];
            }
            sh.initialize(K, s);
            HashType hs = sh.get(1, K);
            if (h.hasKey(hs)) {
                int key = h.getKey(hs);
                int ans = i - idx[key];
                if (ans > Max) Max = ans;
            }
            else {
                idx[h.setKey(hs)] = i;

            }

        }
        printf("%d\n", Max);

    }


    return 0;
}

/*

7 3
7
6
7
2
1
4
2

2 3
5 2

*/