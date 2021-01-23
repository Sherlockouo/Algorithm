#include <iostream>
#include <queue>
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


//************ �����������ģ�� ************

const int inf = -1;

class IBFSState {
protected:
    StateType nowstate_;
    static StateType finalstate_;
public:
    IBFSState() {}
    virtual bool isValidState() = 0;                // 1. �ж����״̬ [λ��] �Ƿ�Ϸ����Ƿ�Խ����߲��ɴ�֮���
    virtual void DeSerialize(StateType state) = 0;  // 2. ��������̳У���Ϊʵ�ʷ����л���ʲô���ݣ�ֻ������֪��

    virtual StateType Serialize() {                 // 3. ���л�������ֻ��һ�������ǳ����� StateType
        return nowstate_;
    }
    virtual bool isFinalState() {                   // 4. ��ֹ̬�����ж�������Բ�ȷ���ģ�Ҫ�� virtual
        return nowstate_ == finalstate_;
    }
    static void setFinalState(StateType s_) {
        finalstate_ = s_;
    }
};

StateType IBFSState::finalstate_ = 0;

class BFSGraphBase {
public:
    BFSGraphBase();
    virtual ~BFSGraphBase();
private:
    virtual void bfs_initialize(IBFSState* pkInitState);
public:
    virtual int bfs(IBFSState* pkInitState, IBFSState* pkFinalState);
    virtual void bfs_state_initialize();
    virtual int bfs_get_step(IBFSState* pkState);

public:
    virtual void bfs_extendstate(int bfsHashState, IBFSState* bfsState) = 0;
    virtual void bfs_outputpath(IBFSState* pkState);

protected:
    queue <int> queue_;               // ���ڹ��ѵĶ���
    Hash hash_;                       // ���״̬��hash��
    int* step_;                       // ��ǳ�ʼ״̬��ĳ��״̬�Ĳ���
    int* pre_;                        // ��¼ÿ��״̬��ǰ��״̬ 
};


BFSGraphBase::BFSGraphBase() : step_(NULL) {
    step_ = new int[MAXH + 1];
    pre_ = new int[MAXH + 1];
}

BFSGraphBase::~BFSGraphBase() {
    if (step_) {
        delete[] step_;
        step_ = NULL;
    }
    if (pre_) {
        delete[] pre_;
        pre_ = NULL;
    }
}

void BFSGraphBase::bfs_state_initialize() {
    memset(step_, inf, (MAXH + 1) * sizeof(int));           // 1. ������ʼ��
    memset(pre_, inf, (MAXH + 1) * sizeof(int));            // 2. ״̬ǰ����ʼ��
    hash_.initialize();                                     // 3. ��ϣ���ʼ��
}

int BFSGraphBase::bfs_get_step(IBFSState* pkState) {
    int initState = hash_.getKey(pkState->Serialize());
    return step_[initState];
}

void BFSGraphBase::bfs_outputpath(IBFSState* pkState) {

}

void BFSGraphBase::bfs_initialize(IBFSState* pkInitState) {
    bfs_state_initialize();
    while (!queue_.empty()) {                              // 1. �������
        queue_.pop();
    }
    int initState = hash_.getKey(pkInitState->Serialize()); // 2. ��ȡ��ʼ״̬��ϣkey
    queue_.push(initState);                                 // 3. �������
    step_[initState] = 0;                                   // 4. ��ǳ�ʼ����Ϊ 0
}

int BFSGraphBase::bfs(IBFSState* pkState, IBFSState* pkFinalState) {
    bfs_initialize(pkState);                    // 1. ��ʼ״̬ѹ�����
    if (pkFinalState) {                         // 2. ������ֹ״̬
        IBFSState::setFinalState(pkFinalState->Serialize());
    }
    else {
        IBFSState::setFinalState(inf);
    }

    while (!queue_.empty()) {
        int bfsState = queue_.front();          // 3. �Ӷ��е���һ��״̬
        StateType s = hash_.getValue(bfsState); // 4. ͨ���±귴��״̬��ͨ����ϣ�� ֵvalue ��ȡ ��ϣֵ��
        pkState->DeSerialize(s);                // 5. ͨ����ϣֵ�õ��ؼ���key���ؼ�����һ�� BFSState ��
        queue_.pop();
        if (pkState->isFinalState()) {          // 6. �ж��Ƿ���ֹ״̬
            bfs_outputpath(pkState);
            return step_[bfsState];             //    ���򷵻��߹��Ĳ���
        }
        bfs_extendstate(bfsState, pkState);     // 7. ��״̬������չ��ѹ�����
    }
    return inf;
}


// �̳���ʵ�����⹦��
class BFSState : public IBFSState {
public:
    virtual bool isValidState() {
        return true;
    }
    virtual void DeSerialize(StateType state);

    virtual bool isFinalState() {
        return false;
    }
};

class BFSGraph : public BFSGraphBase {
public:
    BFSGraph() {}
    virtual ~BFSGraph() {}
    virtual void bfs_extendstate(int bfsHashState, IBFSState* bfsState);
};

//************ �����������ģ�� ************


//************ ��Ҫʵ�ֵĽӿ� ************

const int MAXV = 16;
const int MAXD = 4;

// ע���1  ����������
int adj[MAXV][MAXD] = {
    { 2, 3, 5, 9 },//1
    { 1, 4, 6, 10 },//2
    { 1, 4, 7, 11 },//3
    { 2, 3, 8, 12 },//4
    { 1, 6, 7, 13 },//5
    { 2, 5, 8, 14 },//6
    { 3, 5, 8, 15 },//7
    { 4, 6, 7, 16 },//8
    { 1, 10, 11, 13 },//9
    { 2, 9, 12, 14 },//10
    { 3, 9, 12, 15 },//11
    { 4, 10, 11, 16 },//12
    { 5, 9, 14, 15 },//13
    { 6, 10, 13, 16 },//14
    { 7, 11, 13, 16 },//15
    { 8, 12, 14, 15 }//16
};

void BFSState::DeSerialize(StateType state) {
    nowstate_ = state;
}

bool has(int state, int bit) {
    return state & (1 << bit);
}

void BFSGraph::bfs_extendstate(int bfsHashState, IBFSState* bfsState) {
    BFSState bs;
    for (int i = 0; i < MAXV; ++i) {
        for (int j = 0; j < MAXD; ++j) {
            int toState = bfsState->Serialize();
            if (has(toState, i) != has(toState, adj[i][j])) {
                toState ^= (1 << i);
                toState ^= (1 << adj[i][j]);

                bs.DeSerialize(toState);

                int sState = hash_.getKey(toState);
                if (step_[sState] == inf) {
                    queue_.push(sState);
                    step_[sState] = step_[bfsHashState] + 1;
                }
            }
        }
    }
}


//************ ��Ҫʵ�ֵĽӿ� ************

BFSGraph bfs;

int main() {

    for (int i = 0; i < MAXV; ++i) {
        for (int j = 0; j < MAXD; ++j) {
            adj[i][j] -= 1;
        }
    }
    BFSState S;
    S.DeSerialize(65280);
    bfs.bfs(&S, NULL);

    int t, cas = 0;
    scanf("%d", &t);

    while (t--) {
        int ans = 0;
        for (int i = 0; i < MAXV; ++i) {
            int v;
            scanf("%d", &v);
            if (v) {
                ans |= (1 << i);
            }
        }
        BFSState bs;
        bs.DeSerialize(ans);
        int ss = bfs.bfs_get_step(&bs);
        if (ss > 3) {
            printf("Case #%d: more\n", ++cas);
        }
        else
            printf("Case #%d: %d\n", ++cas, ss);

    }
    return 0;
}