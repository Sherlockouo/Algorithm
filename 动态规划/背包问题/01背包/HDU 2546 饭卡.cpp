/*
	���⣺���ϵ�ʣ������ڻ����5Ԫ����һ�����Թ���ɹ�����ʹ����������Ϊ������
	�����޷����򣨼�ʹ����㹻�������Դ�Ҷ�ϣ������ʹ���ϵ�������١�
	ĳ�죬ʳ������n�ֲ˳��ۣ�ÿ�ֲ˿ɹ���һ�Ρ���֪ÿ�ֲ˵ļ۸��Լ����ϵ���
	�����ٿ�ʹ���ϵ����Ϊ���١�
	
	
	dp[m] ��Ϊ��ʼ״̬ Ϊ 1
	���� 0/1 ���� ����״̬ת��

	dp[j] = dp[j] || dp[j + c[i]];
	
	����ֻ�� j + c[i] >= 5 ���ܽ���״̬ת��
	 
	 
*/ 
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;


//************************************ 01���� ģ�� ************************************
const int MAXN = 1010;            // ��Ʒ���� 
const int MAXC = 2010;            // �������� 
const int BASE = 45;              // ����������ƫ�� 
typedef bool ValueType;           // ������ֵ������ 
const ValueType inf = 0;          // �����ֵ����С������Сֵ����� 
const ValueType init = 1;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXC];

struct Knapsack {
	int capacity;
	ValueType weight;
	Knapsack(){
	} 
	Knapsack(int c, ValueType w) : capacity(c), weight(w) {
	}
	
	bool operator < (const Knapsack& k) const {
		return capacity < k.capacity;
	} 
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
	return x || y;
}

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = -45; i <= maxCapacity; ++i) {
		dp[i + BASE] = (i == maxCapacity) ? init : inf;
	}
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = -45; j + knap[i].capacity <= maxCapacity; ++j) {
			if(j + knap[i].capacity >= 5)
				dp[j + BASE] = opt(dp[j + BASE], dp[j + knap[i].capacity + BASE] + knap[i].weight);
		}
	}
}

//************************************ 01���� ģ�� ************************************


int main() {
	int n, m; 
	while(scanf("%d", &n) != EOF && n) {
		for(int i = 0; i < n; ++i) {
			int v;
			scanf("%d", &v);
			Knap[i] = Knapsack(v, 0);
		}
		scanf("%d", &m);
		sort(Knap, Knap + n);
		zeroOneKnapsack(n, Knap, m);
		int ans = -1;
		for(int j = -45; j <= m; ++j) {
			if(dp[j+BASE]) {
				ans = j;
				break;
			}
		}
		printf("%d\n", ans);
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


