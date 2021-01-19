#include <iostream>
#include <queue>
#include <cstring>

using namespace std;


//************ ɢ�й�ϣģ�� ************
// ��̬��ϣ�����С
const int MAXH = ((1 << 18) - 1);
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
//************ ɢ�й�ϣģ�� ************

StateType v[4];
Hash h;
StateType cnt[MAXH + 1];

int main() {
    int t, n;
    while (scanf("%lld %lld %lld %lld", &v[0], &v[1], &v[2], &v[3]) != EOF) {

        h.initialize();
        memset(cnt, 0, sizeof(cnt));

        for (int i = 1; i <= 100; ++i) {
            for (int j = 1; j <= 100; ++j) {
                if (i && j)
                    ++cnt[h.getKey(v[0] * i*i + v[1] * j*j)];
            }
        }
        bool has = false;
        StateType SUM = 0;
        for (int i = 1; i <= 100; ++i) {
            for (int j = 1; j <= 100; ++j) {
                if (i&&j){
                    StateType HASHKEY = -v[2] * i*i - v[3] * j*j;
                    if (h.hasKey(HASHKEY)) {
                        SUM += cnt[h.getKey(HASHKEY)];
                    }
                }
            }
        }
        printf("%lld\n", SUM * 16);
    }

    return 0;
}