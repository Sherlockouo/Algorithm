#include <iostream>

using namespace std;
int n;

int main() {
    int t = 1;
    while( scanf( "%d", &n ) != EOF && n) {
        printf("%d. ", t ++ );
        printf( "%s %d\n",  n % 2 ? "odd" : "even", n / 2 );
    }
    return 0;
}

