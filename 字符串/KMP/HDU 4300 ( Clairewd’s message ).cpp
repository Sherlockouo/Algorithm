#include <iostream>

using namespace std;

#pragma warning(disable:4996)

#define NULL_MATCH (-1)
#define Type char
#define MAXN 1000010

/*
    "ababaaba"

*/
void GenNext(int *next, Type* M, int MLen) {
    // 0. �� NULL_MATCH(-1) ����һ��û����ǰ׺��0��λ��һ��û����ǰ׺������Ϊ NULL_MATCH
    int MPos = NULL_MATCH;
    next[0] = MPos;
    for (int TPos = 1; TPos < MLen; ++TPos) {
        // 1. M[TPos-MPos-1...TPos-1] �� M[0...MPos] ��ȫƥ�� 
        //    ��� M[TPos] �� M[MPos + 1] �Ƿ�ƥ�䣬��ƥ�䣬������һ�� MPos' = next[MPos]��
        while (MPos != NULL_MATCH && M[TPos] != M[MPos + 1])
            MPos = next[MPos];
        // 2. ��ȷƥ���ϣ����� MPos
        if (M[TPos] == M[MPos + 1]) MPos++;
        // 3. M[TPos-MPos...TPos] �� M[0...MPos] ��ȫƥ�� 
        next[TPos] = MPos;                                    
    }
    
    /*for (int i = 0; i < MLen; ++i) {
        printf("%d ", next[i]);
    }
    puts("");*/
    
}

int KMP(int *next, Type* M, int MLen, Type *T, int TLen) {
    // 1. �������ó� -1 ��Ŀ���ǣ�
    // �����Ϊ������� Ŀ�괮�Ŀմ� �� ƥ�䴮�Ŀմ� һ��ƥ��
    int MPos = NULL_MATCH;
    for (int TPos = (TLen+1)/2; TPos < TLen; ++TPos) {
        // 2. ǰ���� T[...TPos-1] == M[0...MPos] ��MPos == -1 ����������մ�ƥ�䣬ͬ������)
        //    ��� T[TPos] != M[MPos + 1]���� MPos = MPos' ����ƥ��
        while (MPos != NULL_MATCH && T[TPos] != M[MPos + 1])
            MPos = next[MPos];
        // 3. �� T[TPos] == M[MPos + 1] �� TPos++, MPos++;
        if (T[TPos] == M[MPos + 1]) MPos++;
        // 4. ƥ����ϣ����� Ŀ�괮 ��һ��ƥ���λ��
    }
    return MPos;
}



int Next[MAXN];
Type T[MAXN], TT[MAXN], M[MAXN];

char c[256];
char conv[256];

int main() {
    int MLen, i;
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", c);
        for (i = 0; c[i]; ++i) {
            conv[c[i]] = 'a' + i;
        }
        scanf("%s", T);
        for (i = 0; T[i]; ++i) {
            M[i] = conv[T[i]];
        }
        M[i] = '\0';
        MLen = i;
        GenNext(Next, M, MLen);
        int maxPos = KMP(Next, M, MLen, T, MLen);

        printf("%s", T);
        for (i = maxPos + 1; i < MLen - (maxPos+1); ++i) {
            printf("%c", M[i]);
        }
        puts("");
    }
    return 0;
}

/*
33
qwertyuiopasdfghjklzxcvbnm
qwerta
abcdefghijklmnopqrstuvwxyz
abcdab
qwertyuiopasdfghjklzxcvbnm
qwertabcde

abcdefghijklmnopqrstuvwxyz
aaab
*/
