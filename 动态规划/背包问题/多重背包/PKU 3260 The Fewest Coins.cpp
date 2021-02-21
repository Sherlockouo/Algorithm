#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ ���ر��� ģ�� ************************************
const int MAXN = 6200;            // ��Ʒ���� 
const int MAXC = 24600;           // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf =  1e9;       // �����ֵ����С������Сֵ����� 
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
		if( knap[i].capacity > 0) {
			for(int j = maxCapacity; j >= knap[i].capacity; --j) {
				dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
			}			
		}else {
			for(int j = 0; j - knap[i].capacity <= maxCapacity; ++j) {
				dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
			}
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

int main() {
	int n, m;
	int i;
	while(scanf("%d %d", &n, &m) != EOF) {
		int capm = m + 120*120;
		
		for(i = 0; i < n; ++i) {
			int v;
			scanf("%d", &v);
			MKnap[i].capacity = v;
		}
		for(i = 0; i < n; ++i) {
			int cnt;
			scanf("%d", &cnt);
			MKnap[i].weight = 1;
			MKnap[i].count = cnt;
		}
		for(i = 0; i < n; ++i) {
			MKnap[n+i] = MultiKnapsack(10120, -MKnap[i].capacity, 1 );
		}
		
		multiKnapsack(n<<1, MKnap, Knap, capm);
		
		int ans = dp[m];
		if(ans > inf/2) {
			ans = -1;
		}
		printf("%d\n", ans);
	}
	
	return 0;
}

/*
3 20
5 25 50
5 2 1
*/




