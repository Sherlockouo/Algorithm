#include <iostream>

using namespace std;

char str[ 10000 ];
int i;

int main() {
    int cas = 1;

    while( scanf( "%s", str ) != EOF ) {
        
        if( str[0] == '-' )
            break;

        int ans = 0;
        int s = 0;
        for( i = 0; str[i]; i ++ ) {
            if( str[i] == '{' )
                s ++;
            else
                s --;

            if( s < 0 ) {
                ans ++;
                s += 2;
            }
        }
        ans += s / 2;
        printf("%d. %d\n", cas++, ans );
    }
    return 0;
}

