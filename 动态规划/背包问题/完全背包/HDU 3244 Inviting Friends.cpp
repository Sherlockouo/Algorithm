/*
	���⣺n( n <= 100 ) ��ԭ�ϣ� m (m <= 100000) ��Ǯ�� ÿ��ԭ���� 6 ������������
	x (x <= 100)��ÿ������Ҫ����ԭ�ϵ����� 
	y (y <= 100)������Ŀǰ�е�����    
	s1��p1 (s1,p1 <= 100)��С��װ��ԭ������ + �۸� 
	s2��p2 (s2,p2 <= 100)�����װ��ԭ������ + �۸�
	
	��⣺���ִ� + ��ȫ����
	
	�������� L ���ˣ�ĳ��ԭ�ϸ�ÿ������Ҫ 100 ��������û�У� 
	��ô���������� 100L��
	�����ٵļ�Ǯ�����ԭ�� �� p1 = 10 -> s1 = 100, ����������ԭ��Ϊ 100000/p1*s1 = 10^6
	���������˵����޾���  10^6 = 10L�� L = 100000 ���ټ��� y/x �����ֵ���� 10 
	
	����������� L ->  [0, 100010]
	��ÿ��ԭ�������Ҫ�Ĺ����㹻ԭ����Ҫ�����ټ۸��������ԭ�ϼ۸������С�ڵ��� m ������Ҫ��
	L ���ӣ�����L���٣� 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ ��ȫ���� ģ�� ************************************
const int MAXN = 2;               // ��Ʒ���� 
const int MAXC = 1100000;         // �������� 
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

struct Item {
	int x, y, s1, p1, s2, p2;
	void read() {
		scanf("%d %d %d %d %d %d", &x, &y, &s1, &p1, &s2, &p2);
	}
}I[110];

int n, m;

bool fit(int L) {
	int needm = 0; 
	for(int i = 0; i < n; ++i) {
		int need = I[i].x * L - I[i].y;
		
		if(need <= 0) {
			continue;
		}else if( need > 1010000) {
			return false;
		}
		
		Knap[0] = Knapsack(I[i].s1, I[i].p1);
		Knap[1] = Knapsack(I[i].s2, I[i].p2);
		completeKnapsack(2, Knap, need + 210);
		
		int ans = inf;
		for(int j = need; j <= need + 210; ++j) {
			ans = opt(ans, dp[j]);
		}
		needm += ans;
		
		if(needm > m) {
			return false;
		}
	}
	return true;
}

int main() {
	while(scanf("%d %d", &n, &m) != EOF && (n || m)) {
		for(int i = 0; i < n; ++i) {
			I[i].read();
		}
		int l = 0, r = 100100;
		int ans = 0;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(fit(mid)) {
				ans = mid;
				l = mid + 1;
			}else {
				r = mid - 1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
} 

/*
1 100000
100 100 100 10 100 10

1 100000
10 100 100 10 100 10

*/



