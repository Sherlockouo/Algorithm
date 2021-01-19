#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

//************ ����ɢ�й�ϣģ�� ************
// ��̬��ϣ�����С
const int MAXH = ((1 << 20) - 1);
#define StateType unsigned long long 

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
    // ��ȡ����ֵ�Ĺ�ϣֵ
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

int Hash::getKey(StateType val) {
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
const int MAXS = 1000010;
const int BASE[] = { 12289, 24593, 98317, 393241 };
const int MOD[] = { 25165843, 50331653, 100663319, 201326611 };

#define ValueType const char 
#define HashType unsigned long long

int valueTypeIndex(ValueType v) {
    return v - 'a' + 1;
}

class StringifyHash {
public:
    StringifyHash();
    virtual ~StringifyHash();

private:
    int mod_;
    HashType *hash_;
    HashType *power_;

public:
    void initialize(int size, ValueType v[], int b = BASE[2], int p = MOD[2]);
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

void StringifyHash::initialize(int size, ValueType v[], int b, int p) {
    mod_ = p;
    power_[0] = 1;
    hash_[0] = 0;
    for (int i = 1; i <= size; ++i) {
        power_[i] = power_[i - 1] * b;
        hash_[i] = (hash_[i - 1] * b + valueTypeIndex(v[i]));
    }
}

HashType StringifyHash::get(int l, int r) {
    HashType hst = (hash_[r] - hash_[l - 1] * power_[r - l + 1]);
    return hst;
}
//************ �ַ�����ϣģ�� ************



//************ ˫��ϣģ�� ************
class DoubleStringifyHash {
private:
    StringifyHash shash_[2];

public:
    void initialize(int size, ValueType v[], int b1 = BASE[2], int p1 = MOD[2], int b2 = BASE[3], int p2 = MOD[3]);
    HashType get(int l, int r);
};

void DoubleStringifyHash::initialize(int size, ValueType v[], int b1, int p1, int b2, int p2) {
    shash_[0].initialize(size, v, b1, p1);
    shash_[1].initialize(size, v, b2, p2);
}

HashType DoubleStringifyHash::get(int l, int r) {
    HashType high = shash_[0].get(l, r);
    HashType low = shash_[1].get(l, r);
    return  high << 32 | low;
}
//************ ˫��ϣģ�� ************



// �ַ�����ϣ + ����

char str[MAXS];
StringifyHash dhl, dhr;

int Min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int t = 0;
    while (scanf("%s", &str[1]) != EOF) {
        if (strcmp(&str[1], "END") == 0) break;
        int len = strlen(&str[1]);

        // l -> r
        dhl.initialize(len, str);
        for (int i = 1; i <= len / 2; ++i) {
            char tmp = str[i];
            str[i] = str[len - i + 1];
            str[len - i + 1] = tmp;
        }
        // r -> l
        dhr.initialize(len, str);


        int Max = 1;
        for (int i = 1; i <= len; ++i) {
            // ������������� i Ϊ�е㣬������ɢ����
            int l = 1;
            int r = Min(i, len - i + 1);
            int ans = -1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (dhl.get(i - mid + 1, i) == dhr.get(len - i - mid + 2, len - i + 1)) {
                    l = mid + 1;
                    ans = mid;
                }
                else {
                    r = mid - 1;
                }
            }
            if (ans != -1) {
                ans = ans * 2 - 1;
                if (ans > Max) Max = ans;
            }

            // ż����������� [1��i] �� [i+1, len] Ϊ�����ֽ�
            l = 0;
            r = Min(i, len - i);
            ans = -1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (dhl.get(i - mid + 1, i) == dhr.get(len - i - mid + 1, len - i)) {
                    l = mid + 1;
                    ans = mid;
                }
                else {
                    r = mid - 1;
                }
            }
            if (ans != -1) {
                ans = ans << 1;
                if (ans > Max) Max = ans;
            }
        }

        printf("Case %d: %d\n", ++t, Max);

    }

    return 0;
}