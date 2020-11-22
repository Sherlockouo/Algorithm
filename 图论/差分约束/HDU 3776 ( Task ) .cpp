/*
   ���⣺�������룬��Ϸ���task����ʹ�����е���������� 
    1. task i starts at least A minutes later than task j
    2. task i starts within A minutes of the starting time of task j
   ��⣺���Լ��
          ���ڵ�һ����������������ʽ��   d[i]-d[j] >= A
          ���ڵڶ�����������������ʽ��   0 <= d[i]-d[j] <= A
       ����������ת���� a-b >= c��Ȼ������ b->a(ȨֵΪc)����������û�б������ĵ���һ���·���� 
*/ 

#include <iostream>
#include <queue>

using namespace std;

#define MAXN 50010
#define MAXE 1000020
#define INF 100000000

/*
    �����Ȩ�� 
*/ 
class Edge {
public:    
    int edgeValue; 
    int toVertex;
    Edge* next;

    Edge() {}
    void reset(int _to, int _val, Edge* _next) {
        toVertex = _to;
        edgeValue = _val;
        next = _next;
    }
};
typedef Edge* EdgePtr;

/*
    ����ͼ 
*/
class Graph {
    EdgePtr *head;
    Edge *edges;
    int edgeCount;
    int vertexCount;

    Graph() {
        // ��ʽǰ���� �洢
        // �ڽӱ��׽��
        head = new EdgePtr[MAXN];
        // ���� 
        dist = new int[MAXN];
        // ������ʴ��� 
        visit = new int[MAXN]; 
        // ���ڴ��
        edges = new Edge[MAXE];
    }
    ~Graph() {
        delete [] edges;
        delete [] head;
        delete [] dist;
        delete [] visit;
    }
public:
    int *visit;
    int *dist;
    
    void init(int vCount);
    void initDist();
    void addConstraint(int a, int b, int c); 
    void addEdge(int from, int to, int value);
    bool spfa(int start);

    static Graph& Instance() {
        static Graph inst;
        return inst; 
    }
};

void Graph::init(int vCount) {
    vertexCount = vCount;
    edgeCount = 0;
    for(int i = 0; i <= vCount; i++) {
        head[i] = NULL;
    }
}

/*
    ����һ������������
    a - b >= c 
    if(b + c > a) {
        a = b + c; 
        // ����и��£���Ϊ���·������ 
    }
    ���ʾb����c�������ܹ�����a���򽨱����£�b->a(ȨΪc) 
*/

void Graph::addConstraint(int a, int b, int c) {
    //printf("%d-%d>=%d\n", a, b, c);
    addEdge(b, a, c);
}

void Graph::addEdge(int from, int to, int value) {
    edges[edgeCount].reset(to, value, head[from]);
    head[from] = &edges[edgeCount++];
}

void Graph::initDist() {
    for(int i = 0; i <= vertexCount; ++i) {
        dist[i] = -INF;
        visit[i] = 0;
    }
}

bool Graph::spfa(int start) {
    int i;
    Edge *e;
    dist[start] = 1;
    visit[start] = 1;
    queue<int> Q;
    Q.push(start);
    while( !Q.empty() ) {
        int u = Q.front();
        Q.pop();
        if( visit[u]++ > vertexCount + 1) {
            return false;
        }
         
        for(e = head[u]; e; e = e->next) {
            int &v = e->toVertex;
            int &val = e->edgeValue;
            if( dist[u] + val > dist[v] ) {
                dist[v] = dist[u] + val;
                Q.push(v);
            }
        }
    }
    return true;
}


char str[1000];
int num[10];

void get_num(char *str, int *num, int& flag) {
    int s = 0;
    num[0] = 0;
    for(int i = 0; str[i]; ++i) {
        if(str[i]=='l' && str[i+1] == 'e' && str[i+2]=='a' && str[i+3] == 's' && str[i+4] == 't') {
            flag = 1;
        }
        if(str[i]=='w' && str[i+1] == 'i' && str[i+2]=='t' && str[i+3] == 'h' && str[i+4] == 'i') {
            flag = 2;
        }
        if(str[i] >= '0' && str[i] <= '9') {
            s = s * 10 + (str[i] - '0');
        }else {
            if(s) {
                num[ ++num[0] ] = s;
                s = 0;
            }
        }
    }
    if(s) {
        num[ ++num[0] ] = s;
        s = 0;
    }
}

int main() {
    int n, m;
    int i;
    while(scanf("%d", &n) != EOF && n) {
        Graph &g = Graph::Instance();
        g.init(n);
        scanf("%d", &m);
        getchar();
        while(m--) {
            gets(str);
            int flag = 0;
            get_num(str, num, flag);
            if(flag==1) {
                g.addConstraint(num[1], num[3], num[2]);
            }else if(flag == 2) {
                g.addConstraint(num[1], num[3], 0);
                g.addConstraint(num[3], num[1], -num[2]);
            }
        }
        g.initDist();
        for(i = 1; i <= n; i++) {
            if(g.visit[i]) continue;
            if(!g.spfa(i)) {
                printf("Impossible.\n");
                break;
            }
        }
        if(i == n+1) {
            int Min = INF;
            for(i = 1; i <= n; i++) {
                if(g.dist[i] < Min) {
                    Min = g.dist[i];
                }
            }
            
            for(i = 1; i <= n; i++) {
                if(i > 1) {
                    printf(" ");
                }
                printf("%d", g.dist[i] - Min + 1);
            }
            puts("");
        }
    }
    return 0;
} 

