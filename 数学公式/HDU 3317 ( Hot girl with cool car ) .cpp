#include <iostream>
#include <cmath>
using namespace std;

double r, w, t;
#define pi acos( -1.0 )
 
double la( double t ) {
    return cos( t / 360 * pi );
}
int main() {
    while( scanf( "%lf %lf %lf", &r, &w, &t ) != EOF ) {
        printf("%.3lf\n", r + w * ( 1 / (1-la(t)) ) );
    }
}
