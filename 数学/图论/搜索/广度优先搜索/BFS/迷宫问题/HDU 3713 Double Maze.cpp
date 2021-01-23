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
    virtual void bfs_outputpath(IBFSState* pkState) = 0;

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
//************ �����������ģ�� ************





//************ ��Ҫʵ�ֵĽӿ� ************
const int MAPN = 6;
int W, H;
int NOW;
int Map[100][10][10];

const int DIR_COUNT = 4;
const int dir[DIR_COUNT][2] = {
    // D, L, R, U
    // �£� �� �ң���
    { 1, 0 }, { 0, -1 }, { 0, 1 }, { -1, 0 }
};
char CRT[DIR_COUNT + 1] = "DLRU";

int hasBarrior(int state, int diridx) {
    int dirto[] = { 1, 0, 2, 3 };
    return state & (1 << dirto[diridx]);
}

bool isSquare(int state) {
    return state & (1 << 4);
}

bool isHole(int state) {
    return !isSquare(state);
}

bool isStart(int state) {
    return state & (1 << 5);
}

bool isEnd(int state) {
    return state & (1 << 6);
}

class BFSState : public IBFSState {
public:
    int x1_, y1_, x2_, y2_;

    void print() {
        printf("(%d,%d),(%d,%d)\n", x1_, y1_, x2_, y2_);
    }
    virtual StateType Serialize(int x1, int y1, int x2, int y2) {
        x1_ = x1;
        y1_ = y1;
        x2_ = x2;
        y2_ = y2;
        nowstate_ = (x1_ << 9 | y1_ << 6 | x2_ << 3 | y2_);
        return nowstate_;
    }
    virtual void DeSerialize(StateType state) {
        nowstate_ = state;
        x1_ = (state >> 9) & 0x7;
        y1_ = (state >> 6) & 0x7;
        x2_ = (state >> 3) & 0x7;
        y2_ = (state >> 0) & 0x7;
    }

    virtual bool isFinalState() {
        return isEnd(Map[NOW][x1_][y1_]) && isEnd(Map[NOW - 1][x2_][y2_]);
    }

    virtual bool canMove(int d) {
        return !hasBarrior(Map[NOW][x1_][y1_], d) || !hasBarrior(Map[NOW - 1][x2_][y2_], d);
    }

    virtual StateType moveDir(BFSState *pre, int d) {
        *this = *pre;

        if (!hasBarrior(Map[NOW][x1_][y1_], d)) {
            x1_ += dir[d][0];
            y1_ += dir[d][1];
        }
        if (!hasBarrior(Map[NOW - 1][x2_][y2_], d)) {
            x2_ += dir[d][0];
            y2_ += dir[d][1];
        }
        return Serialize(x1_, y1_, x2_, y2_);
    }

    virtual bool isValidState() {
        if (x1_ < 0 || y1_ < 0 || x1_ >= MAPN || y1_ >= MAPN) {
            return false;
        }
        if (x2_ < 0 || y2_ < 0 || x2_ >= MAPN || y2_ >= MAPN) {
            return false;
        }
        int state1 = Map[NOW][x1_][y1_];
        int state2 = Map[NOW - 1][x2_][y2_];

        return (isSquare(state1) && isSquare(state2));
    }

    void operator=(const BFSState& bs) {
        x1_ = bs.x1_;
        y1_ = bs.y1_;

        x2_ = bs.x2_;
        y2_ = bs.y2_;
    }

    BFSState operator - (const BFSState& other) {
        BFSState tmp = *this;
        tmp.x1_ -= other.x1_;
        tmp.y1_ -= other.y1_;

        tmp.x2_ -= other.x2_;
        tmp.y2_ -= other.y2_;

        return tmp;
    }
};

class BFSGraph : public BFSGraphBase {
public:
    virtual void bfs_extendstate(int bfsHashState, IBFSState* bfsState);
    virtual void bfs_outputpath(IBFSState* pkState);
};

void BFSGraph::bfs_extendstate(int bfsHashState, IBFSState* bfsState) {
    BFSState to;
    for (int i = 0; i < DIR_COUNT; ++i) {
        BFSState *bs = (BFSState *)bfsState;

        if (!bs->canMove(i)) {
            continue;
        }

        StateType toStateValue = to.moveDir(bs, i);

        if (!to.isValidState()) {
            continue;
        }
        if (hash_.hasKey(toStateValue)) {
            continue;
        }
        int toStateKey = hash_.setKey(toStateValue);
        pre_[toStateKey] = bfsHashState;
        step_[toStateKey] = step_[bfsHashState] + 1;
        queue_.push(toStateKey);
    }
}

int getDir(BFSState *pkStart, BFSState *pkEnd) {
    BFSState now = *pkStart - *pkEnd;

    for (int i = 0; i < DIR_COUNT; ++i) {
        if (now.x1_ == dir[i][0] && now.y1_ == dir[i][1] || now.x2_ == dir[i][0] && now.y2_ == dir[i][1]) {
            return i;
        }
    }
}

void BFSGraph::bfs_outputpath(IBFSState* pkState) {
    int now = hash_.getKey(pkState->Serialize());
    BFSState nowstate, prestate;
    BFSState* pkPreState = NULL;
    BFSState* pkNowState = &nowstate;
    vector <int> ans;

    while (now != -1) {
        if (!hash_.hasKey(now)) while (1)
        {

        }
        StateType st = hash_.getValue(now);
        pkNowState->DeSerialize(st);
        if (pkPreState) {
            ans.push_back(getDir(pkPreState, pkNowState));
        }
        pkPreState = &prestate;
        *pkPreState = *pkNowState;

        now = pre_[now];
    }
    for (int i = ans.size() - 1; i >= 0; --i) {
        printf("%c", CRT[ans[i]]);
    }
    puts("");
}

//************ ��Ҫʵ�ֵĽӿ� ************


char str[100];
BFSGraph bfs;

int main() {
    int t;
    int i, j;
    scanf("%d", &t);
    int x2, y2, x1, y1;
    for (NOW = 0; NOW < t; ++NOW) {
        for (i = 0; i < MAPN; ++i) {
            for (j = 0; j < MAPN; ++j) {
                scanf("%d", &Map[NOW][i][j]);
                if (isStart(Map[NOW][i][j])) {
                    x1 = i;
                    y1 = j;
                }
            }
        }

        if (NOW) {
            BFSState bfsstate;
            bfsstate.Serialize(x1, y1, x2, y2);

            int step = bfs.bfs(&bfsstate, NULL);
            if (step == inf) printf("-1\n");
        }
        x2 = x1;
        y2 = y1;
    }



    return 0;
}
