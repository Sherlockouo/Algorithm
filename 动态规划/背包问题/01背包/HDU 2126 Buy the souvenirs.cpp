/*
	���⣺����һ����Ʒ��ÿ����Ʒ����һ���۸� 
	Ҫ����Щ��Ʒ���������������ĳ���۸�������
	�� �ܹ����������Ʒ���������Լ��������� 
	
	��⣺ 
		dp[i][j] = max(dp[i-1][j], dp[i-1][j-c[i]] + 1); 
		����������һ�������¼������ dp �����״̬ת�������з����ļ�¼ 
*/ 

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 01���� ģ�� ************************************
const int MAXN = 40;              // ��Ʒ���� 
const int MAXC = 510;             // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -10000000;  // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXC];
ValueType sel[MAXC];

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
		sel[i] = (!i) ? 1 : 0;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = maxCapacity; j >= knap[i].capacity; --j) {
			
			int x = dp[j];
			int y = dp[j - knap[i].capacity] + knap[i].weight; 
			if(x > y) {
				dp[j] = x;
			}else if(x < y) {
				dp[j] = y;
				sel[j] = sel[ j - knap[i].capacity ];
			}else {
				sel[j] = sel[j] + sel[ j - knap[i].capacity ]; 
			}
		}
	}
}

//************************************ 01���� ģ�� ************************************



int main() {
	int t, i;
	int n, m;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; ++i) {
			scanf("%d", &Knap[i].capacity);
			Knap[i].weight = 1;
		}
		zeroOneKnapsack(n, Knap, m);
		int ans, Max = 0;
		for(i = m; i >= 1; --i) {
			if(dp[i] > Max) {
				Max = dp[i];
				ans = sel[i];
			}else if(dp[i] == Max) {
				ans += sel[i];
			}
		}
		if(!Max) {
			printf("Sorry, you can't buy anything.\n");
		}else {
			printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n", ans, Max);
		}
		
	}
	
	return 0;
}




