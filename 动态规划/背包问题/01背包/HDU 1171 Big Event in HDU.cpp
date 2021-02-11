/*
     ���⣺�ܹ� n(n <= 1000) ���豸��ÿ���豸�и�Ȩֵ v(0 < v <= 50)��Ҫ��
     �������豸�ֳ������֣�������������Ȩֵ�;�����ȣ������յķֳɷ�����
     
     ��⣺01����
     ��Ϊÿ���豸ֻ������ѡ�����Կ�����Ϊ ѡ �� ��ѡ ���ַ���������ѡ���豸
     ��Ȩֵ��Ϊ X�� ��ô��ѡ�豸��Ȩֵ�;�Ӧ�õ��� ��Ȩֵ�� - X��
     Ҫ��ľ��� | ��Ȩֵ�� - 2X | ����С��
     
     �� dp[i][j] ��ʾѡ�˵� i ���豸��Ȩֵ��Ϊ j �ķ����Ƿ���ڣ�
     
     dp[i][j] = (dp[i-1][j] || dp[i-1][j - v[i] ]);   (i <= 5000, j <= 250000)
      
     
*/ 

#include <iostream>
#include <cstring>
using namespace std;


//************************************ 01���� ģ�� ************************************
const int MAXN = 5010;     // ��Ʒ���� 
const int MAXC = 250010;   // �������� 
typedef bool ValueType;

ValueType dp[MAXC];

struct Knapsack {
    int capacity;
    int weight;
    Knapsack(){
    } 
    Knapsack(int c, int w) : capacity(c), weight(w) {
    }
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x || y;
}

void zeroOneKnapsackInit() {
    memset(dp, false, sizeof(dp));
    dp[0] = true;
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap) {
    zeroOneKnapsackInit();
    int maxCapacity = 0;
    for(int i = 0; i < knapsackSize; ++i) {
        maxCapacity += knap[i].capacity;
        for(int j = maxCapacity; j >= knap[i].capacity; --j) {
            dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
        }
    }
}

//************************************ 01���� ģ�� ************************************




int main() {
    int n, i;
    while(scanf("%d", &n) != EOF && n >= 0) {
        int kp = 0;
        int tot = 0;
        for(i = 0; i < n; ++i) {
            int cap, num;
            scanf("%d %d", &cap, &num);
            for(int j = 0; j < num; ++j) {
                Knap[kp++] = Knapsack(cap, 0);
            }
            tot += cap * num;
        }
        zeroOneKnapsack(kp, Knap);
        int a = 0, b = 0;
        for(i = 0; i * 2 <= tot; ++i) {
            if( dp[tot - i] ) {
                a = i;
                b = tot - i;
                if(a < b) swap(a, b);
            }
        }
        printf("%d %d\n", a, b);
    }
    
    return 0;
}
