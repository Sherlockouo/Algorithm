#include <iostream>
#include <cstring>

using namespace std;

//****** ����ͼ���ƥ��ģ��(��ʽǰ����) ******
// ���㷶Χ  ��ߵĵ�[1, X]���ұߵĵ�[1,Y]

const int VMAX = 110;
const int EMAX = 10010;

struct Edge {
    int to, next;

    Edge() {}
    Edge(int _t, int _n) : to(_t), next(_n) {}
};

class BipartiteGraph {
public:
    BipartiteGraph();
    virtual ~BipartiteGraph();
    void initialize(int lefts, int rights);
    void addEdge(int u, int v);
    int getMaxMatch();
private:
    bool findMatch(int u);       // �������㷨������·
private:
    int leftsize_, rightsize_;   // ���ҵ㼯����Ŀ

    //  ��ʽǰ����  
    Edge *edges_;                // �߼�
    int edgecount_;              // ���ñ���
    int head_[VMAX];             // ÿ���ڵ�߼�������ͷ

    int pre_[VMAX];              // �������㷨������·ʱ�� pre
    bool visit_[VMAX];           // �������㷨������·ʱ�� visit
};

BipartiteGraph::BipartiteGraph() :
edges_(NULL), leftsize_(0), rightsize_(0)
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

void BipartiteGraph::initialize(int lefts, int rights) {
    leftsize_ = lefts;
    rightsize_ = rights;
    edgecount_ = 0;
    memset(pre_, -1, sizeof(pre_));
    memset(head_, -1, sizeof(head_));
}


void BipartiteGraph::addEdge(int u, int v) {
    edges_[edgecount_] = Edge(v, head_[u]);
    head_[u] = edgecount_++;
}

int BipartiteGraph::getMaxMatch() {
    int cnt = 0;
    for (int i = 1; i <= leftsize_; ++i) {
        memset(visit_, false, sizeof(visit_));
        if (findMatch(i)) {
            ++cnt;
        }
    }
    return cnt;
}
//****** ����ͼ���ƥ��ģ��(��ʽǰ����) ******


int main() {
    BipartiteGraph bg;
    int i, j;
    int n, m, k, a, b, c;
    while (scanf("%d %d %d", &n, &m, &k) != EOF && n) {
        bg.initialize(n, m);
        while (k--) {
            scanf("%d %d %d", &a, &b, &c);
            if (b && c) {
                bg.addEdge(b, c);
            }
        }
        printf("%d\n", bg.getMaxMatch());
    }

    return 0;
}
