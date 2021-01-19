#include <iostream>
#include <queue>
#include <cstring>

using namespace std;


//************ ɢ�й�ϣģ�� ************
// ��̬��ϣ�����С
const int MAXH = ((1 << 21) - 1);
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



// ���������




#define MAXN 1000100
Hash h;
int a[MAXN];
StateType sumodd[MAXN], sumeven[MAXN];

char line[12000010];

void get() {
    int idx = 0, t = 0, s = 0;
    getchar();
    gets(line);
    int flag = 0, startinput = false;
    while (line[idx]) {
        if (line[idx] >= '0' && line[idx] <= '9') {
            startinput = true;
            s = s * 10 + line[idx] - '0';
        }
        else if (line[idx] == '-'){
            flag = 1;
        }
        else {
            a[++t] = flag ? -s : s;
            startinput = false;
            s = 0;
            flag = 0;
        }
        ++idx;
    }
    if (startinput) {
        a[++t] = flag ? -s : s;
    }
}

StateType getsumodd(int idx) {
    if (idx <= 0) {
        return 0;
    }
    return sumodd[idx];
}

StateType getsumeven(int idx) {
    if (idx <= 0) {
        return 0;
    }
    return sumeven[idx];
}

int power(int idx) {
    return (idx & 1) ? -1 : 1;
}

int main() {
    int t, n;
    int K, cas = 0;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &K);
        get();
        for (int i = 1; i <= n; ++i) {
            if (i & 1) {
                sumodd[i] = a[i];
                if (i - 2 > 0) sumodd[i] += sumodd[i - 2];
            }
            else {
                sumeven[i] = a[i];
                if (i - 2 > 0) sumeven[i] += sumeven[i - 2];
            }
        }
        bool bFind = false;
        for (int o = 1; o <= 2; ++o) {
            h.initialize();
            for (int i = o; i <= n; i++) {
                if (!((i - o) & 1)) {
                    // ֻ�к�oͬ��żʱ��ִ�в���
                    StateType key = getsumodd(i - 1 - (i & 1))*power(i) + getsumeven(i - 2 + (i & 1))*power(i + 1);
                    h.getKey(key);
                }

                StateType checkKey = K + getsumodd(i - 1 + (i & 1))*power(o) + getsumeven(i - (i & 1))*power(o + 1);;

                if (h.hasKey(checkKey)) {
                    bFind = true;
                }
                if (bFind) break;



            }

            if (bFind) break;
        }
        printf("Case #%d: %s.\n", ++cas, bFind ? "Yes" : "No");
    }

    return 0;
}

/*
100

10 7
1 2 3 4 5 6 7 8 9 10

10 111
1 2 3 4 5 6 7 8 9 10
*/