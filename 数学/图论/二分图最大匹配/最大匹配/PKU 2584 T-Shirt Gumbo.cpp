#pragma   comment(linker, "/STACK:1024000000,1024000000")

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

//****** ����ͼ���ƥ��ģ��(��ʽǰ����) ******

const int VMAX = 4000;
const int EMAX = 250010;

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
    int getTreeMaxMatch();
    int getMaxMatch();
    void getMaxMatchPath(int& maxMatch, int left[], int right[]);
    bool isBipartite();
private:
    int max(int a, int b);
    bool findMatch(int u);               // �������㷨������·
    void findTreeMatch(int fat, int u);
    void dye();
    bool dyeBFS(int u);                  // bfs �Զ������Ⱦɫ
    void doAddEdge(int u, int v);

    bool isVisited(int v);
    void setVisit(int v);
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
    int visit_[VMAX];            // �������㷨������·ʱ�� visit
    int visittag_;

    // ����DP ��ƥ��
    int dp_[VMAX][2];            // ��������DP���������ƥ��
    // 0 �Ե�ǰ���Ϊ����㣬���ӽ��֮��û��ƥ���
    // 1 �Ե�ǰ���Ϊ���ڵ㣬���ӽ����һ��ƥ��ߣ�Ҳ����һ���ˣ�
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

int BipartiteGraph::max(int a, int b)
{
    return a > b ? a : b;
}

bool BipartiteGraph::findMatch(int u) {
    // u -> v
    if (u == -1) {
        return true;
    }
    for (int e = head_[u]; ~e; e = edges_[e].next) {
        int v = edges_[e].to;
        if (!isVisited(v)) {
            setVisit(v);
            if (findMatch(pre_[v])) {
                pre_[v] = u;
                return true;
            }
        }
    }
    return false;
}


void BipartiteGraph::findTreeMatch(int fat, int u) {
    dp_[u][0] = 0;
    for (int e = head_[u]; ~e; e = edges_[e].next) {
        int v = edges_[e].to;
        if (v == fat) {
            continue;
        }
        findTreeMatch(u, v);
        dp_[u][0] += max(dp_[v][0], dp_[v][1]);
    }

    dp_[u][1] = 0;
    for (int e = head_[u]; ~e; e = edges_[e].next) {
        int v = edges_[e].to;
        if (v == fat) {
            continue;
        }
        // ѡ�� (u, v) ��Ϊƥ��ߣ���ô v ����ѡ���ʱ���Ȼ����ѡ��ƥ��ߣ�����ȡ dp_[v][0] �����
        int s = dp_[u][0] - max(dp_[v][0], dp_[v][1]) + 1 + dp_[v][0];
        if (s > dp_[u][1]) {
            dp_[u][1] = s;
        }
    }
}

void BipartiteGraph::dye() {
    memset(color_, -1, sizeof(color_));
    for (int i = 0; i <= vertexcount_; ++i) {
        if (color_[i] == -1) {
            dyeBFS(i);
        }
    }
}

bool BipartiteGraph::dyeBFS(int u) {
    queue <int> Q;
    Q.push(u);
    color_[u] = 0;

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();


        for (int e = head_[u]; ~e; e = edges_[e].next) {
            int v = edges_[e].to;
            if (color_[v] == -1) {
                color_[v] = 1 - color_[u];
                Q.push(v);
            }
            else if (color_[v] == color_[u]) {
                return false;
            }
        }
    }
    return true;
}

void BipartiteGraph::doAddEdge(int u, int v) {
    edges_[edgecount_] = Edge(v, head_[u]);
    head_[u] = edgecount_++;
}

bool BipartiteGraph::isVisited(int v)
{
    return visit_[v] == visittag_;
}

void BipartiteGraph::setVisit(int v)
{
    visit_[v] = visittag_;
}

void BipartiteGraph::initialize(int n) {
    vertexcount_ = n;
    edgecount_ = 0;
    visittag_ = 0;
    memset(head_, -1, sizeof(head_));
    memset(visit_, 0, sizeof(visit_));
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
            ++visittag_;
            if (findMatch(i)) {
                ++cnt;
            }
        }
    }
    return cnt;
}

int BipartiteGraph::getTreeMaxMatch() {
    // ������� 0
    addEdge(0, 1);
    findTreeMatch(0, 1);
    return max(dp_[1][0], dp_[1][1]);
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

bool BipartiteGraph::isBipartite() {
    memset(color_, -1, sizeof(color_));
    for (int i = 0; i <= vertexcount_; ++i) {
        if (color_[i] == -1 && !dyeBFS(i)) {
            return false;
        }
    }
    return true;
}

//****** ����ͼ���ƥ��ģ��(��ʽǰ����) ******

char str[100];
const char SMLXT[] = "SMLXT";

int getID(char c) {
    for (int i = 0; SMLXT[i]; ++i) {
        if (SMLXT[i] == c) {
            return i;
        }
    }
}

int X[50][2];
int xSize[5];

BipartiteGraph bg;


int main() {
    int n;
    while (scanf("%s", str) != EOF) {
        if (strcmp(str, "ENDOFINPUT") == 0) {
            break;
        }
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%s", str);
            X[i][0] = getID(str[0]);
            X[i][1] = getID(str[1]);
        }
        bg.initialize(n + 110);

        for (int i = 0; i < 5; ++i) {
            scanf("%d", &xSize[i]);

            for (int j = 0; j < n; ++j) {
                if (X[j][0] <= i && i <= X[j][1]) {
                    for (int v = i * 5 + 1; v <= i * 5 + xSize[i]; ++v) {
                        bg.addEdge(j + 1, n + v);
                    }
                }
            }
        }
        scanf("%s", str);
        int ans = bg.getMaxMatch();
        if (ans == n) {
            printf("T-shirts rock!\n");
        }
        else {
            printf("I'd rather not wear a shirt anyway...\n");
        }
    }
    return 0;
}

/*

START 1
ST
0 0 1 0 0
END

START 2
SS TT
0 0 1 0 0
END

START 4
SM ML LX XT
0 1 1 1 0
END

ENDOFINPUT

*/