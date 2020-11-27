#include <iostream>
#include <algorithm>
using namespace std;

int a[3];

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &a[0], &a[1], &a[2]);
        sort(a, a + 3);

        if(a[0]*a[0] + a[1]*a[1] == a[2]*a[2]) {
            printf("good");
        }else if(a[0] == a[1] || a[1] == a[2]) {
            printf("perfect");
        }else {
            printf("just a triangle");
        }
        puts("");
    }
    return 0;
}
