#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ ��ȫ���� ģ�� ************************************
const int MAXN = 200;             // ��Ʒ���� 
const int MAXC = 300;             // �������� 
typedef long long ValueType;      // ������ֵ������ 
const ValueType inf = 0;          // �����ֵ����С������Сֵ����� 
const ValueType init = 1;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

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
	return x + y;
}

void completeKnapsackInit(int maxCapacity) {
	for(int num = 0; num < MAXN; ++num)
		for(int i = 0; i <= maxCapacity; ++i)
			dp[num][i] = (!num && !i) ? init : inf;
}

void completeKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	completeKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int num = 1; num < MAXN; ++num)
			for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
				dp[num][j] = opt(dp[num][j], dp[num-1][j - knap[i].capacity] + knap[i].weight);
			}
	}
}

//************************************ ��ȫ���� ģ�� ************************************


int a[5] = {1, 5, 10, 25, 50};

int main() {
	int i, n;
	int cas = 0;
	
	for(i = 0; i < 5; ++i) {
		Knap[i] = Knapsack(a[i], 0);
	}
	completeKnapsack(5, Knap, MAXC - 1);
	
	while(scanf("%d", &n) != EOF) {
		if(n < 0) {
			printf("0\n");
			continue;
		}
		long long ans = 0;
		for(i = 0; i <= 100; ++i) ans += dp[i][n]; 
		printf("%lld\n", ans);
	}
	
	return 0;
} 




