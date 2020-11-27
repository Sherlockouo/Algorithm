#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#define pi acos(-1.0)
using namespace std;

#define MAXP 50005
#define eps    1e-7
  
class Point2D;
typedef Point2D vector2D;

class Point2D {
public:
    double x, y;
    Point2D () {
        x = 0, y = 0;
    }
    Point2D( double _x, double _y ) {
        x = _x;
        y = _y;
    }
    void read() {
        scanf("%lf %lf", &x, &y);
    }
    
    Point2D operator+(const Point2D& p) {
        return Point2D(x + p.x, y + p.y);
    }
    Point2D operator-(const Point2D& p) {
        return Point2D(x - p.x, y - p.y);
    }
    double operator*(const Point2D& p) {
        return x * p.x + y * p.y; 
    }
    double operator^(const Point2D& p) {
        return x * p.y - y * p.x;
    }
    double dist(const Point2D& p) {
        Point2D q = *this - p;
        return sqrt( q.x*q.x + q.y*q.y );
    }
    Point2D operator*(const double& val) {
        return Point2D(x * val, y * val); 
    }
};

class Polygon {
public:
    int sta[MAXP];      //在凸包上点的下标
    Point2D point[MAXP];
    bool flag[MAXP];
    int top, n, stab;            //n为读入的点的个数,top-1为凸包上点的个数,0 -- top-2是凸包上点的坐标,top-1和0存的都是第一个点.

    Polygon() { top = n = 0; }
    
    static bool cmp(const Point2D& A,const Point2D& B) { 
        return A.x < B.x || A.x == B.x && A.y < B.y;
    }
    void convexHull(bool f);           //求凸包上的点,f为true表示求的包括边上的点*
    void getpoint(int i,bool f);
    
    void printConvexHull();
    
    double length();
    double area();

private:
    // 要检测的点是否在栈顶边的右侧
    bool is_right_point(int index, bool f) {
        Point2D pt1 = point[index] - point[ sta[top-2] ];
        Point2D pt2 = point[ sta[top-1] ] - point[ sta[top-2] ];
        double xPro = pt1 ^ pt2;
        if (f) {
            return xPro > 0.0 || fabs(xPro) < eps;
        }
        return xPro > 0.0;
    }
};

void Polygon::getpoint(int i, bool f)
{
    if(top == stab || is_right_point(i, f) ) {
        sta[top++] = i;
        flag[i] = false;
    }
    else {
        
        do {
            top --;
            flag[sta[top]] = true;
        }while ( top > stab && !is_right_point(i, f) );
        
        sta[top++] = i;
        flag[i] = false;
    }
}

void Polygon::convexHull(bool f) {
    int i;
    memset(flag, true, n + 1);
    sort(point, point + n, cmp);
    sta[0] = 0;
    sta[1] = 1;
    top = 2;
    flag[1] = false;
    stab = 1;
    for(i = 2; i < n; i++) 
        getpoint(i, f);
    stab = top;
    for(i = n-2; i >= 0; i--) 
        if(flag[i]) 
            getpoint(i,f);
}

void Polygon::printConvexHull() {
    for(int i = 0; i < top; i++) {
        printf("%lf %lf\n", point[ sta[i] ].x, point[ sta[i] ].y );
    }    
}

double Polygon::length() {
    double ans = 0;
    for(int i = 0; i < top-1; i++) {
        ans += point[ sta[i] ].dist( point[ sta[i+1] ] );
    }
    return ans;
}

double Polygon::area() {
    double ans = 0;
    for(int i = 0; i < top - 1; i++) {
        ans += point[sta[i]] ^ point[sta[i+1]];
    }
    return fabs(ans) / 2;
}


Polygon Tubao;

int main() {
    int t;
    int c, n;
    int i;
    scanf("%d", &t);
    
    while(t--) {
        scanf("%d %d", &c, &n);
        Tubao.n = n;
        for(i = 0; i < n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            Tubao.point[i] = Point2D(x, y);
        }
        Tubao.convexHull(false);
        Tubao.top--;
        int idx = 0;
        for(i = 1; i < Tubao.top; i++) {
            Point2D now = Tubao.point[ Tubao.sta[i] ];
            Point2D pre = Tubao.point[ Tubao.sta[idx] ];
            if(now.y > pre.y || fabs(now.y-pre.y)<eps && now.x < pre.x ) {
                idx = i;
            }
        }
        printf("%d %d\n", c, Tubao.top);
        int cnt = Tubao.top;
        for(i = idx; ; i++) {
            Point2D pt = Tubao.point[ Tubao.sta[i%Tubao.top] ];
            printf("%.0lf %.0lf\n", pt.x, pt.y);
            cnt --;
            if(!cnt) break;
        }
        
    }
    return 0;
}

