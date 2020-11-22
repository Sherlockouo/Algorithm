/*
���⣺
    ����һ������ΪL���ַ���������L��ǰ׺ΪC[1:1], C[1:2], ..., C[1:L]����i��ǰ׺��C[1:i]�ַ�������ԭ���г��ֵĴ�����ΪK[i]����sum{K[i]| 1<=i<=L} % 256��
��⣺KMP + DP
    ��������KMP����next���顣
    dp[i]��ʾ�Ե�i��Ԫ�ؽ�β���Ӵ��ǡ�ԭ��ǰ׺�����ַ����ĸ�����
    �����ԣ���� next[i] == 0, dp[i] = 0;
            ��� next[i] > 0, dp[i] = dp[next[i]] + 1��
    ע��
        ������Ҫ׷�ݵ�next[i]�ĺ��壺          S[1 : next[i]] == S[i-next[i]+1 : i]     ("==" ������ȫƥ�䣩�� 
    ��j = next[i], ��next[j]�Ϳ��Ա�ʾ���£�   S[1 : next[j]] == S[j-next[j]+1 : j] == S[next[i]-next[j]+1 : next[i]] == S[i-next[j]+1 : i]
    ����ͨ�׵ı�ʾ��
        ��i, j, k, l...���� j=next[i], k=next[j], l = next[k]...ʱ��
            �� S[i-next[i]+1 : i]
               S[i-next[j]+1 : i]
               S[i-next[k]+1 : i]
               S[i-next[l]+1 : i]...
            ��Ϊ��i��β���ַ������������ǡ�ԭ��ǰ׺����
    ��ô��i��β���ַ�������ԭ��S��ǰ׺���ַ���һ����   S[i-next[i]+1 : i]��S[i-next[next[i]]+1 : i]��S[i-next[next[next[i]]]+1 : i]...
    �����״̬ת�Ʒ��� dp[i] = dp[next[i]] + 1�� ��������
*/

#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 100010
#define MOD 256

int pre[MAXN];
int dp[MAXN];    // dp[i] ��ʾ��i��Ԫ��Ϊĩβ���Ӵ���ǰ׺�ĸ���
char str[MAXN];

void get_next(char *str, int len) {
    int i, j;
    pre[1] = 0;
    for(i = 2; i <= len; i++) {
        j = pre[i-1];
        while(j > 0 && str[i] != str[j+1] ) j = pre[j];
        if(str[i] == str[j+1]) j++;
        pre[i] = j;
    }
}

int main() {
    int i;
    while(scanf("%s", &str[1]) != EOF) {
        int n = strlen(&str[1]);
        get_next(str, n);
        for(i = 0; i <= n; i++) {
            dp[i] = 0;
        }
        int sum = n % MOD;
        for(i = 1; i <= n; i++) {
            if(pre[i]) {
                dp[i] = (dp[pre[i]] + 1) % MOD;
            }else {
                dp[i] = 0;
            }
            sum = (sum + dp[i]) % MOD;
        }
        printf("%d\n", sum);
    }
    return 0;
}

