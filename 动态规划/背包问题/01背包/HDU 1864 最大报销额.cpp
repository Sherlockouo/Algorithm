/*
	���⣺���� n �ŷ�Ʊ��ÿ�ŷ�Ʊ�� x ���۸�������۳��� 600 ���ܱ������ܼ۳��� 1000 Ҳ���ܱ�����
	�ʸ���һ���۸��Ͻ磬����ܱ�������Ǯ����ȷ��С����� 2 λ��
	
	��⣺ �۸����100��Ȼ��ɸѡ�������������� 0/1 ���� 
*/ 

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 01���� ģ�� ************************************
const int MAXN = 40;              // ��Ʒ���� 
const int MAXC = 1000*100*32;     // �������� 
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

//************************************ 01���� ģ�� ************************************

#define eps 1e-8


int main() {
	double v;
	int intV, i;
	char ch[100];
	int n;
	double g[3];
	while(scanf("%lf %d", &v, &n) != EOF && n) {
		intV = int(v * 100 + eps);
		int tp = 0;
		int needCap;
		while(n--) {
			int k;
			
			scanf("%d", &k);
			
			g[0] = g[1] = g[2] = 0;
			
			double tot = 0;
			double ans;
			bool flag = 1;
			while(k--) {
				scanf("%s", ch);
				char tmp;
				sscanf(ch, "%c:%lf", &tmp, &ans);
				tot += ans;
				if(tot > 1000 + eps) {
					flag = 0;
				}
				if(tmp != 'A' && tmp != 'B' && tmp != 'C') {
					flag = 0;
				}else {
					g[ tmp - 'A' ] += ans;
					if( g[ tmp - 'A' ] > 600 + eps ) {
						flag = 0;
					}
					
				}
			}
			if(flag) {
				int cap = int(tot * 100 + eps);
				Knap[tp++] = Knapsack( cap, 0 );
				needCap += cap;
			}
		}
		if(needCap < intV) intV = needCap;
		
		zeroOneKnapsack(tp, Knap, intV);
		for(i = intV; i >= 0; --i) {
			if(dp[i]) {
				break;
			}
		}
		printf("%d.%02d\n", i/100, i%100);
	}
	
	
	return 0;
}




