#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//****** ����ͼ���ƥ��ģ��(��ʽǰ����) ******

const int VMAX = 10010;
const int EMAX = 40010;

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

#define MAXN 110

int mat[MAXN][MAXN];
int XID[MAXN][MAXN], XIDSize;
int YID[MAXN][MAXN], YIDSize;

BipartiteGraph bg;
int n, m, k;

int getMatch(int r, int c) {
    int i, j;


    bg.initialize(n + m);

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; j++) {
            if (i == r && j == c) {
                continue;
            }
            if (mat[i][j]) {
                bg.addEdge(i + 1, j + n + 1);
            }
        }
    }
    return bg.getMaxMatch();
}


int main() {
    int i, j;
    int cas = 0;
    while (scanf("%d %d %d", &n, &m, &k) != EOF) {
        memset(mat, 0, sizeof(mat));

        while (k--) {
            int x, y;
            scanf("%d %d", &x, &y);
            --x, --y;
            mat[x][y] = 1;
        }
        XIDSize = 0, YIDSize = 0;

        for (i = 0; i < n; ++i) {
            for (j = 0; j < m; ++j) {
                if (mat[i][j]) {
                    ++XIDSize;
                    while (mat[i][j]) {
                        XID[i][j] = XIDSize;
                        ++j;
                    }
                }

            }
        }
        for (i = 0; i < m; ++i) {
            for (j = 0; j < n; ++j) {
                if (mat[j][i]) {
                    ++YIDSize;
                    while (mat[j][i]) {
                        YID[j][i] = YIDSize;
                        ++j;
                    }
                }

            }
        }

        int l = getMatch(-1, -1);
        int ans = 0;

        for (i = 0; i < n; ++i) {
            for (j = 0; j < m; ++j) {
                if (mat[i][j]) {
                    if (getMatch(i, j) != l) {
                        ++ans;
                    }
                }
            }
        }

        printf("Board %d have %d important blanks for %d chessmen.\n", ++cas, ans, l);

    }
}

