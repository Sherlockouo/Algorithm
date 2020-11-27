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
char strTmp[MAXN];
 
int Min(int a, int b) {
    return a < b ? a : b;
}

void ManacherPre(char *str) {
    strcpy(strTmp, str);
    int i;
    for(i = 0; strTmp[i]; ++i) {
        str[2*i] = '$';
        str[2*i+1] = strTmp[i];
    }
    str[2*i] = '$';
    str[2*i+1] = '\0';
}

int Manacher(char *str) {
    int ct = 0, r = 0, maxLen = 1;
    p[0] = 1;
    for(int i = 1; str[i]; ++i) {
        // 1.����p[i]��ʼֵ 
        if(i < r) {
            p[i] = Min(p[2*ct-i], r-i);
        }else {
            p[i] = 1;
        }
        // 2.����p[i]������Ӧ�ﵽp[i]���ֵ 
        while(i-p[i]>=0 && str[i-p[i]] == str[i+p[i]])
            ++p[i];
        
        // 3.����ct
        if(p[i] + i > r) {
            ct = i;
            r = p[i] + i;
        }
        // 4.��������� 
        if(2*p[i]-1 > maxLen) {
            maxLen = 2*p[i] - 1;
        }
    }
    return maxLen; 
}



char str[MAXN];

int main() {
    while(scanf("%s", str) != EOF) {
        ManacherPre(str);
        int len = Manacher(str);
        printf("%d\n", len/2);
    }
    return 0;
} 

