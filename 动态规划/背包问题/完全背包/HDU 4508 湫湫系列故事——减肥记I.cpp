/*
	���⣺ÿ��������һ������n��ʼ����ʾÿ���ʳ���嵥��n��ʳ� 
����������n�У�ÿ����������a��b������a��ʾ����ʳ����Դ������е��Ҹ�ֵ����ֵԽ��Խ�Ҹ�����
	b��ʾ���г�����ʳ������յĿ�·������
���������һ������m����ʾ����һ�����յĿ�·�ﲻ�ܳ���m��
	 
	��⣺��ȫ����
	 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ ��ȫ���� ģ�� ************************************
const int MAXN = 110;             // ��Ʒ���� 
const int MAXC = 100010;          // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
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

int main() {
	int i;
	int n, m;
	
	while(scanf("%d", &n) != EOF) {
		for(i = 0; i < n; ++i) {
			int c, w;
			scanf("%d %d", &w, &c);
			Knap[i] = Knapsack(c, w);
		}
		scanf("%d", &m);
		completeKnapsack(n, Knap, m);
		int ans = inf;
		for(i = 0; i <= m; ++i) ans = opt(ans, dp[i]);
		printf("%d\n", ans);
	}
	return 0;
} 





