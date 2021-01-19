#include <iostream>
#include <queue>
#include <cstring>
#include <cmath>

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
#define MAXN 100010
Hash h;
int a[MAXN], f[MAXN], b[MAXN], c[MAXN];

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


vector <int> fac[MAXN];
int hashpos[MAXN];

void getmaxf(int n, int *org) {
    memset(hashpos, 0, sizeof(hashpos));

    for (int i = 1; i <= n; ++i) {
        if (hashpos[org[i]]) {
            f[i] = hashpos[org[i]];
        }
        else {
            f[i] = i;
        }
        for (int j = fac[org[i]].size() - 1; j >= 0; --j) {
            int fact = fac[org[i]][j];
            hashpos[fact] = i;
        }
    }
    for (int i = 1; i <= n; ++i) {
        b[i] = a[f[i]];
    }
}

void getminf(int n, int *org) {
    memset(hashpos, 0, sizeof(hashpos));

    for (int i = n; i >= 1; --i) {
        if (hashpos[org[i]]) {
            f[i] = hashpos[org[i]];
        }
        else {
            f[i] = i;
        }
        for (int j = fac[org[i]].size() - 1; j >= 0; --j) {
            int fact = fac[org[i]][j];
            hashpos[fact] = i;
        }
    }
    for (int i = 1; i <= n; ++i) {
        c[i] = a[f[i]];
    }
}



int main() {
    int n;
    for (int i = 2; i < MAXN; ++i) {
        int s = 1 + sqrt(i + 0.0);
        for (int j = 1; j <= s; ++j) {
            if (i % j == 0) {
                fac[i].push_back(j);
                if (i*i != j)
                    fac[i].push_back(i / j);
            }
        }
    }

    while (scanf("%d", &n) != EOF && n) {
        get();
        getmaxf(n, a);
        getminf(n, a);
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans += (long long)b[i] * c[i];
        }
        printf("%lld\n", ans);
    }

    return 0;
}