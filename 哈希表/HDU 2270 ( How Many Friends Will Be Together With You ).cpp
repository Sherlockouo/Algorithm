#include <iostream>

using namespace std;

int id[1000001];

int a[1000001];
int n, coun;

int main() {

    while(scanf("%d", &n) != EOF) {
        for(int i = 1; i <= n; i++) {
            id[i] = i;
        }

        for(i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            id[ a[i] ] = id[ i ];
        }

        coun = 0;
        for(i = 1; i <= n ;i++) {
            if(id[i] == id[1] && i != 1)
                coun ++;
        }

        printf("%d\n", coun);
    }
    return 0;
}
