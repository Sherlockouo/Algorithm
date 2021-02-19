/*
	���⣺n(n <= 16)�����У���1�ų��г���������ÿ����������һ���ٻص� 1�ų��е����·����
	
	��⣺dp[i][j] ����״̬��0 < i < n�� 1 <= j < 2^n  
	i ����ǰ���ڳ���
	j �����Ѿ����ʹ��ĳ��е�λ�飬���� (10011)2 ����0��1��4�ų����Ѿ������ʹ��� 
	 
	dp[i][j] = min( k != i | dp[k][j] + w(k,i), dp[k][j ^ (1<<i)]  + w(k,i) );
	
	dp[0][1] = 0 Ϊ��ʼ״̬
	 
	dp[k][j] + w(k,i)  ����� k �� i������֮ǰ�Ѿ����� i �����·����
	dp[k][ j ^ (1<<i)) ] + w(k, i) ����� k �� i������֮ǰ��û������ i �����·����
	 
*/
#include <iostream>
#include <cstring>
using namespace std;

#define maxn 17
#define inf 1000000000

int dp[maxn][1<<maxn];
int mat[maxn][maxn];
int id[1<<maxn+1];

bool hascity(int v, int state) {
	return (1<<v) & state;
}

int lowbit(int x) {
	return x & -x;
}

int Min(int a, int b) {
	return a < b ? a : b;
}

int dfs(int v, int state) {
	if( !hascity(v, state) ) {
		return inf;
	}	
	if(dp[v][state] != -1) {
		return dp[v][state]; 
	}
	 
	if( v == 0 && state == 1 ) {
		return 0;
	}
	
	dp[v][state] = inf;
	
	int x = state;
	while(x) {
		int k = lowbit(x);
		int u = id[k];
		// u -> v
		
		if( (1<<v) != k ) {
			dp[v][state] = Min( dp[v][state], dfs(u, state) + mat[u][v] );
			dp[v][state] = Min( dp[v][state], dfs(u, ( state ^ (1<<v) ) ) + mat[u][v] );
		}
		
		x ^= k;
	}
	return dp[v][state];
}

int main() {
	int t, i, j, n, m;
	for(i = 0; i < maxn; ++i) {
		id[1<<i] = i;
	}
	
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; ++i) {
			for(j = 0; j < n; ++j) {
				mat[i][j] = (i==j) ? 0 : inf;
			}
		}
		while(m--) {
			int u, v, w;
			
			scanf("%d %d %d", &u, &v, &w);
			--u, --v; 
			if(w < mat[u][v]) {
				mat[u][v] = mat[v][u] = w;
			}
		}
		memset(dp, -1, sizeof(dp));
		printf("%d\n", dfs(0, (1<<n)-1));
	}	
	
	return 0;
} 
