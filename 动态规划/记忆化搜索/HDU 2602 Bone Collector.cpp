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

int dfs(int n, int vol) {
	if(vol < 0) {
		return inf;
	}
	if(n == 0) {
		return 0;
	}
	ValueType &val = dp[n][vol];
	if(val != -1) {
		return val;
	}
	return val = opt( 
		dfs(n-1, vol), 
		dfs(n-1, vol - Knap[n].capacity) + Knap[n].weight 
	);
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
		memset(dp, -1, sizeof(dp));
		printf("%d\n", dfs(n, v) );
	}	
	return 0;
}
