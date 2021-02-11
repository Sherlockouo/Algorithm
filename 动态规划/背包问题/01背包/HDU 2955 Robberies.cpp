/*
	���⣺һ��ǿ����Ҫ�������У�����һ����ץ���� P�����С��������ʣ�����Ϊ���Ա����ܣ�
	�ܹ� (n <= 100) �����У��� i �����а��� m[i] ��Ǯ�����ұ�ץ�ĸ���Ϊ p[i]������С�ڸ���
	���� P ������£��ܹ�ǿ��������Ǯ��
	
	��⣺ 0/1 ����
	�� ������Ϊ�� ������ Ǯ��Ϊ�Ǽ�ֵ�������� 0/1 �������ڵĸ�������� ���������������޷�����
	״̬ӳ�� �� ״̬ת�ơ�
	�������ǿ��Է�����˼������ Ǯ��Ϊ��������������Ϊ�Ǽ�ֵ�������ͱ������
	
	Ҫ�����ٱ�ץһ�ε���С���� < P
	ת����һ�ζ�����ץ�������� >= 1 - P 
	 
	����ĳ��Ǯ�� x��һ�ζ�����ץ����С���� >= 1 - P�����Ǯ x ���ǿ��Ե��ֵģ������� x��  
*/ 


#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;


//************************************ 01���� ģ�� ************************************
const int MAXN = 1010;            // ��Ʒ���� 
const int MAXC = 10010;           // �������� 
typedef double ValueType;         // ������ֵ������ 
const ValueType inf = -10000000;   // �����ֵ����С������Сֵ����� 
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
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = maxCapacity; j >= knap[i].capacity; --j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
	}
}

//************************************ 01���� ģ�� ************************************

int n, i;
double P;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%lf %d", &P, &n);
		int s = 0;
		for( i = 0; i < n; ++i ) {
			double p;
			int cap;
			scanf("%d %lf", &cap, &p);  // ��ץ�ĸ��� 
			p = log10(1 - p);           // ����ץ�ĸ��� 
			Knap[i] = Knapsack(cap, p);
			s += cap;
		}
		zeroOneKnapsack(n, Knap, s);
		for(i = s; i >= 0; --i) {
			double ans = pow(10, dp[i]);
			// printf("%d %lf\n", i, ans);
			if(ans >= 1 - P) {
				break;
			}
		}
		printf("%d\n", i);
	}
	
	return 0;
} 
