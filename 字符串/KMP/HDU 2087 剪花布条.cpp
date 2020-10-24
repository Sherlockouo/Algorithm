// HDU 2087
// KMP

#include <iostream>
#include <cstring>
using namespace std;

#pragma warning(disable:4996)

#define NULL_MATCH (-1)
#define Type char
#define MAXN 1000010

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
}

int KMP(int *next, Type* M, int MLen, Type *T, int TLen) {
	// 1. �������ó� -1 ��Ŀ���ǣ�
	// �����Ϊ������� Ŀ�괮�Ŀմ� �� ƥ�䴮�Ŀմ� һ��ƥ��
	int MPos = NULL_MATCH;
	int c = 0;
	for (int TPos = 0; TPos < TLen; ++TPos) {
		// 2. ǰ���� T[...TPos-1] == M[0...MPos] ��MPos == -1 ����������մ�ƥ�䣬ͬ������)
		//    ��� T[TPos] != M[MPos + 1]���� MPos = MPos' ����ƥ��
		while (MPos != NULL_MATCH && T[TPos] != M[MPos + 1])
			MPos = next[MPos];
		// 3. �� T[TPos] == M[MPos + 1] �� TPos++, MPos++;
		if (T[TPos] == M[MPos + 1]) MPos++;
		// 4. ƥ����ϣ����� Ŀ�괮 ��һ��ƥ���λ��
		if (MPos == MLen - 1) {
			// 
			MPos = NULL_MATCH;
			++c;
		}
	}
	return c;
}



int Next[MAXN];
Type T[MAXN], TT[MAXN], M[MAXN];

int main() {
	while (scanf("%s", T) != EOF && T[0] != '#') {
		scanf("%s", M);
		GenNext(Next, M, strlen(M));
		printf("%d\n", KMP(Next, M, strlen(M), T, strlen(T)));
	}

	return 0;
}