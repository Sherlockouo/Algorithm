/*
	ͼ�����ص�
	
		����һ��ͼ������С�� sqrt(m) �ĵ��Ϊ ��㣬����Ϊ�ص�
		
		��� �� ���е����ߣ�   ����֤С�� sqrt(m) ���� 
		�ص� �� �����ص����ߣ� ����֤С�� sqrt(m) ���� 
		
		ע�⣺�ص� �� ��� �����ߣ� 
		
		����Ȩֵʱ�� 
			1�����ӵ�ǰ������Χ�ڽӽ��Ĺ���ֵ a[i]; 
			2�������ǰ���Ϊ��� u�� ��ô��������Χ���е��ص� v������Ȩֵ�� sum[v]; 
			
		ͳ��ʱ��
			���:���������ڽӵ㣬�� a[i] ��ͼ�Ϊ�𰸣�
			�ص�:���������ڽӵ㣬�� a[i] ��ͣ��ټ��ϱ����¼�� �ڽӺ� sum[i]�� 
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 100020;
#define ll long long 

vector< int > edges[MAXN];
int deg[MAXN];
int heav[MAXN];

struct Edge {
	int u, v;
}E[ MAXN ];

struct Quest {
	char tp;
	int u, v; 
};

ll a[MAXN], s[MAXN];

int main() {
	int t, i, j;
	int q, n, m;
	
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		for(i = 1; i <= n; ++i) {
			edges[i].clear();
			deg[i] = 0;
			a[i] = s[i] = 0;
			heav[i] = 0;
		}
		
		for(i = 0; i < m; ++i) {
			int x, y;
			scanf("%d %d", &x, &y);
			E[i].u = x;
			E[i].v = y;
			
			++deg[x];
			++deg[y];
		}
		int sqrtm = sqrt(0.0 + m);
		
		for(i = 1; i <= n; ++i) {
			if(deg[i] > sqrtm) {
				heav[i] = 1;
			}
		}
		for(i = 0; i < m; ++i) {
			int u = E[i].u, v = E[i].v;
			
			// �ص㲻���������
			
			if( heav[u] && !heav[v] ) {
			}else {
				edges[u].push_back(v);
			}
			
			if( heav[v] && !heav[u] ) {
			}else {
				edges[v].push_back(u);
				
			}
		}
		
		
		scanf("%d", &q);
		Quest Q;
		for(i = 0; i < q; ++i) {
			scanf("%d %d", &Q.tp, &Q.u);
			if(Q.tp == 0) {
				scanf("%d", &Q.v);
				
				// 1. ���ڽ����е��Ȩֵ����ֵ 
				a[ Q.u ] += Q.v;
				
				if( !heav[ Q.u ]) {
					// 2. �����ص��Ȩֵ����ֵ 
					for(j = 0; j < edges[Q.u].size(); ++j) {
						int adj = edges[Q.u][j];
						
						if( heav[ adj ] ) {
							s[ adj ] += Q.v;
						}
					}			
				}
			}else {
				ll sum = 0; 
				if( !heav[Q.u] ) {
					// 1. �������㣬��ֱ��ͳ���ڽӵ�ĺ�
					for(j = 0; j < edges[Q.u].size(); ++j) {
						int adj = edges[Q.u][j];

						sum += a[adj];
					}	
				}else {
					// 2. ������ص㣬��Ҫͳ��  �������� + �ص�����ĺ�
					// 2.1 �������ľ���  sum[ Q.u ]; 
					// 2.2 �ص�����ľ���  a[  adj[ Q.u ][j] ]  ��ͣ� 
					sum = s[Q.u];
					 
					for(j = 0; j < edges[Q.u].size(); ++j) {
						int adj = edges[Q.u][j];

						sum += a[adj];
					}
					
				}
				
				printf("%lld\n", sum);
				
			}
		}

		
	}
	return 0;
} 
