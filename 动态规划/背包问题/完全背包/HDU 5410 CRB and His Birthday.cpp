/*
	���⣺�̵��� N(N <= 1000) ����Ʒ�� 
	���ڵ� i ����Ʒ������Ȩֵ w[i], a[i], b[i]��
	������� x ���� i ����Ʒ������ w[i]*x, �õ� a[i]*x+b[i] ���ǹ� 
	�������� M (M <= 2000)�Ļ��� �� �����Ի�ö����ǹ��� 
	 
	��⣺��ȫ����
	
	dp[i][j] ��ʾ ǰ i ����Ʒ�������Ϊ j ������ǹ�
	 
	dp[i][j] = max( dp[i-1][j],                 // �� i �ֲ�ѡ 
		dp[i-1][j - w[i]] + a[i] + b[i],        // �� i �� ѡ 1 �� 
		dp[i-1][j - w[i]*2] + a[i]*2 + b[i],    // �� i �� ѡ 2 ��
		...
		dp[i-1][j - w[i]*k] + a[i]*k + b[i]     // �� i �� ѡ k ��
	) 
	����ʵ�ʸ��Ӷ�Ϊ O(ijk) 
	
	
	�� xdp[i][j] = max( dp[i-1][j - w[i]*k] + a[i]*k );
	// ��ʾ�� i ����Ʒѡ�� k ��ʱ��a[i] �����ǹ������ֵ��ע�� k ���ܵ��� 0 
	
	
	
	
	
	 
	ԭʽת���ɣ�
		dp[i][j] = max( dp[i-1][j], xdp[i][j] + b[i]); 
	
	����ת������ xdp[i][j] 
	����е�������ȫ������ ѡ��1����2����3�� ... �����
	��������˳���һ��ѭ�����
	
    ��һ��һά���� xdp[0...M] = dp[i-1][0...M]
    ˳��ѭ����һ����ȫ���� xdp[0...M]
	Ȼ���� xdp[0...M] += b[i];
	����� xdp[0...M] ���� opt[0...M] ����һ�μ�����
	 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ ��ȫ���� ģ�� ************************************
const int MAXN = 1010;           // ��Ʒ���� 
const int MAXC = 2010;            // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXC], xdp[MAXC];

struct Knapsack {
	int capacity;
	ValueType weighta;
	ValueType weightb;
	Knapsack(){
	} 
	Knapsack(int c, ValueType a, ValueType b) : capacity(c), weighta(a), weightb(b) {
	}
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
	return x > y ? x : y;
}

void completeKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : inf;
		xdp[i] = inf;
	}
}

void completeKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	completeKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
			xdp[j] = dp[j - knap[i].capacity] + knap[i].weighta;
			xdp[j] = opt(xdp[j], xdp[j - knap[i].capacity] + knap[i].weighta);
		}
		
		for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
			dp[j] = opt(dp[j], xdp[j] + knap[i].weightb);
		}
	}
}

//************************************ ��ȫ���� ģ�� ************************************

int M, N;
 
int main() {
	int t;
	int i, j;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &M, &N);
		int n = 0;
		for(i = 0; i < N; ++i) {
			int w, a, b;
			scanf("%d %d %d", &w, &a, &b);
			Knap[n++] = Knapsack(w, a, b);
		}
		
		completeKnapsack(n, Knap, M);
		
		int ans = inf;
		for(i = 0; i <= M; ++i) {
			ans = opt(ans, dp[i]);
		}
		printf("%d\n", ans);
	} 
	 
	return 0;
} 

/*
10

100 1
10 2 1

1 1
10 10 10

100 2
50 1 1
50 1 1

100 2
10 2 1
20 1 1

*/



