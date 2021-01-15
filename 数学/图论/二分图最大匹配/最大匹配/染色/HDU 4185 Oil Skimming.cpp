#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//****** ����ͼ���ƥ��ģ��(��ʽǰ����) ******

const int VMAX = 360010;
const int EMAX = 360010;

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

BipartiteGraph bg;

#define MAXN 605
char mat[MAXN][MAXN];
int ID[MAXN][MAXN], IDSize, IDHash[MAXN*MAXN];
int dir[4][2] = {
    { 0, 1 },
    { 0, -1 },
    { 1, 0 },
    { -1, 0 }
};

int main() {
    int t, cas = 0;
    int n;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        IDSize = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%s", mat[i]);
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == '#') {
                    ID[i][j] = ++IDSize;
                    IDHash[ID[i][j]] = i*n + j;
                }
            }
        }
        bg.initialize(IDSize);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j){

                if (mat[i][j] == '.')continue;
                for (int k = 0; k < 4; ++k) {
                    int ti = i + dir[k][0];
                    int tj = j + dir[k][1];
                    if (ti < 0 || tj < 0 || ti >= n || tj >= n) continue;
                    if (mat[ti][tj] == '.') continue;
                    bg.addEdge(ID[i][j], ID[ti][tj]);
                }
            }
        }
        printf("Case %d: %d\n", ++cas, bg.getMaxMatch());

    }
    return 0;
}