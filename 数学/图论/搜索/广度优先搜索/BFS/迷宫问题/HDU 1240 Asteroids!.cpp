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
    void bfs_initialize(IBFSState* pkInitState);
public:
    int bfs(IBFSState* pkInitState, IBFSState* pkFinalState);
public:
    virtual void bfs_extendstate(int bfsHashState, IBFSState* bfsState) = 0;

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

void BFSGraphBase::bfs_initialize(IBFSState* pkInitState) {
    while (!queue_.empty()) {                              // 1. �������
        queue_.pop();
    }
    memset(step_, -1, (MAXH + 1) * sizeof(int));            // 2. ״̬��ʼ��
    hash_.initialize();                                     // 3. ��ϣ���ʼ��

    int initState = hash_.getKey(pkInitState->Serialize()); // 4. ��ȡ��ʼ״̬��ϣkey
    queue_.push(initState);                                 // 5. �������
    step_[initState] = 0;                                   // 6. ��ǳ�ʼ����Ϊ 0
}

int BFSGraphBase::bfs(IBFSState* pkState, IBFSState* pkFinalState) {
    bfs_initialize(pkState);                    // 1. ��ʼ״̬ѹ�����
    if (pkFinalState) {                         // 2. ������ֹ״̬
        IBFSState::setFinalState(pkFinalState->Serialize());
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
int MAX;
char Map[20][20][20];

const int DIR_COUNT = 6;
const int dir[DIR_COUNT][3] = {
    { 0, 0, 1 },
    { 0, 0, -1 },
    { 0, 1, 0 },
    { 0, -1, 0 },
    { 1, 0, 0 },
    { -1, 0, 0 }
};

class BFSState : public IBFSState {
public:
    int x_, y_, z_;

    virtual StateType Serialize(int x, int y, int z) {
        x_ = x;
        y_ = y;
        z_ = z;
        nowstate_ = (x_ << 8 | y_ << 4 | z_);
        return nowstate_;
    }
    virtual void DeSerialize(StateType state) {
        nowstate_ = state;
        x_ = (state >> 8);
        y_ = (state >> 4) & 0xf;
        z_ = (state & 0xf);
    }

    virtual bool isValidState() {
        if (x_ < 0 || y_ < 0 || z_ < 0 || x_ >= MAX || y_ >= MAX || z_ >= MAX) {
            return false;
        }
        if (Map[z_][x_][y_] != 'O') {
            return false;
        }
        return true;
    }
};

class BFSGraph : public BFSGraphBase {
public:
    virtual void bfs_extendstate(int bfsHashState, IBFSState* bfsState);
};

void BFSGraph::bfs_extendstate(int bfsHashState, IBFSState* bfsState) {
    for (int i = 0; i < DIR_COUNT; ++i) {
        BFSState *bs = (BFSState *)bfsState;
        BFSState to;
        StateType toStateValue = to.Serialize(bs->x_ + dir[i][0], bs->y_ + dir[i][1], bs->z_ + dir[i][2]);
        if (!to.isValidState()) {
            continue;
        }
        if (hash_.hasKey(toStateValue)) {
            continue;
        }
        int toStateKey = hash_.getKey(toStateValue);
        step_[toStateKey] = step_[bfsHashState] + 1;
        queue_.push(toStateKey);
    }
}


//************ ��Ҫʵ�ֵĽӿ� ************


char str[100];
BFSGraph bfs;

int main() {
    while (scanf("%s %d", str, &MAX) != EOF) {
        for (int z = 0; z < MAX; ++z) {
            for (int x = 0; x < MAX; ++x) {
                scanf("%s", Map[z][x]);
            }
        }
        BFSState initState, finalState;
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        initState.Serialize(x, y, z);
        scanf("%d %d %d", &x, &y, &z);
        finalState.Serialize(x, y, z);
        scanf("%s", str);

        int ans = bfs.bfs((IBFSState *)&initState, (IBFSState *)&finalState);
        if (ans == -1) printf("NO ROUTE\n");
        else printf("%d %d\n", MAX, ans);
    }

    return 0;
}
