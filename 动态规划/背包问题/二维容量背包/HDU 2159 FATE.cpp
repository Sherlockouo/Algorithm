/*
	���⣺������Ҫ n(n <= 100) �㾭��ֵ�� ��ʣ�� m(m <= 100) �����Ͷȣ������ͶȽ��� <= 0 ��
	��Ϸ�������ܹ��� k (k <= 100) �ֹ֣�ÿ�ֹ�ɱ����õ� a[i] �ľ���ֵ����ȥ b[i] �����Ͷȣ� 
	�����ɱ s (s <= 100) ֻ�֣����ܷ�����������������ܱ�����������Ͷȡ� 
	 
	��⣺��ά��ȫ����
	
	Ҫ��ѡ��С�ڵ��� s ֻ�֣�ʹ�����ǵ� ����ֵ�Ӻ� >= n���������ͶȼӺ� <= m���Ҿ���С��
	
	����԰ѡ�����ֵ�������ǡ��������������Ͷȡ������ǡ���ֵ����������ȫ������
	��������ֵ����������ƣ���ҪС�ڵ���s��������Ҫ����һ�� �ֵ����� ά�ȡ�
	
	dp[i][j][k]  ���� "ǰi�ֹ���ѡ��jֻ����ɱ�õ�����ֵΪk����С�������Ͷ�"
	
	dp[i][j][k] = 
		min( dp[i][j - 1][ k - a[i] ] + b[i],    // �� i �ֹ���ѡ��1��2, 3, 4 ...����ɱ 
	                           dp[i-1][j][k],    // �� i �ֲֹ�ѡ�� 
	    )
	    
	ת����  dp[j][k] = min( dp[j-1][k-a[i]] + b[i], dp[j][k]); 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ ��ȫ���� ģ�� ************************************
const int MAXN = 110;             // ��Ʒ���� 
const int MAXC = 1000;            // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = 1e9;        // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXN][MAXC];

struct Knapsack {
	int capacity;
	ValueType weight;
	Knapsack(){
	} 
	Knapsack(int c, ValueType w) : capacity(c), weight(w) {
	}
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
	return x < y ? x : y;
}

void completeKnapsackInit(int nCnt, int maxCapacity) {
	for(int i = 0; i <= nCnt; ++i) {
		for(int j = 0; j <= maxCapacity; ++j) {
			dp[i][j] = (!i && !j) ? init : inf;
		}
	}
}

void completeKnapsack(int knapsackSize, Knapsack *knap, int nCnt, int maxCapacity) {
	completeKnapsackInit(nCnt, maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = 1; j <= nCnt; ++j) {
			for(int k = knap[i].capacity; k <= maxCapacity; ++k) {
				dp[j][k] = opt(dp[j][k], dp[j-1][k - knap[i].capacity] + knap[i].weight);
			}
		}

	}
}

//************************************ ��ȫ���� ģ�� ************************************

int n, m, k, s;

int main() {
	int i, j;
	while(scanf("%d %d %d %d", &n, &m, &k, &s) != EOF) {
		for(i = 0; i < k; ++i) {
			int a, b;
			scanf("%d %d", &a, &b);
			Knap[i] = Knapsack(a, b);
		}
		completeKnapsack(k, Knap, s, n + 100);
		int need = inf;
		for(j = 0; j <= s; ++j)
			for(i = n; i <= n + 100; ++i) {
				need = opt(need, dp[j][i]);
			}
		
		if(need > m) {
			need = -1;
		}else {
			need = m - need;
		}
		printf("%d\n", need);
	}
	return 0;
} 





