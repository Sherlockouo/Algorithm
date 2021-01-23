#include <iostream>
#include <queue>
#include <cstring>
using namespace std;


//************ �Թ��� ����������� ģ�� ************
const int MAXQUEUE = 1000000;
const int MAXN = 110;
const int DIR_COUNT = 4;
const int inf = -1;

enum eDirection {
    ED_RIGHT = 0,
    ED_UP = 1,
    ED_LEFT = 2,
    ED_DOWN = 3,
};

const int dir[DIR_COUNT][2] = {
    { 0, 1 },   // 0. ��
    { -1, 0 },  // 1. ��
    { 0, -1 },  // 2. ��
    { 1, 0 },   // 3. ��
};

int getDirIndex(int dx, int dy) {
    for (int i = 0; i < DIR_COUNT; ++i) {
        if (dx == dir[i][0] && dy == dir[i][1]) {
            return i;
        }
    }
    return -1;
}
int optDir[] = {
    2, 3, 0, 1
};
int getOptIndex(int idx) {
    if (idx & 1) {
        return 4 - idx;
    }
    else {
        return 2 - idx;
    }
}

// ���ѵĵ�ͼ����Ϊȫ�ֱ����洢
char Map[MAXN][MAXN];

// ����ʱ������е�״̬���
struct BFSState {
    char x, y;                              // 1. һ���Թ����ⶼ���е�λ���ֶ�
    int  dirMask;

protected:
    int getStateKey() const;                // 1. ���йؼ��ִ����һ����ϣֵ���й�ϣӳ��

public:
    inline int getDir(int idx) const {
        return (dirMask >> (idx << 1)) & 0x3;
    }

public:

    inline bool isValidState(int row, int col);    // 1. �����Ƿ�Ϸ���һ�����ж� �谭 �ͱ߽�
    inline bool isFinalState();                    // 2. �Ƿ����״̬
    inline int getStep() const;                    // 3. ��ȡ�� ��ʼ״̬ �� ��ǰ״̬�Ĳ���
    inline void setStep(int step);                 // 4. ���ô� ��ʼ״̬ �� ��ǰ״̬�Ĳ���
    inline void print() const;                     // 5. ���Դ�ӡ��ǰ״̬��
    inline bool operator==(const BFSState & o);    // 6. �����ж�����״̬�Ƿ����

public:
    static short step[21][21][1 << 14];          // ���״̬�Ƿ񱻷��ʹ�
    //static Hash hashState;                   // ���״̬��ɢ����µ�ɢ�й�ϣ
};


class BFSQueue {
public:
    BFSQueue();
    virtual ~BFSQueue();

    void clear();
    bool empty();
    void push(const BFSState& bs);
    BFSState& pop();
private:
    BFSState *data_;
    int front_, rear_;
};

BFSQueue::BFSQueue() : data_(NULL) {
    data_ = new BFSState[MAXQUEUE];
}

BFSQueue::~BFSQueue() {
    if (data_) {
        delete[] data_;
        data_ = NULL;
    }
}

void BFSQueue::clear() {
    front_ = rear_ = 0;
}

void BFSQueue::push(const BFSState& bs) {
    data_[rear_++] = bs;
    if (rear_ == MAXQUEUE) rear_ = 0;
}

BFSState& BFSQueue::pop(){
    if (++front_ == MAXQUEUE) front_ = 0;
    if (front_ == 0)
        return data_[MAXQUEUE - 1];
    else
        return data_[front_ - 1];
}

bool BFSQueue::empty() {
    return front_ == rear_;
}

class BFSGraph {
public:

    void bfs_extendstate(const BFSState& fromState);
    void bfs_initialize(BFSState startState);
    int  bfs(BFSState startState, int useLen);
private:
    BFSQueue queue_;
    int uselen_;
};



int snakeMap[MAXN][MAXN], cas;
int W, H;
int L, K, R, N;
int beans[MAXN], prebeans[MAXN];


int BFSState::getStateKey() const {
    // dirMask  : 11111111 11111111
    // y        : 11111
    // x        : 11111
    return x << 21 | y << 16 | dirMask;
}

bool BFSState::isValidState(int row, int col) {
    if (x < 0 || y < 0 || x >= row || y >= col) {
        return false;
    }
    if (Map[x][y] == 0) {
        return false;
    }
    return true;
}

bool BFSState::isFinalState() {
    return !x && !y;
}

int BFSState::getStep() const {
    return step[x][y][dirMask];
}

void BFSState::setStep(int sp) {
    step[x][y][dirMask] = sp;
}

void BFSState::print() const {
    printf("%d %d\n", x, y);
}

// Hash BFSState::hashState;
short BFSState::step[21][21][1 << 14];
int lenMask[10];

void BFSGraph::bfs_extendstate(const BFSState& fromState) {
    //fromState.print(); 
    int stp = fromState.getStep() + 1;
    BFSState to;
    ++cas;
    int x = fromState.x, y = fromState.y;
    if (uselen_) {
        snakeMap[x][y] = cas;
        // �ߵ�β���ǲ���Ҫ��ǵģ���Ϊ�ƶ�һ���Ժ�
        for (int i = 0; i < uselen_ - 1; ++i) {
            int d = (fromState.dirMask >> (i << 1)) & (0x3);
            x += dir[d][0];
            y += dir[d][1];
            snakeMap[x][y] = cas;
        }

    }

    for (int i = 0; i < DIR_COUNT; ++i) {
        to.x = fromState.x + dir[i][0];
        to.y = fromState.y + dir[i][1];

        if (!to.isValidState(H, W)) {
            continue;
        }
        // �Ƿ�Ե��Լ�
        if (snakeMap[to.x][to.y] == cas) {
            continue;
        }
        to.dirMask = (fromState.dirMask << 2 | optDir[i]) & lenMask[uselen_];

        if (to.getStep() == inf) {
            to.setStep(stp);
            queue_.push(to);
        }
    }

}

void BFSGraph::bfs_initialize(BFSState startState) {
    // BFSState::hashState.initialize();
    memset(BFSState::step, -1, sizeof(BFSState::step));
    queue_.clear();
    queue_.push(startState);
    startState.setStep(0);
}

int BFSGraph::bfs(BFSState startState, int useLen) {
    uselen_ = useLen;
    bfs_initialize(startState);
    while (!queue_.empty()) {
        BFSState bs = queue_.pop();
        if (bs.isFinalState()) {
            return bs.getStep();
        }
        bfs_extendstate(bs);
    }
    return inf;
}

//************ �Թ��� ����������� ģ�� ************

BFSGraph bfs;

int main() {
    int t, cas = 0;
    int x, y;
    int prex, prey;

    for (int i = 1; i <= 8; ++i) {
        lenMask[i] = (1 << ((i - 1) << 1)) - 1;
    }
    while (scanf("%d %d %d", &H, &W, &L) != EOF && (H || W | L)) {
        memset(Map, -1, sizeof(Map));

        BFSState bs;
        bs.dirMask = 0;

        for (int i = 0; i < L; ++i) {
            scanf("%d %d", &x, &y);
            if (i) {
                int dirIndex = getDirIndex(x - prex, y - prey);
                bs.dirMask |= dirIndex << ((i - 1) << 1);
            }
            else {
                bs.x = x - 1;
                bs.y = y - 1;
            }
            prex = x;
            prey = y;
        }

        scanf("%d", &N);

        while (N--) {
            scanf("%d %d", &x, &y);
            --x; --y;
            Map[x][y] = 0;
        }

        int ans = bfs.bfs(bs, L);
        printf("Case %d: %d\n", ++cas, ans);

    }
    return 0;
}

/*
10

8 9
5 2
1 8

5 2
6 2
6 3
6 4
6 5

4 2
2 6

2 1

2 5
3 5
4 4
4 5
4 6
5 6
5 7
6 7

20 20
8 7
4 0

1 1
2 1
3 1
4 1
5 1
6 1
7 1
8 1

20 1
10 1
20 2
10 2
20 3
10 3
20 4

1 2
2 3
3 4


20 20 8
20 12
20 13
20 14
20 15
20 16
20 17
20 18
20 19
29
2 1
2 2
2 3
2 4
2 5
2 6
2 7
2 8
2 9
2 10
4 2
4 3
4 4
4 5
4 6
4 7
4 8
4 9
4 10
4 11
4 12
4 13
4 14
4 15
4 16
4 17
4 18
4 19
4 20


20 20 8
20 12
20 13
20 14
20 15
20 16
20 17
20 18
20 19
30
2 1
2 2
2 3
2 4
2 5
2 6
2 7
2 8
2 9
2 10
4 1
4 2
4 3
4 4
4 5
4 6
4 7
4 8
4 9
4 10
4 11
4 12
4 13
4 14
4 15
4 16
4 17
4 18
4 19
4 20
*/