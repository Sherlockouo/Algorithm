/*
���⣺n ���������ȫͼ����Ȩ�Ƕ����ŵ���С��������������ͼ����С��������
��⣺��С������̰���㷨��ȡÿ����С�ıߣ���1�����ж������С��������С������������������еĶ���Ķ���1��������Ȩ���ǣ�
S(n) = (2 + 3 + ... n);
*/

#include <iostream>

using namespace std;

#define LL __int64

int main() {
	int t, cas = 0;
	LL n;
	scanf("%d", &t);

	while (t--) {
		scanf("%I64d", &n);
		n = (n*n + n - 2) / 2;
		printf("Case #%d: %I64d\n", ++cas, n);
	}


	return 0;
}
