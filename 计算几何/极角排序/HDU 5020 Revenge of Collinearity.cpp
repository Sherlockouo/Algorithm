/*
    �������������Ǻܴ�ģ��������������������������
*/
#include <iostream>
#include <algorithm>
using namespace std;

#define INT_POINT


const int MAXP = 2010;
const double eps = 1e-10;
#define NINT_POINT


#ifdef INT_POINT
typedef int PointType;
typedef long long BigPointType;    // ���ڳ˷����ܵ��� int �����������Ҫ����һ�ֳ˷��������(ƽ������ˡ����)
#else
typedef double PointType;
typedef double BigPointType;
#endif
typedef int PointIndex;

// С��
bool ST(BigPointType a, BigPointType b) {
#ifdef INT_POINT
    return a < b;
#else
    return a - b < -eps;
#endif
}

// ����
bool EQ(BigPointType a, BigPointType b) {
#ifdef INT_POINT
    return a == b;
#else
    return fabs(a - b) < eps;
#endif
}

// ����
bool LT(BigPointType a, BigPointType b) {
    return !ST(a, b) && !EQ(a, b);
}

int TernaryFunc(double v) {
    if (EQ(v, 0)) {
        return 0;
    }
    return ST(v, 0) ? -1 : 1;
}

BigPointType SQR(BigPointType x) {
    return x * x;
}

class Point2D {
public:
    Point2D() : x_(0), y_(0) {}
    Point2D(PointType x, PointType y) : x_(x), y_(y) {}

    bool zero() const;
    Point2D operator - (const Point2D& pt) const;
    bool operator < (const Point2D& pt) const;
    BigPointType cross(const Point2D& pt) const;
    BigPointType distSquare(const Point2D& pt) const;
    static bool angleCmp(const Point2D& a, const Point2D& b);
    void calculateAngle(const Point2D& o);

    void read(int idx);
    void print();
    PointType x() const;
    PointType y() const;
    double getAngle() const;
    int getIndex() const;

    Point2D getMinusYPoint() const;
private:
    PointType x_, y_;
    double angle_;            // ��������½ǵ�ļ���
    double distSqr_;          // ��������½ǵ�ľ���ƽ��
    int index_;               // ��ԭ������±꣬����������
};
typedef Point2D Vector2D;

bool Point2D::zero() const {
    return EQ(x_, 0) && EQ(y_, 0);
}

BigPointType Vector2D::cross(const Vector2D& pt) const {
    return (BigPointType)x_ * pt.y_ - (BigPointType)y_ * pt.x_;
}

Point2D Point2D::operator - (const Point2D& pt) const {
    return Point2D(x_ - pt.x_, y_ - pt.y_);
}

bool Point2D::operator<(const Point2D& pt) const {
    // 1. ��һ�ؼ��֣� y С��
    // 2. �ڶ��ؼ��֣� x С��
    // 3. �����ؼ��֣��±�С�� - �������ظ���
    if (!EQ(y_, pt.y_)) {
        return ST(y_, pt.y_);
    }
    if (!EQ(x_, pt.x_)) {
        return ST(x_, pt.x_);
    }
    return index_ < pt.index_;
}


BigPointType Point2D::distSquare(const Point2D& pt) const {
    Point2D t = *this - pt;
    return SQR(t.x_) + SQR(t.y_);
}

bool Point2D::angleCmp(const Point2D& a, const Point2D& b) {
    if (fabs(a.angle_ - b.angle_) > eps) {
        return a.angle_ < b.angle_;
    }
    if (fabs(a.distSqr_ - b.distSqr_) > eps) {
        return a.distSqr_ < b.distSqr_;
    }
    return a.index_ < b.index_;
}

void Point2D::calculateAngle(const Point2D& o) {
    Point2D t = *this - o;
    if (t.zero()) {
        // ������� atan2 �� undefined �ģ���Ҫ��������
        angle_ = 0;
        distSqr_ = 0;
    }
    else {
        angle_ = atan2(0.0 + t.y_, 0.0 + t.x_); // ���� y >= 0 ���ܱ�֤�ģ�����ֵ�� [0, PI) ֮��
        distSqr_ = distSquare(o);
    }
}

void Point2D::read(int idx) {
#ifdef INT_POINT
    scanf("%d %d", &x_, &y_);
#else
    scanf("%lf %lf", &x_, &y_);
#endif
    index_ = idx;
}

void Point2D::print() {
#ifdef INT_POINT
    printf("%d %d\n", x_, y_);
#else
    printf("%lf %lf", x_, y_);
#endif
}

PointType Point2D::x() const {
    return x_;
}

PointType Point2D::y() const {
    return y_;
}

double Point2D::getAngle() const {
    return angle_;
}

int Point2D::getIndex() const {
    return index_;
}


const int MAXN = 1010;
Point2D P[MAXN], Q[MAXN];


/*
    ���⣺���� n(n <= 1000) ���㣬���ж��ٸ���Ԫ�飨�����飩�������㹲�ߣ�

    ��⣺
    1������ÿ���� P����Ϊ�����½ǵ㣬�������������������ģ����뵽���� S �У�
    2���Լ��� S ���յ� P ���м�������
    3������ԭ�� P ��ѡ���ٸ��ݼ���˳��ѡ���������ߵ㣬������ x �����ԭ�㹲��  C(x,2)
*/

int main() {
    int t;
    int n;
    scanf("%d", &t);

    while (t--) {

        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            P[i].read(i);
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int s = 0;
            for (int j = 1; j <= n; ++j) {
                if (j==i || P[j] < P[i]) continue;

                Q[s] = P[j];
                Q[s].calculateAngle(P[i]);
                ++s;
            }
            sort(Q, Q + s, Point2D::angleCmp);
            int start = 0;
            int ans1 = 0;
            for (int j = 0; j <= s; ++j) {
                if (j == s || (Q[j]-P[i]).cross(Q[start]-P[i]) != 0 ) {    
                    // �������������Ǻܴ�ģ��������������������������
                    int cnt = j - start;
                    ans1 += cnt * (cnt-1) / 2;
                    start = j;
                }
            }
            //printf("%d %d %d %d\n", P[i].x(), P[i].y(), s, ans1);
            ans += ans1;
        }

        printf("%d\n", ans);
    }
    return 0;
}

/*
8
0 0 
1 1
2 0
2 2
0 2
3 3
2 3
0 3

9
0 0 
1 0
2 0
0 1
1 1
2 1
0 2
1 2
2 2

9
0 0
-1000000000 0
1000000000 0
-1000000000 1000000000
-1000000000 -1000000000
0 1000000000
0 -1000000000
1000000000 1000000000
1000000000 -1000000000

9
0 0
2 2
4 4
-2 -2 
-4 -4
2 -4
2 4
-2 -4
-2 4
16

16
0 0
1 0
2 0
3 0
0 1
1 1
2 1
3 1
0 2
1 2
2 2
3 2
0 3
1 3
2 3
3 3
*/