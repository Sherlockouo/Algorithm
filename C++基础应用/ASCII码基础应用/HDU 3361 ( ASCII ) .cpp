#include <iostream>

using namespace std;

int t, i;
int x;

int main() {
    while( scanf( "%d", &t ) != EOF ) {
        for( i = 0; i < t; i ++ ) {
            scanf("%d", &x);
            printf("%c", x );
        }
    }
}

