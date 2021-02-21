#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ ���ر��� ģ�� ************************************
const int MAXN = 200;             // ��Ʒ���� 
const int MAXC = 8010;            // �������� 
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
}Knap[MAXN];

struct MultiKnapsack : public Knapsack {
	int count;
	MultiKnapsack() {
	}
	MultiKnapsack(int cnt, int cap, ValueType w): count(cnt) {
		capacity = cap;
		weight = w;
	}
}MKnap[MAXN];

ValueType opt(ValueType x, ValueType y) {
	return x || y;
}

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : inf;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = maxCapacity; j >= knap[i].capacity; --j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
	}
}

void multiKnapsack(int knapsackSize, MultiKnapsack *mknap, Knapsack *knap, int maxCapacity) {
	int nknapSize = 0;
	for(int i = 0; i < knapsackSize; ++i) {
		int cnt = mknap[i].count;
		int cap = mknap[i].capacity;
		int val = mknap[i].weight;
		int k = 1;
		// �����Ʋ�� 
		while( cnt ) {
			if(k > cnt) {
				k = cnt;
			}
			knap[nknapSize++] = Knapsack( cap*k, val*k );
			cnt -= k;
			k <<= 1;
		}
	}
	zeroOneKnapsack(nknapSize, knap, maxCapacity);
}

//************************************ ���ر��� ģ�� ************************************


int a[3];
int b[3] = {1, 2, 5};

int main() {
	int i;
	int cas = 0;
	while(scanf("%d %d %d", &a[0], &a[1], &a[2]) != EOF) {
		if(a[0] + a[1] + a[2] == 0) break;
		int s = 0;
		for(i = 0; i < 3; ++i) {
			MKnap[i] = MultiKnapsack(a[i], b[i], 0);
			s += a[i] * b[i];
		}
		multiKnapsack(3, MKnap, Knap, s);
		dp[s+1] = false;
		for(int j = 0; j <= s+1; ++j) {
			if(!dp[j]) {
				printf("%d\n", j);
				break;
			}
		}
	}
	
	return 0;
} 




