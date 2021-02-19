/*
	���⣺���� 1 <= a,b,c <= 10^6 ���� ax+by = c �Ľ� (x,y) �Ķ���
	
	��⣺����ͬ��
	1)  �� g = gcd(a, b)����� c % g != 0�� ���޽⣬��� 0������ת 2 
	2)  a /= g, b /= g, c /= g;
	3)  ������չŷ������ҳ���С������ X ����  aX + by = c
	4)  ���������ʽ�� x = X + kb (k = 0,1,2,3,...)
	y = [c - a(X + kb) ] / b = -ak + (c-aX)/b,     y�ǹ���k��һ�εݼ�����
	���� k Խ���� y ԽС��Ϊ�˱�֤ y > 0�� ֻ��Ҫ  c - a(X + kb) > 0
		
		
		�� y0 = (-X * a + c) / b;
		���� y0 > ak
		
		LL ans = 0; 
		
		if(y0 <= 0) {
			ans = 0;
		}else {
			if(y0 % a) {
				ans = y0 / a;
			}else {
				ans = y0 / a + 1;
			}
		}
*/
#include <iostream>

using namespace std;

#define LL __int64
#define MAXN 100010

LL GCD(LL a, LL b) {
	return b ? GCD(b, a%b) : a;
}

// ��չŷ�����
// aX + bY = 1 
LL ExpGcd(LL a, LL b, LL &X, LL &Y) {
     LL q, temp;
     if( !b ) {
         q = a; X = 1; Y = 0;
         return q;
     }else {
        q = ExpGcd(b, a % b, X, Y);
        temp = X; 
        X = Y;
        Y = temp - (a / b) * Y;
        return q;
	 }
}

int main() {
	int t;
	scanf("%d", &t);
	
	while(t--) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		LL X, Y;
		LL g = ExpGcd(a, b, X, Y); 
		
		if(c % g != 0) {
			printf("0\n");
			continue;
		}
		a /= g;
		b /= g;
		c /= g;
		X = ( (X % b) * c ) % b;
		if( X <= 0 ) {
			X += b;
		}
		// y0 > ak
		LL y0 = (-X * a + c) / b;

		LL ans = 0; 
		
		if(y0 <= 0) {
			ans = 0;
		}else {
			if(y0 % a == 0) {
				ans = y0 / a;
			}else {
				ans = y0 / a + 1;
			}
		}
		printf("%lld\n", ans);
		 
	}
	return 0;
} 
