#include <iostream>

using namespace std;

#define ll __int64

ll x, f[ 100 ], ans, n;
ll val[] = { 1, 11, 111, 1111, 11111, 
    111111, 1111111, 11111111, 111111111, 111111111};
int main() {
    int i;
    f[0] = 1;

    for( i = 1; i < 100; i ++ ) {
        f[i] = f[i-1] * 10;
    }
    for( i = 1; i < 100; i ++ ) {
        f[i] += f[i-1];
        //printf("%I64d\n", f[i] );
    }
    while( scanf( "%I64d", &x ) != EOF && x ) {
        for( i = 0; f[i] > 0; i ++ ) {
            if( x % f[i] == 0 ) {
                ans = x / f[i];
            }
        }
        printf("%I64d\n", ans );
    }
    return 0;
}

