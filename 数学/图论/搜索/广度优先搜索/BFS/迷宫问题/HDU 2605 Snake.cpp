#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

//************ ����ɢ�й�ϣģ�� ************
// ��̬��ϣ�����С
const int MAXH = ((1 << 23) - 1);
#define StateType int

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
    int cnt = 0;
    while (1) {
        if (++cnt > MAXH) {
            return key;
        }
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
    int cnt = 0;
    while (1) {
        if (++cnt > MAXH) {
            return true;
        }
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


//************ �Թ��� ����������� ģ�� ************
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

// ���ѵĵ�ͼ����Ϊȫ�ֱ����洢
char Map[MAXN][MAXN];

// ����ʱ������е�״̬���
struct BFSState {
    char x, y;                              // 1. һ���Թ����ⶼ���е�λ���ֶ�
    char beanMask;                          // 2. ��ͬ���ⲻͬ�洢�������Ƿ���Ҳ����������
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
    inline void print();                           // 5. ���Դ�ӡ��ǰ״̬��
    inline bool operator==(const BFSState & o);    // 6. �����ж�����״̬�Ƿ����

public:
    static short step[MAXH + 1];             // ���״̬�Ƿ񱻷��ʹ�
    static Hash hashState;                   // ���״̬��ɢ����µ�ɢ�й�ϣ
};


class BFSGraph {
public:
    void bfs_extendstate(const BFSState& fromState);
    void bfs_initialize(BFSState startState);
    int  bfs(BFSState startState, int useLen);
private:
    queue <BFSState> queue_;
    int uselen_;
};

enum  MapType {
    MT_EMPTY = -1,
    MT_WALL = 0,
    MT_BEAN
};

int snakeMap[MAXN][MAXN], cas;
int W, H;
int L, K, R, N;
int beans[MAXN], prebeans[MAXN];


int BFSState::getStateKey() const {
    // dirMask  : 11111111 111111
    // beanMask : 1111111
    // y        : 11111
    // x        : 11111
    return x << 26 | y << 21 | beanMask << 14 | dirMask;
}

bool BFSState::isValidState(int row, int col) {
    if (x < 0 || y < 0 || x >= row || y >= col) {
        return false;
    }
    if (Map[x][y] == MapType::MT_WALL) {
        return false;
    }
    return true;
}

bool BFSState::isFinalState() {
    return (beanMask + 1) == (1 << K);
}

int BFSState::getStep() const {
    int key = getStateKey();
    if (BFSState::hashState.hasKey(key)) {
        return step[BFSState::hashState.getKey(key)];
    }
    return inf;
}

void BFSState::setStep(int sp) {
    StateType key = getStateKey();
    if (!BFSState::hashState.hasKey(key)) {
        step[BFSState::hashState.getKey(key)] = sp;
    }
}

Hash BFSState::hashState;
short BFSState::step[MAXH + 1];
int lenMask[10];

void BFSGraph::bfs_extendstate(const BFSState& fromState) {
    int stp = fromState.getStep() + 1;
    BFSState to;
    ++cas;
    int x = fromState.x, y = fromState.y;
    if (uselen_) {
        snakeMap[x][y] = cas;
        // �ߵ�β���ǲ���Ҫ��ǵģ���Ϊ�ƶ�һ���Ժ�
        for (int i = 0; i < uselen_ - 2; ++i) {
            int d = (fromState.dirMask >> (i << 1)) & (0x3);
            x += dir[d][0];
            y += dir[d][1];
            snakeMap[x][y] = cas;
        }

    }

    for (int i = 0; i < DIR_COUNT; ++i) {
        to.x = fromState.x + dir[i][0];
        to.y = fromState.y + dir[i][1];

        if (!to.isValidState(W, H)) {
            continue;
        }
        // �Ƿ�Ե��Լ�
        if (snakeMap[to.x][to.y] == cas) {
            continue;
        }
        // �� Bean �Ļ���Ҫ�ж�ǰ��
        to.beanMask = fromState.beanMask;
        to.dirMask = fromState.dirMask;

        if (Map[to.x][to.y] > MapType::MT_WALL) {
            int bean = Map[to.x][to.y];
            int preBean = prebeans[bean];
            if (preBean == -1 || (to.beanMask & (1 << (preBean - 1)))) {
                // û��ǰ�� ����ǰ���Ѿ�������
                to.beanMask |= (1 << (bean - 1));
            }
            else {
                continue;
            }
        }
        to.dirMask = (fromState.dirMask << 2 | optDir[i]) & lenMask[uselen_];


        if (to.getStep() == inf) {
            to.setStep(stp);
            queue_.push(to);
        }
    }

}

void BFSGraph::bfs_initialize(BFSState startState) {
    BFSState::hashState.initialize();
    memset(BFSState::step, -1, sizeof(BFSState::step));
    while (!queue_.empty()) {
        queue_.pop();
    }
    queue_.push(startState);
    startState.setStep(0);
}

int BFSGraph::bfs(BFSState startState, int useLen) {
    uselen_ = useLen;
    bfs_initialize(startState);
    while (!queue_.empty()) {
        BFSState bs = queue_.front();
        queue_.pop();
        if (bs.isFinalState()) {
            return bs.getStep();
        }
        bfs_extendstate(bs);
    }
    return inf;
}

//************ �Թ��� ����������� ģ�� ************

BFSGraph bfs;

/*const int dir[DIR_COUNT][2] = {
{ 0, 1 },   // 0. ��
{ -1, 0 },  // 1. ��
{ 0, -1 },  // 2. ��
{ 1, 0 },   // 3. ��
};*/

// �л�
bool dfs(int depth, int u) {
    if (prebeans[u] == -1) {
        return false;
    }
    if (depth > 20) return true;
    return dfs(depth + 1, prebeans[u]);
}

int main() {
    int t;
    int v;
    int x, y;
    int prex, prey;

    for (int i = 1; i <= 8; ++i) {
        lenMask[i] = (1 << ((i - 1) << 1)) - 1;
    }

    scanf("%d", &t);

    while (t--) {
        scanf("%d %d %d %d %d %d", &H, &W, &L, &K, &R, &N);
        memset(Map, MapType::MT_EMPTY, sizeof(Map));
        memset(prebeans, -1, sizeof(prebeans));

        BFSState bs;
        bs.beanMask = bs.dirMask = 0;

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

        for (int i = 1; i <= K; ++i) {
            scanf("%d %d", &x, &y);
            --x; --y;
            Map[x][y] = i;
        }

        for (int i = 1; i <= R; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            prebeans[b] = a;
        }

        int ans = 0;
        for (int i = 1; i <= K; ++i) {
            if (dfs(0, i)) {
                ans = -1;
                break;
            }
        }


        while (N--) {
            scanf("%d %d", &x, &y);
            --x; --y;
            Map[x][y] = MapType::MT_WALL;
        }

        if (ans == -1) {

        }
        else if (L == 1) {
            ans = bfs.bfs(bs, 1);
        }
        else {
            //for (int i = 2; i <= L; ++i) {
            ans = bfs.bfs(bs, L);
            //    if (ans == inf) break;
            //}

        }

        printf("%d\n", ans);

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

*/