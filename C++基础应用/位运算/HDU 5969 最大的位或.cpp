#include <iostream>

using namespace std;

#define ll long long
#define maxb 63

ll f[maxb];

int main() {
	for(int i = 0; i < maxb; ++i) {
		f[i] = (ll)1<<i;
		//printf("%lld\n", f[i]);
	}
	int t;
	ll l, r;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld %lld", &l, &r);
		
		/* 
			1000000000...    - 61��0   - f[61] 
		    1100000000...    - 60��0   - f[61] + f[60]
			
			... 
			 
			1111111111110    -  1��0   - f[61] + ... f[1]
			1111111111111    -  0��0   - f[61] + ... f[0]
		*/
		ll mask = 0;
		for(int i = 61; i >= 0; --i) {
			mask += f[i];
			
			if((mask & l) != (mask & r)) {
				l |= (f[i + 1] - 1);
				break;	
			}
		}
		printf("%lld\n", l);
	}
	
	return 0;
} 
