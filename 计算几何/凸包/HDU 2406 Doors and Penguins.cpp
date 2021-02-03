#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;

//************************* ���㼸�� ģ�� *************************
// ������
// 1��͹��
// 2���߶��н�
// 3�����ڶ������
// 4������ν��ж�

const int MAXP = 100010;
const double eps = 1e-10;
#define INT_POINT

// ���߶ν�������
enum SegCrossType {
    SCT_NONE = 0,
    SCT_CROSS = 1,         // �����ཻ
    SCT_ENDPOINT_ON = 2,   // ����һ���߶εĶ˵�����һ����
};

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
    Point2D operator + (const Point2D& pt) const;
    Point2D operator - (const Point2D& pt) const;
    BigPointType operator * (const Point2D& pt) const;
    BigPointType cross(const Point2D& pt) const;
    bool operator < (const Point2D& pt) const;
    bool operator == (const Point2D& pt) const;


    BigPointType distSquare(const Point2D& pt) const;
    static bool angleCmp(const Point2D& a, const Point2D& b);
    void calculateAngle(const Point2D& o);

    void read(int idx);
    void print();
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

Point2D Point2D::operator + (const Point2D& pt) const {
    return Point2D(x_ + pt.x_, y_ + pt.y_);
}

Point2D Point2D::operator - (const Point2D& pt) const {
    return Point2D(x_ - pt.x_, y_ - pt.y_);
}

BigPointType Point2D::operator * (const Point2D& pt) const {
    return x_ * pt.x_ + y_ * pt.y_;
}

BigPointType Vector2D::cross(const Vector2D& pt) const {
    return (BigPointType)x_ * pt.y_ - (BigPointType)y_ * pt.x_;
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

BigPointType Point2D::distSquare(const Point2D& pt) const {
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

int Point2D::getIndex() const {
    return index_;
}

Point2D Point2D::getMinusYPoint() const
{
    return Point2D(x_, -y_);
}

class Segment2D {
public:
    Segment2D(){}
    Segment2D(Point2D from, Point2D to) : from_(from), to_(to) {}
    BigPointType cross(const Point2D& p) const;
    bool lineCross(const Segment2D& other) const;
    bool pointOn(const Point2D& p) const;
    SegCrossType segCross(const Segment2D& other);
private:
    Point2D from_, to_;
};

// ������
// �ⲿ��һ��p��Ȼ����� (p-s) X (t-s)
BigPointType Segment2D::cross(const Point2D& p) const {
    return (p - from_).cross(to_ - from_);
}

// ��������
// ����ǰ�߶���Ϊһ���ܳ���ֱ�ߣ�����߶�other�Ƿ����������ֱ�ߵ�����
bool Segment2D::lineCross(const Segment2D& other) const {
    return TernaryFunc(cross(other.from_)) * TernaryFunc(cross(other.to_)) == -1;
}

// ���Ƿ����߶���
bool Segment2D::pointOn(const Point2D& p) const {
    // ��������������
    //  1.���Ϊ0��    (p-s)��(t-s) == 0
    //  2.���Ϊ-1��0��(p-s)*(p-t) <= 0
    return TernaryFunc(cross(p)) == 0 && TernaryFunc((p - from_) * (p - to_)) <= 0;
}

// �߶��н�
// 1.ͨ����������
// 2.���Ƿ����߶���
SegCrossType Segment2D::segCross(const Segment2D& other) {
    if (this->lineCross(other) && other.lineCross(*this)) {
        // ���ο��������������Ȼ�ཻ��һ��
        return SCT_CROSS;
    }
    // ����һ���߶ε�ĳ���˵��Ƿ�������һ���߶��ϣ��������
    if (pointOn(other.from_) || pointOn(other.to_) ||
        other.pointOn(from_) || other.pointOn(to_)) {
        return SCT_ENDPOINT_ON;
    }
    return SCT_NONE;
}


class Polygon {
private:
    void grahamScan_Pre();   // ����͹��ǰ��׼������
    void grahamScan_Post(bool flag, Polygon& ret);  // ���͹���ĵ㵽�����Ķ����
public:
    bool isPoint() const;                      // ����͹���Ժ��ж��Ƿ���һ����
    bool isLine() const;                       // ����͹���Ժ��ж��Ƿ���һ����
    bool isPointIn(const Point2D& pt) const;   // �жϵ��Ƿ��ڶ�����ڣ�
    bool isIntersectWithPolygon(Polygon &o);   // �ж��Ƿ�����һ������н�����
    void grahamScan(bool flag, Polygon& ret);
    double area();
    double length();
    int size();
    void clear();
    void addPoint(const Point2D& pt);
public:
    //bool check(Polygon& o);           // ���ݲ�ͬ����ṩ�Ŀ��Žӿ�
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


bool Polygon::isPointIn(const Point2D& pt) const {
    Point2D inf(123456543, 132543876);
    Segment2D judge(pt, inf);
    int isIn = 0;
    for (int i = 0; i < n_; ++i) {
        if (Segment2D(point_[i], point_[i + 1]).segCross(judge) != SCT_NONE) {
            isIn ^= 1;
        }
    }
    return isIn;
}

bool Polygon::isIntersectWithPolygon(Polygon& o) {
    // 1. ��������εı��н��������� false
    for (int i = 0; i < n_; ++i) {
        Segment2D srcSeg(point_[i], point_[i + 1]);
        for (int j = 0; j < o.n_; ++j) {
            Segment2D tarSeg(o.point_[j], o.point_[j + 1]);
            if (srcSeg.segCross(tarSeg) != SCT_NONE) {
                return false;
            }
        }
    }

    // 2. һ������εĵ�����һ���������
    for (int i = 0; i < n_; ++i) {
        if (o.isPointIn(point_[i])) {
            return false;
        }
    }

    for (int i = 0; i < o.n_; ++i) {
        if (isPointIn(o.point_[i])) {
            return false;
        }
    }

    return true;
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
    // ���ɻ�·
    ret.point_[ret.n_] = ret.point_[0];
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
            BigPointType crossRet = p1.cross(p2);
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

int Polygon::size() {
    return n_;
}

void Polygon::clear() {
    n_ = 0;
    top_ = 0;
}

void Polygon::addPoint(const Point2D& pt) {
    point_[n_++] = pt;
}

//************************* ���㼸�� ģ�� *************************

Polygon D, P, DRes, PRes;

int main() {
    int n, p;
    Point2D s, t;
    int cas = 0;
    int x1, y1, x2, y2;
    while (scanf("%d %d", &n, &p) != EOF && (n || p)) {
        if (cas++) puts("");
        D.clear();
        P.clear();
        for (int i = 0; i < n; ++i) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            D.addPoint(Point2D(x1, y1));
            D.addPoint(Point2D(x1, y2));
            D.addPoint(Point2D(x2, y1));
            D.addPoint(Point2D(x2, y2));
        }
        for (int i = 0; i < p; ++i) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            P.addPoint(Point2D(x1, y1));
            P.addPoint(Point2D(x1, y2));
            P.addPoint(Point2D(x2, y1));
            P.addPoint(Point2D(x2, y2));
        }
        D.grahamScan(false, DRes);
        P.grahamScan(false, PRes);
        bool ans = DRes.isIntersectWithPolygon(PRes);
        printf("Case %d: %s\n", cas, ans ? "It is possible to separate the two groups of vendors." : "It is not possible to separate the two groups of vendors.");
    }
    return 0;
}