#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

//****** ����ͼ���ƥ��ģ��(��ʽǰ����) ******

const int VMAX = 410;
const int EMAX = 100010;

struct Edge {
    int to, next;

    Edge() {}
    Edge(int _t, int _n) : to(_t), next(_n) {}
};

class BipartiteGraph {
public:
    BipartiteGraph();
    virtual ~BipartiteGraph();
    void initialize(int n);
    void addEdge(int u, int v);
    int getMaxMatch();
    void getMaxMatchPath(int& maxMatch, int left[], int right[]);
private:
    bool findMatch(int u);               // �������㷨������·
    void dye();
    void dyeDFS(int fat, int u, int c);  // dfs �Զ������Ⱦɫ
    void doAddEdge(int u, int v);
private:
    // ע�����ǣ����ҵ㼯����������Ŀ
    int vertexcount_;

    //  ��ʽǰ����  
    Edge *edges_;                // �߼�
    int edgecount_;              // ���ñ���
    int head_[VMAX];             // ÿ���ڵ�߼�������ͷ

    // Ⱦɫ
    int color_[VMAX];

    int pre_[VMAX];              // �������㷨������·ʱ�� pre
    bool visit_[VMAX];           // �������㷨������·ʱ�� visit
};

BipartiteGraph::BipartiteGraph() :
edges_(NULL), vertexcount_(0)
{
    edges_ = new Edge[EMAX];
}

BipartiteGraph::~BipartiteGraph() {
    if (edges_) {
        delete[] edges_;
    }
}

bool BipartiteGraph::findMatch(int u) {
    // u -> v
    for (int e = head_[u]; ~e; e = edges_[e].next) {
        int v = edges_[e].to;
        if (!visit_[v]) {
            visit_[v] = true;
            int vpre = pre_[v];
            pre_[v] = u;
            if (vpre == -1 || findMatch(vpre)) {
                return true;
            }
            pre_[v] = vpre;
        }
    }
    return false;
}


void BipartiteGraph::dye() {
    memset(color_, -1, sizeof(color_));
    for (int i = 0; i <= vertexcount_; ++i) {
        dyeDFS(-1, i, 0);
    }
}

void BipartiteGraph::dyeDFS(int fat, int u, int c) {
    if (color_[u] != -1) {
        return;
    }
    color_[u] = c;
    for (int e = head_[u]; ~e; e = edges_[e].next) {
        int v = edges_[e].to;
        dyeDFS(u, v, 1 - c);
    }
}

void BipartiteGraph::doAddEdge(int u, int v) {
    edges_[edgecount_] = Edge(v, head_[u]);
    head_[u] = edgecount_++;
}

void BipartiteGraph::initialize(int n) {
    vertexcount_ = n;
    edgecount_ = 0;
    memset(head_, -1, sizeof(head_));
}

void BipartiteGraph::addEdge(int u, int v) {
    doAddEdge(u, v);
    doAddEdge(v, u);
}

int BipartiteGraph::getMaxMatch() {
    dye();
    int cnt = 0;
    memset(pre_, -1, sizeof(pre_));
    for (int i = 0; i <= vertexcount_; ++i) {
        if (color_[i] == 0) {
            memset(visit_, false, sizeof(visit_));
            if (findMatch(i)) {
                ++cnt;
            }
        }
    }
    return cnt;
}

void BipartiteGraph::getMaxMatchPath(int& maxMatch, int left[], int right[]) {
    maxMatch = getMaxMatch();
    int matchCnt = 0;
    for (int i = 0; i <= vertexcount_; ++i) {
        if (color_[i] == 1 && pre_[i] != -1) {
            left[matchCnt] = pre_[i];
            right[matchCnt] = i;
            ++matchCnt;
        }
    }
}

//****** ����ͼ���ƥ��ģ��(��ʽǰ����) ******

int n, m;
char mat[45][45];
int matId[45][45];

int dir[4][2] = {
    { 0, 1 },
    { 0, -1 },
    { 1, 0 },
    { -1, 0 }
};

#define MARK '*'

BipartiteGraph bg;
int cnt;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        cnt = 0;
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; ++i) {
            scanf("%s", mat[i]);
            for (int j = 0; j < m; ++j) {
                if (mat[i][j] == MARK) {
                    matId[i][j] = ++cnt;
                }
            }
        }
        bg.initialize(cnt);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mat[i][j] != MARK) {
                    continue;
                }
                for (int k = 0; k < 4; ++k) {
                    int ti = i + dir[k][0];
                    int tj = j + dir[k][1];
                    if (ti < 0 || ti >= n || tj < 0 || tj >= m) continue;
                    if (mat[ti][tj] != MARK) continue;
                    bg.addEdge(matId[i][j], matId[ti][tj]);
                }
            }
        }
        printf("%d\n", cnt - bg.getMaxMatch());
    }


    return 0;
}