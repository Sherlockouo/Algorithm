// HDU 5935
// ̰�� 
// ���е�ʱ��Ҫ�����������е��ٶ���ʵ���� 
// Ҫ���ٶȲ�������:   (a[1]-a[0])/t1 <=  (a[2]-a[1])/t2 <= ... <= (a[N]-a[N-1])/tN
// �� sum  {ti | 1<=i<=N} 
// ����̰�ķ���tN �϶�ȡԽСԽ�ã���1��Ȼ��Ӻ���ǰһ��������� ti �ۼӣ�
 
#include <iostream>

using namespace std;

#define MAXN 100010
#define ll __int64

ll a[MAXN], T[MAXN];
int n;

int main() {
	int i, t, cas = 0;
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d", &n);
		for(i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		ll ans = 0; 
		for(i = n; i >= 1; i--) {
			a[i] -= a[i-1];
			if(i == n) {
				T[i] = 1;
			}else {
				ll s = a[i] * T[i+1];
				if(s % a[i+1]) {
					T[i] = s / a[i+1] + 1;
				}else {
					T[i] = s / a[i+1];
				}
			}
			
			ans += T[i];
		}
		
		printf("Case #%d: %I64d\n", ++cas, ans);
	}
	
	
	return 0;
} 
