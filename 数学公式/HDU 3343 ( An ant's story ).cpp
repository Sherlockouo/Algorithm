#include <iostream>

using namespace std;

#define LL __int64

LL L, v, m;

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%I64d %I64d %I64d", &L, &v, &m);
        printf("%s\n", (v > 0) ? "YES" : "NO" );
    }
    return 0;
}

