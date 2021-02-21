#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;


//************************************ ��ȫ���� ģ�� ************************************
const int MAXN = 510;             // ��Ʒ���� 
const int MAXC = 100010;          // �������� 
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

void completeKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : inf;
	} 
}

void completeKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	completeKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
	}
}

//************************************ ��ȫ���� ģ�� ************************************

struct De {
	int n;
	int val[10];
	int gapcover;
	int idx;
	
	bool operator < (const De & o) const {
		if(gapcover != o.gapcover) {
			return gapcover > o.gapcover;
		}
		
		if(n != o.n) {
			return n < o.n;
		}
		
		if(val[n-1] != o.val[n-1]) {
			return val[n-1] < o.val[n-1];
		}
		return idx < o.idx;
	}
}D[10000];

int main() {
	int S, i, j;
	int n;
	
	while(scanf( "%d", &S ) != EOF && S) {
		scanf("%d", &n);
		for(i = 0; i < n; ++i) {
			D[i].idx = i;
			scanf("%d", &D[i].n);
			for(j = 0; j < D[i].n; ++j) {
				scanf("%d", &D[i].val[j]);
				Knap[j] = Knapsack(D[i].val[j], 1);
			}
			completeKnapsack(D[i].n, Knap, 1000);
			for(j = 0; j <= 1000; ++j) {
				if(dp[j] > S) {
					break;
				}
			}
			D[i].gapcover = j - 1 ;
		}
		sort(D, D + n);
		printf("max coverage = %d :", D[0].gapcover);
		for(i = 0; i < D[0].n; ++i) {
			printf(" %d", D[0].val[i]);
		}
		puts("");
	}
	
	return 0;
}





