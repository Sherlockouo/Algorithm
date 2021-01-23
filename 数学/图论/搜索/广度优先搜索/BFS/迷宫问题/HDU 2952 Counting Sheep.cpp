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
    virtual void bfs_extendstate(int bfsHashState, IBFSState* bfsState) = 0;
    virtual int bfs_get_step(IBFSState* pkState);
protected:
    queue <int> queue_;               // ���ڹ��ѵĶ���
    Hash hash_;                       // ���״̬��hash��
    int* step_;                       // ��ǳ�ʼ״̬��ĳ��״̬�Ĳ���
};


BFSGraphBase::BFSGraphBase() : step_(NULL) {
    step_ = new int[MAXH + 1];
}

BFSGraphBase::~BFSGraphBase() {
    if (step_) {
        delete[] step_;
        step_ = NULL;
    }
}

void BFSGraphBase::bfs_state_initialize() {
    memset(step_, inf, (MAXH + 1) * sizeof(int));           // 1. ״̬��ʼ��
    hash_.initialize();                                     // 2. ��ϣ���ʼ��
}

int BFSGraphBase::bfs_get_step(IBFSState* pkState) {
    int initState = hash_.getKey(pkState->Serialize());
    return step_[initState];
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
            return step_[bfsState];             //    ���򷵻��߹��Ĳ���
        }
        bfs_extendstate(bfsState, pkState);     // 7. ��״̬������չ��ѹ�����
    }
    return -1;
}
//************ �����������ģ�� ************





//************ ��Ҫʵ�ֵĽӿ� ************
const int MAPN = 110;
int W, H;
char Map[110][110];

const int DIR_COUNT = 4;
const int dir[DIR_COUNT][2] = {
    { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }
};

class BFSState : public IBFSState {
public:
    int x_, y_;

    virtual StateType Serialize(int x, int y) {
        x_ = x;
        y_ = y;
        nowstate_ = (x_ << 7 | y_);
        return nowstate_;
    }
    virtual void DeSerialize(StateType state) {
        nowstate_ = state;
        x_ = (state >> 7);
        y_ = state & 0x7f;
    }

    virtual bool isValidState() {
        if (x_ < 0 || y_ < 0 || x_ >= W || y_ >= H) {
            return false;
        }
        if (Map[x_][y_] != '#') {
            return false;
        }
        return true;
    }
};

class BFSGraph : public BFSGraphBase {
public:
    virtual void bfs_initialize(IBFSState* pkInitState);
    virtual void bfs_extendstate(int bfsHashState, IBFSState* bfsState);
};

void BFSGraph::bfs_initialize(IBFSState* pkInitState) {
    while (!queue_.empty()) {                              // 1. �������
        queue_.pop();
    }
    int initState = hash_.getKey(pkInitState->Serialize()); // 2. ��ȡ��ʼ״̬��ϣkey
    queue_.push(initState);                                 // 3. �������
    step_[initState] = 0;                                   // 4. ��ǳ�ʼ����Ϊ 0
}

void BFSGraph::bfs_extendstate(int bfsHashState, IBFSState* bfsState) {
    BFSState to;
    for (int i = 0; i < DIR_COUNT; ++i) {
        BFSState *bs = (BFSState *)bfsState;
        StateType toStateValue = to.Serialize(bs->x_ + dir[i][0], bs->y_ + dir[i][1]);
        if (!to.isValidState()) {
            continue;
        }
        if (hash_.hasKey(toStateValue)) {
            continue;
        }
        int toStateKey = hash_.setKey(toStateValue);
        step_[toStateKey] = step_[bfsHashState] + 1;
        queue_.push(toStateKey);
    }
}


//************ ��Ҫʵ�ֵĽӿ� ************


char str[100];
BFSGraph bfs;

int main() {
    int t;
    int i, j;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &W, &H);
        for (i = 0; i < W; ++i) {
            scanf("%s", Map[i]);
        }
        int c = 0;
        bfs.bfs_state_initialize();

        for (i = 0; i < W; ++i) {
            for (j = 0; j < H; ++j) {
                BFSState bfsstate;
                bfsstate.Serialize(i, j);
                if (Map[i][j] == '#' && bfs.bfs_get_step(&bfsstate) == inf) {
                    ++c;
                    bfs.bfs(&bfsstate, NULL);
                }
            }
        }
        printf("%d\n", c);
    }

    return 0;
}
