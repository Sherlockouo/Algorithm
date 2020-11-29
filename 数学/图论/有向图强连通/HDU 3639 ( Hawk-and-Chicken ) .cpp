#include <iostream>
#include <vector>
using namespace std;

#define MAXN 10010
#define MAXM 200020

class Edge {
public:
	int u, v, next;
	Edge(){
	}
	Edge(int _u, int _v, int _n) {
		u = _u;
		v = _v;
		next = _n;
	}
};

int n;
int head_p[MAXN], tot_p;
int head_n[MAXN], tot_n;
Edge edges_p[MAXM], edges_n[MAXM];

// һЩ������Ϣ
// �������ͼ����ʱ���¼ �������� �ĵ�
int torder[2 * MAXN], nowtime;
bool visited[MAXN];

int scc;         // ǿ��ͨ��֧��
int id[MAXN];    // ǿ��ͨ���

void reset() {
	memset(head_p, -1, sizeof(head_p));
	memset(head_n, -1, sizeof(head_n));
	tot_p = 0, tot_n = 0;
}

void addEdge(int u, int v, bool inv) {
	if (!inv) {
		// �����
		edges_p[tot_p] = Edge(u, v, head_p[u]);
		head_p[u] = tot_p++;
	}
	else {
		// �����
		edges_n[tot_n] = Edge(v, u, head_n[v]);
		head_n[v] = tot_n++;
	}
}

// ��������ͼ����¼ÿ��������ʱ��
void dfs_post(int u) {
	if (visited[u]) {
		return;
	}
	visited[u] = true;
	for (int i = head_p[u]; i != -1; i = edges_p[i].next) {
		int v = edges_p[i].v;
		dfs_post(v);
	}
	torder[nowtime++] = u;
}

// ������������¼ÿ�������ɱ�����ʱ��
void postTraversal() {
	nowtime = 0;
	memset(visited, false, sizeof(visited));

	for (int i = 1; i <= n; i++) {
		dfs_post(i);
	}
}

// �������ͼ����¼ÿ�����ǿ��ͨ��֧��� (0 - base)
void dfs_pre(int u) {
	if (visited[u]) {
		return;
	}
	visited[u] = true;
	id[u] = scc;
	for (int i = head_n[u]; i != -1; i = edges_n[i].next) {
		int v = edges_n[i].v;
		dfs_pre(v);
	}
}

// ǿ��ͨ��֧
void kosaraju() {
	scc = 0;
	memset(visited, false, sizeof(visited));

	for (int i = nowtime - 1; i >= 0; i--) {
		int u = torder[i];
		if (!visited[u]) {
			dfs_pre(u);
			scc++;

		}
	}
}


vector <int> vec[MAXN];
vector <int> ans;
int blockCnt[MAXN];
int blockHas[MAXN];
int tot;
int has[MAXN], T;

int orgHas[MAXN];

void dfs(int u) {
	if (has[u] == T) {
		return;
	}
	has[u] = T;
	tot += blockCnt[u];

	for (int i = vec[u].size() - 1; i >= 0; i--) {
		dfs(vec[u][i]);
	}
}

int main() {
	int t;
	int m;
	int i, j;
	int cases = 1;
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d", &n, &m);
		reset();
		while (m--) {
			int x, y;
			scanf("%d %d", &x, &y);
			x++;
			y++;
			addEdge(x, y, false);
			addEdge(x, y, true);
		}
		postTraversal();
		kosaraju();

		for (i = 0; i < scc; i++) {
			vec[i].clear();
			blockCnt[i] = 0;
		}
		ans.clear();

		for (i = 1; i <= n; i++) {
			int u = id[i];
			blockCnt[u] ++;
			for (j = head_p[i]; j != -1; j = edges_p[j].next) {
				int v = id[edges_p[j].v];
				if (u != v) {
					// ע�⣬���ｨ�����Ƿ����
					vec[v].push_back(u);

				}
			}
		}
		T = 0;
		memset(has, 0, sizeof(has));
		// ö��ÿ�������ĵ�
		for (i = 0; i < scc; i++) {
			tot = -1;
			T++;
			dfs(i);
			blockHas[i] = tot;
		}
		int Max = -1;

		for (i = 1; i <= n; i++) {
			orgHas[i] = blockHas[id[i]];
			if (orgHas[i] > Max) {
				Max = orgHas[i];
				ans.clear();
				ans.push_back(i - 1);
			}
			else if (orgHas[i] == Max) {
				ans.push_back(i - 1);
			}
		}
		printf("Case %d: %d\n", cases++, Max);
		for (i = 0; i < ans.size(); i++) {
			if (i) printf(" ");
			printf("%d", ans[i]);
		}
		puts("");
	}
	return 0;
}

/*
10
4 3
3 2
2 0
2 1

3 3
1 0
2 1
0 2

6 7
0 1
0 2
1 3
2 3
3 4
4 5
5 3

*/