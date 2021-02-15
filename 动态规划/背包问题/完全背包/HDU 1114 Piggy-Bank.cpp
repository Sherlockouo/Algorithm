/*
	���⣺���� n (n <= 500) ��Ӳ�ҵ� ��ֵ p �� ���� w����Ӳ������һ����������ޣ�
	�����ٵ�Ӳ�Ҽ�ֵ��
	
	��⣺��ȫ����
	Ӳ�ҿ���ѡ 0��1��2��3... �����Ǹ���ȫ�������⣻ 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ ��ȫ���� ģ�� ************************************
const int MAXN = 510;             // ��Ʒ���� 
const int MAXC = 10010;           // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = 1e9;        // �����ֵ����С������Сֵ����� 
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
	return x < y ? x : y;
}

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : inf;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
	}
}

//************************************ ��ȫ���� ģ�� ************************************

int main() {
	int t, n;
	int E, F;
	
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d %d", &E, &F);
		F -= E;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i) {
			int p, w;
			scanf("%d %d",&p, &w);
			Knap[i] = Knapsack(w, p);
		}
		zeroOneKnapsack(n, Knap, F);
		if(dp[F] > inf/2+10) {
			printf("This is impossible.\n");
		}else {
			printf("The minimum amount of money in the piggy-bank is %d.\n", dp[F]);
		}
	}
	
	return 0;
} 





