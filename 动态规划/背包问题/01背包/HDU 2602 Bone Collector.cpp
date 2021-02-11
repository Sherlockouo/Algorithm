/*
	 ���⣺�� 01 ����
	 
*/ 

#include <iostream>
#include <cstring>
using namespace std;


//************************************ 01���� ģ�� ************************************
const int MAXN = 1010;      // ��Ʒ���� 
const int MAXC = 1010;      // �������� 
const int inf = -100000000; // dp����ķǷ�ֵ 
const int init = 0;         // dp����ĳ�ʼֵ 
typedef int ValueType;

ValueType dp[MAXN][MAXC];

struct Knapsack {
	int capacity;
	ValueType weight;
public:
	Knapsack(){} 
	Knapsack(int c, ValueType w) : capacity(c), weight(w) {}
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
	return x > y ? x : y;
}

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[0][i] = (i==0) ? init : inf;
	}
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 1; i <= knapsackSize; ++i) {
		for(int j = 0; j <= maxCapacity; ++j) {
			if( j >= knap[i].capacity )
				dp[i][j] = opt(dp[i-1][j], dp[i-1][j - knap[i].capacity] + knap[i].weight);
			else
				dp[i][j] = dp[i-1][j];
		}
	}
}

//************************************ 01���� ģ�� ************************************


int main() {
	int n, v, i;
	int t;
	scanf("%d", &t);
	while( t-- ) {
		scanf("%d %d", &n, &v);
		int tot = 0;
		for(i = 1; i <= n; ++i) {
			int w;
			scanf("%d", &w);
			Knap[i].weight = w;
		}
		for(i = 1; i <= n; ++i) {
			int c;
			scanf("%d", &c);
			Knap[i].capacity = c;
		}
		
		zeroOneKnapsack(n, Knap, v);
		int Max = 0;
		for(i = 0; i <= v; ++i) {
			if(dp[n][i] > Max) Max = dp[n][i];
		}
		printf("%d\n", Max);
	}	
	return 0;
}
