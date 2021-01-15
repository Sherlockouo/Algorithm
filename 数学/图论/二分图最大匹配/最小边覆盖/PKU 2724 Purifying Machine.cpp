#pragma   comment(linker, "/STACK:1024000000,1024000000")

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

//****** ����ͼ���ƥ��ģ��(��ʽǰ����) ******

const int VMAX = 2010;
const int EMAX = 4000010;

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

BipartiteGraph bg;
int P[12010], Has[20000];
int PSize;

void dfs(int depth, const char* str, int sum) {
    if (!str[depth]) {
        Has[sum] = 1;
        return;
    }
    if (str[depth] == '*') {
        dfs(depth + 1, str, sum << 1);
        dfs(depth + 1, str, sum << 1 | 1);
    }
    else {
        dfs(depth + 1, str, sum << 1 | (str[depth] - '0'));
    }
}

int main() {
    int n, m;
    char str[20];
    while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
        PSize = 0;
        memset(Has, 0, sizeof(Has));
        for (int i = 0; i < m; ++i) {
            scanf("%s", str);
            dfs(0, str, 0);
        }
        for (int i = 0; i < (1 << n); ++i) {
            if (Has[i]) {
                P[++PSize] = i;
            }
        }

        bg.initialize(PSize);

        for (int i = 1; i <= PSize; ++i) {
            for (int j = 1; j <= PSize; ++j) {
                int a = P[i];
                int b = P[j];
                int c = (a^b);             // ��������Ʋ�һλ����ô����Ȼ��2���ݣ�
                int d = c && ((c&(c - 1)) == 0);  // �����2���ݣ���ô��Ȼ���������ʽ��
                if (d) {
                    bg.addEdge(i, j);
                }
            }
        }
        printf("%d\n", PSize - bg.getMaxMatch());

    }


    return 0;
}

/*

7 7
5 2
1 3
1 6
1 5
3 4
6 7
4 5

*/

