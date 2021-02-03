#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;

const int MAXP = 100010;
const double eps = 1e-10;
#define INT_POINT

#ifdef INT_POINT
typedef int PointType;
typedef long long MultiplyType;    // ���ڳ˷����ܵ��� int �����������Ҫ����һ�ֳ˷��������(ƽ������ˡ����)
#else
typedef double PointType;
typedef double MultiplyType;
#endif
typedef int PointIndex;

// С��
bool ST(PointType a, PointType b) {
#ifdef INT_POINT
    return a < b;
#else
    return a - b < -eps;
#endif
}

// ����
bool EQ(PointType a, PointType b) {
#ifdef INT_POINT
    return a == b;
#else
    return fabs(a - b) < eps;
#endif
}

// ����
bool LT(PointType a, PointType b) {
    return !ST(a, b) && !EQ(a, b);
}

int TernaryFunc(double v) {
    if (EQ(v, 0)) {
        return 0;
    }
    return ST(v, 0) ? -1 : 1;
}

MultiplyType SQR(MultiplyType x) {
    return x * x;
}

class Point2D {
public:
    Point2D() : x_(0), y_(0) {}
    Point2D(PointType x, PointType y) : x_(x), y_(y) {}

    bool zero() const;
    Point2D operator + (const Point2D& pt) const;
    Point2D operator - (const Point2D& pt) const;
    MultiplyType cross(const Point2D& pt) const;
    bool operator < (const Point2D& pt) const;
    bool operator == (const Point2D& pt) const;


    MultiplyType distSquare(const Point2D& pt) const;
    static bool angleCmp(const Point2D& a, const Point2D& b);
    void calculateAngle(const Point2D& o);

    void read(int idx);
    void print();
    double getAngle() const;

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

Point2D Point2D::operator + (const Point2D& pt) const {
    return Point2D(x_ + pt.x_, y_ + pt.y_);
}

Point2D Point2D::operator - (const Point2D& pt) const {
    return Point2D(x_ - pt.x_, y_ - pt.y_);
}

MultiplyType Vector2D::cross(const Vector2D& pt) const {
    return (MultiplyType)x_ * pt.y_ - (MultiplyType)y_ * pt.x_;
}

bool Point2D::operator<(const Point2D& pt) const {
    // 1. ��һ�ؼ��֣� y С��
    // 2. �ڶ��ؼ��֣� x С��
    if (!EQ(y_, pt.y_)) {
        return ST(y_, pt.y_);
    }
    return ST(x_, pt.x_);
}

bool Point2D::operator==(const Point2D& pt) const {
    return (*this - pt).zero();
}

MultiplyType Point2D::distSquare(const Point2D& pt) const {
    Point2D t = *this - pt;
    return SQR(t.x_) + SQR(t.y_);
}

bool Point2D::angleCmp(const Point2D& a, const Point2D& b) {
    if (fabs(a.angle_ - b.angle_) < eps) {
        return a.distSqr_ < b.distSqr_;
    }
    return a.angle_ < b.angle_;
}

void Point2D::calculateAngle(const Point2D& o) {
    Point2D t = *this - o;
    if (t.zero()) {
        // ������� atan2 �� undefined �ģ���Ҫ��������
        angle_ = 0;
        distSqr_ = 0;
    }
    else {
        angle_ = atan2(0.0 + t.y_, 0.0 + t.x_); // ���� y >= 0 ���ܱ�֤�ģ�����ֵ�� [0, PI] ֮��
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

double Point2D::getAngle() const {
    return angle_;
}

Point2D Point2D::getMinusYPoint() const
{
    return Point2D(x_, -y_);
}

class Polygon {
private:
    void grahamScan_Pre();   // ����͹��ǰ��׼������
    void grahamScan_Post(bool flag, Polygon& ret);  // ���͹���ĵ㵽�����Ķ����
public:
    bool isPoint() const;    // ����͹���Ժ��ж��Ƿ���һ����
    bool isLine() const;     // ����͹���Ժ��ж��Ƿ���һ����
    void grahamScan(bool flag, Polygon& ret);
    double area();
    double length();

    void clear();
    void addPoint(const Point2D& pt);
public:
    bool output(int cas);           // ���ݲ�ͬ����ṩ�Ŀ��Žӿ�
private:
    int n_;
    Point2D point_[MAXP];
    PointIndex stack_[MAXP];
    int top_;
};

bool Polygon::isPoint() const  {
    if (n_ <= 1) {
        return true;
    }
    return point_[n_ - 1] == point_[0];
}

bool Polygon::isLine() const {
    if (n_ <= 2) {
        return true;
    }
    return (TernaryFunc((point_[n_ - 1] - point_[0]).cross(point_[1] - point_[0])) == 0);
}


void Polygon::grahamScan_Pre()
{
    // 1. ���Ƚ���������Ǹ��㣨���y��ͬ����ȡ����ߣ��ҳ����ŵ� point_[0] ��λ��
    for (int i = 1; i < n_; ++i) {
        if (point_[i] < point_[0]) {
            swap(point_[i], point_[0]);
        }
    }
    // 2. �� point_[0] ���㼫��
    for (int i = 1; i < n_; ++i) {
        point_[i].calculateAngle(point_[0]);
    }
    // 3. ��������
    sort(point_ + 1, point_ + n_, Point2D::angleCmp);
}


void Polygon::grahamScan_Post(bool flag, Polygon& ret) {
    ret.n_ = top_;
    for (int i = 0; i < top_; ++i) {
        ret.point_[i] = point_[stack_[i]];
    }

    if (ret.isPoint() || ret.isLine()) {
        // �ǵ�����ߵ���������в���
        return;
    }

    // Graham ɨ���㷨�ĸĽ������Ҫ���Ǳ��ϵĵ�
    // ��ô���һ������εĻر�
    if (flag) {
        for (int i = n_ - 1; i >= 0; --i) {
            if (point_[i] == ret.point_[top_ - 1]) continue;
            if (fabs(point_[i].getAngle() - ret.point_[top_ - 1].getAngle()) < eps) {
                // ������ͬ�ĵ���벹����
                ret.point_[ret.n_++] = point_[i];
            }
            else break;
        }
    }
}

// flag �Ƿ����ϱ��ϵĵ㡢�ظ���
void Polygon::grahamScan(bool flag, Polygon& ret) {

    // �ҵ���ֵ����ϵԭ�㣬���Ұ��ռ�������
    grahamScan_Pre();

    // ջ����Զ���Ǹ���ֵ����ϵ��ԭ��
    top_ = 0;
    stack_[top_++] = 0;

    for (int i = 1; i < n_; ++i) {
        if ((point_[i] - point_[0]).zero()) {
            // ��ԭ�����غϣ�������ظ�
            if (flag) {
                stack_[top_++] = i;
            }
            continue;
        }

        while (top_ >= 2) {
            Point2D p1 = point_[stack_[top_ - 1]] - point_[stack_[top_ - 2]];
            Point2D p2 = point_[i] - point_[stack_[top_ - 2]];
            MultiplyType crossRet = p1.cross(p2);
            // ���ѡ����ϵĵ㣬��ô��˽�����ڵ���0�������
            // �����ѡ����ϵĵ㣬��ô��˽������0�������
            if (flag && TernaryFunc(crossRet) < 0 || !flag && TernaryFunc(crossRet) <= 0)
                --top_;
            else
                break;
        }
        stack_[top_++] = i;
    }

    grahamScan_Post(flag, ret);
}

double Polygon::area() {
    double ans = 0;
    point_[n_] = point_[0];
    for (int i = 1; i < n_; ++i) {
        ans += (point_[i] - point_[0]).cross(point_[i + 1] - point_[0]);
    }
    return ans / 2;
}

double Polygon::length() {
    if (n_ == 1) {
        return 0;
    }
    else if (n_ == 2) {
        return sqrt(0.0 + point_[1].distSquare(point_[0])) * 2;
    }
    double ans = 0;
    point_[n_] = point_[0];
    for (int i = 0; i < n_; ++i) {
        ans += sqrt(0.0 + point_[i].distSquare(point_[i + 1]));
    }
    return ans;
}

void Polygon::clear() {
    n_ = 0;
    top_ = 0;
}

void Polygon::addPoint(const Point2D& pt) {
    point_[n_++] = pt;
}

bool Polygon::output(int cas) {
    int minIdx = 0;
    for (int i = 0; i < n_; ++i) {
        point_[i] = point_[i].getMinusYPoint();
        if (point_[i] < point_[minIdx]) {
            minIdx = i;
        }
    }
    printf("%d %d\n", cas, n_);
    int cnt = n_;
    for (int i = minIdx; cnt > 0; --i, --cnt) {
        int idx = (i % n_ + n_) % n_;
        point_[idx].getMinusYPoint().print();
    }
    return true;
}

Polygon P, Res;

int main() {
    int t;
    int cas, n;

    scanf("%d", &t);
    while (t--) {
        P.clear();
        scanf("%d %d", &cas, &n);
        for (int i = 0; i < n; ++i) {
            Point2D pt;
            pt.read(i);
            P.addPoint(pt);
        }
        P.grahamScan(false, Res);
        Res.output(cas);
    }
    return 0;
}
