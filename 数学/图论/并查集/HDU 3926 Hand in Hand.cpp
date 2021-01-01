/*
���鼯��ͼ��ͬ���ж�
ÿ����ͼ��������Ϊ2������ÿ����ͼҪô�� ����Ҫô�� ����
���ݲ��鼯��ÿ������ͼ�����ռ��ϴ�С����������0��������1�������һ���ַ�����
�Ƚ������ַ����Ƿ���ȼ��ɣ�
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200010;
int fset[MAXN], fcircle[MAXN], sum[MAXN];
vector <int> setlist[MAXN];

void init_set(int n) {
    for (int i = 1; i <= n; ++i) {
        fset[i] = i;
        fcircle[i] = 0;
        setlist[i].clear();
    }
}

int find_set(int x) {
    return (fset[x] == x) ? x : (fset[x] = find_set(fset[x]));
}

bool union_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx != fy) {
        fset[fx] = fy;
        return true;
    }
    return false;
}

int n, m;

vector <int> xGraph[2];

int main() {
    int t, n, m;
    int i, x, y;
    int cas = 0;

    while (scanf("%d", &t) != EOF) {
        while (t--) {
            for (int k = 0; k < 2; ++k) {
                scanf("%d %d", &n, &m);
                init_set(n);

                while (m--) {
                    scanf("%d %d", &x, &y);
                    if (!union_set(x, y)) {
                        fcircle[x] = fcircle[y] = 1;
                    }
                }
                for (i = 1; i <= n; ++i) {
                    int root = find_set(i);
                    setlist[root].push_back(i);
                    fcircle[root] = (fcircle[root] || fcircle[i]);
                }
                xGraph[k].clear();
                for (i = 1; i <= n; ++i) {
                    if (setlist[i].size()) {
                        xGraph[k].push_back(setlist[i].size() << 1 | fcircle[i]);
                    }
                }
                sort(xGraph[k].begin(), xGraph[k].end());
            }

            bool isSame = true;
            if (xGraph[0].size() != xGraph[1].size()) {
                isSame = false;
            }
            else {
                for (i = 0; i < xGraph[0].size(); ++i) {
                    if (xGraph[0][i] != xGraph[1][i]) {
                        isSame = false;
                        break;
                    }
                }
            }
            printf("Case #%d: %s\n", ++cas, isSame ? "YES" : "NO");

        }

    }
    return 0;
}