/*
	���⣺
	1) һ����m(m <= 100)��ļ��ڣ�ÿ��ı�Ŵ�1��m;
	2) һ����n(n <= 1000)�ݿ������Ĺ�����ÿ�ݹ�����֪����ʼʱ��s����ֹʱ��e�Ͷ�Ӧ�Ĺ���c��
	3) ÿ�ݹ�������ʼ����ֹʱ������Ϊ��λ(���������)��ÿ�ݹ����������ʼʱ��
	������ֹʱ����ܵõ��ܹ���c���Ҳ��ܴ���ʱ���ص��Ĺ�����
	
	���磬��1����ʼ��2������Ĺ������ܺ͵�2����ʼ����4������Ĺ���һ��ѡ����
	��Ϊ��2��ֻ����һ���ط�������
�������ڣ���֪����ô���Ų����ڼ��ڵ�m���ڻ�����Ĺ������� 

	
	��⣺��������ϵ�� 01 ���� 
	ĳ��ѡ�ˣ�ĳ�����Ͳ���ѡ 
	
	dp[i][j] ����ǰi�������н�ֹ��ʱ��j������� 
	����������ʱ���Ÿ��� 
	
	[ ����ǡ�õ���� ]
	if( j >= p[i].e )
		dp[i][j] = max( dp[i-1][j], dp[i-1][p[i].s - 1] + p[i].c);
	ע�⣺  �������ǡ�õ��������ô��ʼֵ���趨�ǲ�һ���� 
	 
*/


#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;


//************************************ 01���� ģ�� ************************************
const int MAXN = 1010;              // ��Ʒ���� 
const int MAXC = 1010;              // �������� 
typedef int ValueType;              // ������ֵ������ 
const ValueType inf = -100000000;   // �����ֵ����С������Сֵ����� 
const ValueType init = 0;           // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXC];

struct Knapsack {
	int start;
	int end;
	ValueType weight;
	Knapsack(){
	} 
	Knapsack(int s, int e, ValueType w) : start(s), end(e), weight(w) {
	}
	
	bool operator < (const Knapsack& knap) const {
		return end < knap.end;
	}
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
	return x > y ? x : y;
}

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = init;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = maxCapacity; j >= knap[i].end; --j) {
			dp[j] = opt(dp[j], dp[knap[i].start-1] + knap[i].weight);
		}
	}
}

//************************************ 01���� ģ�� ************************************

int main() {
	int t, i;
	int n, m;
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d %d", &m, &n);
		for(i = 0; i < n; ++i) {
			int s, e, c;
			scanf("%d %d %d", &s, &e, &c);
			Knap[i] = Knapsack(s, e, c);
		}
		sort(Knap, Knap + n);
		zeroOneKnapsack(n, Knap, m);
		
		int Max = 0;
		for(i = 0; i <= m; ++i) {
			// printf("%d %d\n", i, dp[i]);
			if(dp[i] > Max) Max = dp[i];
		}
		printf("%d\n", Max); 
	}
	
	return 0;
}

/*
100
10 3
1 3 3
2 4 3
3 5 34
*/
