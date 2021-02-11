/*
	���ر��� ת 0/1 ���� 
*/ 


#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;


//************************************ 01���� ģ�� ************************************
const int MAXN = 100010;          // ��Ʒ���� 
const int MAXC = 10010;           // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -10000000;  // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXC];

struct Knapsack {
	int capacity;
	ValueType weight;
	Knapsack(){
	} 
	Knapsack(int c, ValueType w) : capacity(c), weight(w) {
	}
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
	return x > y ? x : y;
}

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : inf;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	int maxC = 0;
	for(int i = 0; i < knapsackSize; ++i) {
		// printf("%d %d\n", knap[i].capacity, knap[i].weight);
		maxC += knap[i].capacity;
		if(maxC > maxCapacity) {
			maxC = maxCapacity;
		}
		for(int j = maxC; j >= knap[i].capacity; --j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
	}
}

//************************************ 01���� ģ�� ************************************

int Cnt[12][12];

int main() {
	int n;
	int N, C;
	int i, j;
	
	while(scanf("%d %d", &n, &C) != EOF) {
		memset(Cnt, 0, sizeof(Cnt));
		
		N = 0;
		while(n--) {
			int v, c;
			char ch[20];
			scanf("%s %d %d", ch, &v, &c);
			++ Cnt[v][c];
		}
		for(i = 1; i <= 10; ++i) {
			for(j = 0; j <= 10; ++j) {
				if(Cnt[i][j]) {
					int k = 1;
					while(Cnt[i][j]) {
						int min = Cnt[i][j] < k ? Cnt[i][j] : k;
						
						Knap[N++] = Knapsack( j*min,  i*min );
						
						Cnt[i][j] -= min;
						k <<= 1; 
					}
				}
			}
		}
		
		zeroOneKnapsack(N, Knap, C);
		int Max = 0;
		for(int i = C; i >= 0; --i) {
			if(dp[i] > Max) Max = dp[i];
 		}
 		printf("%d\n", Max);
	}
	
	return 0;
} 

/*
5 20
go 3 2
go 3 2 
go 3 2 
go 3 2
go 3 2 
*/
