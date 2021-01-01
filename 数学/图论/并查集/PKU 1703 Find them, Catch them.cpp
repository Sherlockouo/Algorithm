/*
���鼯 : ���滷

��������ʽ�ϲ�����һ����Ȳ��ᳬ�� log(n) ������
����ͨ�� O(log(n)) ��ʱ�����ҵ�ÿ���ڵ����ȣ�

����������ڵ� (x,y)���ֱ���� ��(rx, ry)
1��rx == ry�� ������ͬ��ż��������滷�������ô���
2��rx != ry�������Ȳ�ͬ��ż������Ҫ�� ������С���ǿ�������һ��α����㣬Ȼ���ٽ��кϲ���

*/
#include <iostream>

using namespace std;


const int MAXN = 1003010;
int fset[MAXN], rk[MAXN];
int n;

void init_set(int n) {
    for (int i = 1; i < MAXN; ++i) {
        fset[i] = i;
        rk[i] = 0;
    }
}

int find_set(int x) {
    return (fset[x] == x) ? x : find_set(fset[x]);
}

int find_depth(int x) {
    return (fset[x] == x) ? 0 : 1 + find_depth(fset[x]);
}

int add_set(int x) {
    fset[x] = ++n;
    rk[fset[x]] = rk[x] + 1;
    return fset[x];
}

bool union_set(int x, int y) {
    int fx = find_set(x), fy = find_set(y);
    int dx = find_depth(x), dy = find_depth(y);
    bool bfit = (dx - dy) % 2;

    if (fx == fy) {
        // ���ڵ�һ��������Ҫ�ж���ż�ԣ�������Ϊż����˵���������滷
        return bfit;
    }
    if (bfit) {
        // ��ż�� ��һ�µ���������С���Ǹ���Ҫ����һ�� α�� 
        if (rk[fx] < rk[fy]) {
            fx = add_set(fx);
        }
        else {
            fy = add_set(fy);
        }
    }

    // ��ż�� һ�µ������ֱ�����Ӹ�
    if (rk[fx] == rk[fy]) {
        ++rk[fx];
        fset[fy] = fx;
    }
    else if (rk[fx] < rk[fy]) {
        fset[fx] = fy;
    }
    else {
        fset[fy] = fx;
    }

    return true;
}

enum QSType {
    QST_NOT_SURE = 0,
    QST_DIFF = 1,
    QST_SAME = 2
};

QSType quest_set(int x, int y) {
    int fx = find_set(x), fy = find_set(y);
    int dx = find_depth(x), dy = find_depth(y);
    bool bfit = (dx - dy) % 2;
    if (fx != fy) {
        return QST_NOT_SURE;
    }
    if (fx == fy) {
        return !bfit ? QST_SAME : QST_DIFF;
    }
}

void print_set(QSType tp) {
    if (tp == QST_NOT_SURE) printf("Not sure yet.\n");
    else if (tp == QST_DIFF) printf("In different gangs.\n");
    else if (tp == QST_SAME) printf("In the same gang.\n");
}

int main() {
    int t, cas = 0;
    int m, i, x, y;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        init_set(n);
        bool f = false;
        char ch[10];

        for (i = 0; i < m; ++i) {
            scanf("%s %d %d", ch, &x, &y);
            if (ch[0] == 'D') {
                union_set(x, y);
            }
            else {
                print_set(quest_set(x, y));
            }
        }
    }

    return 0;
}