#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//****** ����ͼ���ƥ��ģ��(��ʽǰ����) ******

const int VMAX = 2510;
const int EMAX = 200010;

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
    memset(pre_, -1, sizeof(pre_));
    memset(head_, -1, sizeof(head_));
    memset(color_, -1, sizeof(color_));
}



void BipartiteGraph::addEdge(int u, int v) {
    doAddEdge(u, v);
    doAddEdge(v, u);
}

int BipartiteGraph::getMaxMatch() {
    dye();
    int cnt = 0;
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
//****** ����ͼ���ƥ��ģ��(��ʽǰ����) ******

char mat[52][52];

struct Line {
    int idx;
    int min, max;
    Line() {}
    Line(int _i, int _min, int _max) : idx(_i), min(_min), max(_max) {}

    bool intersect(const Line & l) {
        return (l.min <= idx && idx <= l.max) && (min <= l.idx && l.idx <= max);
    }
};

Line L[2600], R[2600];
int LSize, RSize;

int main() {
    BipartiteGraph bg;
    int i, j, k;
    int r, c;
    while (scanf("%d %d", &r, &c) != EOF) {
        memset(mat, 0, sizeof(mat));

        for (i = 0; i < r; ++i) {
            scanf("%s", mat[i]);
        }
        LSize = 0;
        RSize = 0;

        for (i = 0; i < r; ++i) {
            for (j = 0; j < c; ++j) {
                if (mat[i][j] == '*') {
                    for (k = j; k <= c; ++k) {
                        if (mat[i][k] != '*') {
                            break;
                        }
                    }
                    L[++LSize] = Line(i, j, k - 1);
                    j = k;
                }
            }
        }

        for (i = 0; i < c; ++i) {
            for (j = 0; j < r; ++j) {
                if (mat[j][i] == '*') {
                    for (k = j; k <= r; ++k) {
                        if (mat[k][i] != '*') {
                            break;
                        }
                    }
                    R[++RSize] = Line(i, j, k - 1);
                    j = k;
                }
            }
        }

        bg.initialize(LSize + RSize);

        for (i = 1; i <= LSize; ++i) {
            for (j = 1; j <= RSize; ++j) {
                if (L[i].intersect(R[j])) bg.addEdge(i, LSize + j);
            }
        }

        printf("%d\n", bg.getMaxMatch());
    }

    return 0;
}