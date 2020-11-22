/*
Manacher�㷨������ַ�������ģ� 
   1.���ַ����������һ��ȫ���ַ������ַ���ת�����������ȣ� 
   2.����ö��ÿ���ַ�Ϊ�����ᣬ�����i���ַ�������İ뾶p[i];
      a.����֮ǰ�ļ��������p[i]��ʼֵ��
      b.������չ������p[i]ֵ��
      c.����i+p[i]���º��������᣻
      d.����2*p[i]-1��������ĳ��� 
Author: WhereIsHeroFrom
Update Time: 2018-3-24
Algorithm Complexity: O(n)
*/

#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 1000010
int p[MAXN];
int n, tmp[MAXN];
 
int Min(int a, int b) {
    return a < b ? a : b;
}

void ManacherPre(int *a) {
    int i;
    for(i = 0; i < n; ++i) {
        tmp[i] = a[i];
    }
    for(i = 0; i < n; ++i) {
        a[2*i] = -1;
        a[2*i+1] = tmp[i];
    }
    a[2*i] = -1;
    a[2*i+1] = '\0';
}

int Manacher(int *a) {
    int ct = 0, r = 0, maxLen = 1;
    p[0] = 1;
    int m = 2*n+1; 
    for(int i = 1; i < m; ++i) {
        // 1.����p[i]��ʼֵ 
        if(i < r) {
            p[i] = Min(p[2*ct-i], r-i);
        }else {
            p[i] = 1;
        }
        // 2.����p[i]������Ӧ�ﵽp[i]���ֵ 
        while(i-p[i]>=0 && a[i-p[i]] == a[i+p[i]])
            ++p[i];
        
        // 3.����ct
        if(p[i] + i > r) {
            ct = i;
            r = p[i] + i;
        }
        //printf("%d (%d)\n", a[i], p[i]);
    }
    return maxLen; 
}

int a[MAXN];
// ÿ��Ԫ�����󵥵���������뾶 
int q[MAXN];

int main() {
    int i, t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; ++i) scanf("%d", &a[i]);        
        
        q[0] = 1;
        for(i = 1; i < n; ++i) {
            if(a[i-1] <= a[i]) {
                q[i] = q[i-1] + 1; 
            }else {
                q[i] = 1;
            }
        }
        
        ManacherPre(a);
        Manacher(a);
        

        int m = 2*n-1, maxLen = 0;
        for(i = 0; i < m; ++i) {
            if(i & 1) {
                int v = Min(p[i] - 1, 2*q[i/2]-1);
                if(v > maxLen) maxLen = v;
            }else {
                int v = Min(p[i] - 1, 2*q[i/2-1]);
                if(v > maxLen) maxLen = v;
            }
        }
        printf("%d\n", maxLen);
    }
    return 0;
} 
