/*
    ����  1,2,3,4...n ��ľ������ȥ�����ٸ���ʹ��ʣ�µ�ľ��������������Σ�

    IDA*

    i �Ӵ�Сö��
        ö�� i ������������������� i �������ź�����������ڵ�ֻҪ��һ�����㣺����֮�ʹ��ڵ�����
    ��ô���ַ����Ͳ����У�һ���ҵ����е������������㣺����֮�ʹ��ڵ����ߣ���Ϊһ�����з�����ֱ�ӷ��أ���Ϊ n-i��

    ��֦��ע��������ʱ�������С����������ʣ���ö�ٸ�������Ѿ�С��ʵ����Ҫö�ٵĸ�����˵������������������У�ֱ�ӷ��أ�

*/
#include <iostream>

using namespace std;

int has[21];
int sta[21], top;


bool dfs(int depth, int idx, int maxn) {

    if (depth == 0) {
        int bfind = false;
        for (int i = 0; i + 2 < top; ++i) {
            if (sta[i] + sta[i + 1] > sta[i + 2]) {
                bfind = true;
            }
        }
        return (!bfind);
    }

    // ǿ��֦
    if (depth > maxn - idx + 1) {
        return false;
    }

    for (int i = idx; i <= maxn; ++i) {
        sta[top++] = i;
        if (dfs(depth - 1, i + 1, maxn)) {
            return true;
        }
        --top;
    }
    return false;
}

int IDA_dfs(int n) {
    if (n < 3) {
        return 0;
    }
    top = 0;
    for (int i = n; i >= 0; --i) {
        if (dfs(i, 1, n)) {
            return n - i;
        }
    }
}

int main() {
   
    int t, cas = 0, n;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        printf("Case #%d: %d\n", ++cas, IDA_dfs(n));
    }

    return 0;
}
