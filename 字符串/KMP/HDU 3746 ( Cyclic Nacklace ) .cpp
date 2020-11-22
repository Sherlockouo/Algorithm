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
        printf("|%d", i);
    }
    puts("");

    for (int i = 0; i < MLen; ++i) {
        printf("|%c", M[i]);
    }
    puts("");

    for (int i = 0; i < MLen; ++i) {
        printf("|-");
    }
    puts("");



    for (int i = 0; i < MLen; ++i) {
        printf("%d --> %d\n", i, next[i]);
    }
    puts("");*/

    /*for (int i = 0; i < MLen; ++i) {
        printf("|%d", next[i]);
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
bool has[MAXN];

int main() {
    int MLen;
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", M);
        MLen = strlen(M);
        GenNext(Next, M, MLen);
        memset(has, 0, sizeof(has));

        int v = Next[MLen - 1];
        while (v != NULL_MATCH) {
            has[v] = 1;
            v = Next[v];
        }

        int ans = MLen;


        // ���ַ���������  X...XY ����ʽ��ö��;
        // ���� X�ַ����ĳ��ȴ���Y��Y �ַ����ĳ��ȿ���Ϊ 0��
        // ö�ٵ��� X �ַ����ĳ��� XLen
        for (int XLen = 1; XLen <= MLen; ++XLen) {
            int K = (MLen / XLen);
            int YLen = (MLen % XLen) ? (MLen - XLen*K) : 0;
            if (YLen >= XLen) {
                continue;
            }

            int XTLen = XLen * K;
            if (XTLen % (XTLen - 1 - Next[XTLen - 1]) == 0) {
                if (K == XTLen / (XTLen - 1 - Next[XTLen - 1])) {
                    if (YLen == 0) {
                        if(K > 1)
                            ans = 0;
                    }
                    else if (has[YLen - 1]) {
                        if (XLen - YLen < ans) ans = XLen - YLen;
                    }
                }
            }

        }

        printf("%d\n", ans);

    }
    return 0;
}

/*
22
abcabca
aaa
abca
abcde
abcabc
abcdabcda
aaaaaaaaaaaaaaaaab
abcabcabcbc
abaabaabaa
abcca

*/
