// HDU 5918
// KMP
// ���⣺�������������У�����aΪ��a[0], a[1] ... a[n-1]�� ����bΪb[0], b[1] ... b[m-1]
// ����һ������ p�������ܹ��ҵ� q������ b = a[q], a[q+p] ... a[q+(m-1)p] 
// �������� q ��������
// ��⣺������a���p�����У�Ȼ��ֱ��b����KMP������ۼӼ��ɣ� 

#include <iostream>
#include <cstring>
using namespace std;

#pragma warning(disable:4996)

#define NULL_MATCH (-1)
#define MATCH_ALL 0 
#define Type int
#define MAXN 1000010

bool TypeEqualExact(Type a, Type b) {
	return a == b;
}

void GenNext(int *next, Type* M, int MLen) {
	// 0. �� NULL_MATCH(-1) ����һ��û����ǰ׺��0��λ��һ��û����ǰ׺������Ϊ NULL_MATCH
	int MPos = NULL_MATCH;
	next[0] = MPos;
	for (int TPos = 1; TPos < MLen; ++TPos) {
		// 1. M[TPos-MPos-1...TPos-1] �� M[0...MPos] ��ȫƥ�� 
		//    ��� M[TPos] �� M[MPos + 1] �Ƿ�ƥ�䣬��ƥ�䣬������һ�� MPos' = next[MPos]��
		while (MPos != NULL_MATCH && !TypeEqualExact(M[TPos], M[MPos + 1]) )
			MPos = next[MPos];
		// 2. ��ȷƥ���ϣ����� MPos
		if ( TypeEqualExact(M[TPos], M[MPos + 1]) ) ++MPos;
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
		while (MPos != NULL_MATCH && !TypeEqualExact(T[TPos], M[MPos + 1])  )
			MPos = next[MPos];
		// 3. �� T[TPos] == M[MPos + 1] �� TPos++, MPos++;
		if ( TypeEqualExact(T[TPos], M[MPos + 1]) ) MPos++;
		// 4. ƥ����ϣ����� Ŀ�괮 ��һ��ƥ���λ��
		if (MPos == MLen - 1) {
			++c;
			MPos = next[MPos];
		}
	}
	return c;
}



int Next[MAXN];
Type T[MAXN], TT[MAXN], M[MAXN];

Type a[MAXN], b[MAXN];

int main() {
	int n, m, p;
	int t;
	int i;
	int cas = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &n, &m, &p);
		for (i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		for (i = 0;i < m; ++i) {
			scanf("%d", &b[i]);
		}
		GenNext(Next, b, m);
		int ans = 0;
		for(i = 0; i < p; ++i) {
			int s = i;
			int tLen = 0;
			while(s < n) {
				T[tLen ++] = a[s];
				s += p;
			}
			ans +=  KMP(Next, b, m, T, tLen);
		}
		
		printf("Case #%d: %d\n", ++cas, ans);
	}


}

/*
10

10 5 2
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1

10 5 2
1 1 1 2 2 1 1 1 1 1 
1 1 1 1 1

10 3 2
1 1 1 1 1 1 1 1 1 1 
1 1 1

6 3 1
1 2 3 1 2 3
1 2 3

6 3 2
1 3 2 2 3 1
1 2 3

5 3 2
1 3 2 2 3
1 2 3

8 2 2
1 1 3 3 1 1 3 3
1 3


*/
