/*
	���⣺���� n(n <= 500) ����Ʒ��ÿ����Ʒ�и��۸� p[i], ��ֵ v[i]��
	�����Ǯ���� q[i] ʱ�Ͳ����������Ʒ�ˣ� �ʸ��� M Ԫ���ܹ��򵽵�����ֵ�Ƕ��٣�
	
	��⣺
	
	dp[i][j] ��ʾǰi����Ʒ��ѡ���������ļ۸�Ϊj������ֵ��
	
	1) �� i ����Ʒѡ������ dp[i][j] = dp[i-1][j];
	2) �� i ����Ʒѡ������  dp[i][j] =  dp[i-1][j-p[i]] + v[i]   |  (j >= q[i])  
	
	
	
	2 2
	1 2 5
	1 1 6
	����һ�����ݣ��� �Ż���� 01 �����������״̬��ϵͼΪ��
	0 inf inf
	0   6 inf 
    
    �����������
	2 2
	1 1 5
	1 2 6 
	0 5 inf
	0 5 11 
*/ 
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;


//************************************ 01���� ģ�� ************************************
const int MAXN = 510;             // ��Ʒ���� 
const int MAXC = 5010;            // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -10000000;  // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXC];

struct Knapsack {
	int capacity;
	int maxcap;
	ValueType weight;
	Knapsack(){
	} 
	Knapsack(int c, int mc, ValueType w) : capacity(c), maxcap(mc), weight(w) {
	}
	
	bool operator < (const Knapsack& k) const {
		return maxcap-capacity < k.maxcap - k.capacity;
	} 
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
	return x > y ? x : y;
}

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = init;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = maxCapacity; j >= knap[i].maxcap; --j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
		
		/*for(int j = 0; j <= maxCapacity; ++j) {
			printf("%d ", dp[j]);
		}
		puts("");*/ 
	}
}

//************************************ 01���� ģ�� ************************************


int main() {
	int n, m; 
	while(scanf("%d %d", &n, &m) != EOF) {
		for(int i = 0; i < n; ++i) {
			int c, mc, v;
			scanf("%d %d %d", &c, &mc, &v);
			Knap[i] = Knapsack(c, mc, v);
		}
		sort(Knap, Knap + n);
		zeroOneKnapsack(n, Knap, m);
		printf("%d\n", dp[m]);
	}
	return 0;
}
/*


2 2
1 2 5
1 1 6
0 -10000000 -9999995
0 6 -9999994
-9999994

2 2
1 1 6
1 2 5
0 6 -9999994
0 6 11
11


2 3
1 2 6
2 2 7
0 -10000000 -9999994 -9999994
0 -10000000 7 -9999993
-9999993

2 3
2 2 7
1 2 6
0 -10000000 7 -9999993
0 -10000000 7 13
13




2 2 
1 2 5
1 1 6

2 2
1 1 6
1 2 5


2 3
1 2 6
2 2 7

2 3
2 2 7
1 2 6


*/


