/*
ģ���˻�
1�����¿��� ����ȡ���ֵ
2����ʼ�㼯 ���Ը��������ص� ȡ1�����ȿ��ǣ�������
3����С�¶Ⱦ��� ������������Ҫ�ľ��ȵ���һ��������
4����ѡ�㼯����ȡ��������Χ֮�ڵĶ���
5������Ҫ��ģ���˻��ʱ�������ϲ�Ľ⣬���ݸ�����ѡ��ϲ�⣻��Ȼ��ҲҪ����ʵ����������ϲ�⡣

Author: WhereIsHeroFrom
Update Time: 2018-3-31
Algorithm Complexity: ȡ�����½��ʵķ�2Ϊ�׵�log�����Ӷ�
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define PI acos(-1.0)
#define eps 1e-6
typedef double Type;

// ��ֵ����
int threeValue(Type d) {
	if (fabs(d) < 1e-6)
		return 0;
	return d > 0 ? 1 : -1;
}

class Point3D {
	Type x, y, z;

public:
	Point3D(){
	}
	Point3D(Type _x, Type _y, Type _z) : x(_x), y(_y), z(_z) {}
	void read() {
		//scanf("%lf %lf", &x, &y);
		//z = 0;
		scanf("%lf %lf %lf", &x, &y, &z);
	}
	void print() {
		printf("<x=%lf, y=%lf, z=%lf>\n", x, y, z);
	}
	inline Type getx() const { return x; }
	inline Type gety() const { return y; }
	inline Type getz() const { return z; }
	bool inRange(Point3D& max) const;
	Point3D operator+(const Point3D& other) const;
	Point3D operator-(const Point3D& other) const;
	Point3D operator*(const double &k) const;
	Point3D operator/(const double &k) const;
	Type operator*(const Point3D& other) const;
	double len() const;
	Point3D normalize();
};

typedef Point3D Vector3D;

double Vector3D::len() const {
	return sqrt(x*x + y*y + z*z);
}

Point3D Vector3D::normalize() {
	double l = len();
	if (threeValue(l)) {
		x /= l;
		y /= l;
		z /= l;
	}
	return *this;
}

bool Point3D::inRange(Point3D& max) const {
	return (0 <= x&&x <= max.x) && (0 <= y&&y <= max.y) && (0 <= z&&z <= max.z);
}

Point3D Point3D::operator+(const Point3D& other) const {
	return Point3D(x + other.x, y + other.y, z + other.z);
}

Point3D Point3D::operator-(const Point3D& other) const {
	return Point3D(x - other.x, y - other.y, z - other.z);
}

Point3D Point3D::operator *(const double &k) const {
	return Point3D(x * k, y * k, z * k);
}

Point3D Point3D::operator /(const double &k) const {
	return (*this) * (1 / k);
}

Type Point3D::operator*(const Point3D& other) const {
	return x*other.x + y*other.y + z*other.z;
}


#define MAXN 10
#define MAXC 200
#define INF 123456786543.0

struct Point3DSet {
	int n;
	Point3D p[MAXN];
};

/*
ģ���˻�-ģ��
��Զ���������
*/
class simulatedAnnealing {
	// ��̬����ͣ��¶�
	static const double minTemperature;
	// �¶��½���
	static const double deltaTemperature;
	// ���к�ѡ�����
	static const int solutionCount;
	// ÿ����ĵ�������
	static const int candidateCount;
private:
	Point3D bound;
	Point3D x[MAXC];
	Point3DSet pointSet;
	double temperature;

	bool valid(const Point3D& pt);
	double randIn01();
	Point3D getRandomPoint();
	Vector3D getRandomDirection();
	Point3D getNext(const Point3D& now, int direction, int big);
	double getZ(double x, double y, bool big);
public:
	void start(double T, Point3DSet& pointSet);
	double evaluateFunc(const Point3D& pt);
	Point3D getSolution();
	static simulatedAnnealing& Instance();
};

// �ĸ���������
// ��̬����ͣ��¶�
const double simulatedAnnealing::minTemperature = 1e-6;
// �¶��½���
const double simulatedAnnealing::deltaTemperature = 0.99;
// ���к�ѡ�����
const int simulatedAnnealing::solutionCount = 1;
// ÿ����ĵ�������
const int simulatedAnnealing::candidateCount = 16;

int dir[8][2] = {
	{ 0, 1 },
	{ 0, -1 },
	{ 1, 0 },
	{ -1, 0 },
	{ 1, 1 },
	{ 1, -1 },
	{ -1, 1 },
	{ -1, -1 }
};

bool simulatedAnnealing::valid(const Point3D& pt) {
	return threeValue(pt.getz() - INF) != 0;
}

double simulatedAnnealing::randIn01() {
	return (rand() + 0.0) / RAND_MAX;
}

/*
���ۺ�������ֵԽСԽ��
*/
double simulatedAnnealing::evaluateFunc(const Point3D& pt) {
	return pt.len();
}

double simulatedAnnealing::getZ(double x, double y, bool big) {
	double a = pointSet.p[0].getx(), b = pointSet.p[0].gety(), c = pointSet.p[0].getz();
	double d = pointSet.p[1].getx(), e = pointSet.p[1].gety(), f = pointSet.p[1].getz();

	double A, B, C;
	A = c;
	B = d*y + e*x;
	C = f*x*y + a*x*x + b*y*y - 1;
	double delta = B*B - 4 * A*C;
	if (threeValue(delta) < 0) {
		return INF;
	}
	double z = (-B + (big ? 1 : -1) * sqrt(delta)) / 2 / A;
	return z;
}

/*
���һ��[0 - bound]�ĵ㣬���Ҫ���и����㣬�뽫�������������ƽ��
*/
Point3D simulatedAnnealing::getRandomPoint() {
	return Point3D(0, 0, getZ(0, 0, rand() % 2));
}

Point3D simulatedAnnealing::getNext(const Point3D& now, int direction, int big) {
	double x = now.getx() + temperature * dir[direction][0];
	double y = now.gety() + temperature * dir[direction][1];
	return Point3D(x, y, getZ(x, y, big));
}

/*
ģ���˻�
*/
void simulatedAnnealing::start(double T, Point3DSet& PS) {
	// 0.��ʼ���¶�
	temperature = T;
	pointSet = PS;
	int i, j;

	// 1.�������solutionCount����ʼ��
	for (i = 0; i < solutionCount; ++i) {
		x[i] = getRandomPoint();
	}


	while (temperature > minTemperature) {
		// 2.��ÿ����ǰ��������Ż�ѡ��
		for (i = 0; i < solutionCount; ++i) {
			double nextEval = INF;
			Point3D nextOpt;
			// 3.����ÿ����ǰ�⣬���ѡȡ������candidateCount���㣬���ҽ����ŵ��Ǹ��Ᵽ��
			for (j = 0; j < candidateCount; ++j) {
				Point3D next = getNext(x[i], j % 8, j / 8);

				if (!valid(next)) {
					continue;
				}
				double Eval = evaluateFunc(next);
				if (Eval < nextEval) {
					nextEval = Eval;
					nextOpt = next;
				}
			}

			// 4.û�����ɿ��н�
			if (nextEval >= INF)
				continue;

			// 5.�������ɵ����Ž��ԭ���Ľ���бȽ�
			double deltaEval = evaluateFunc(nextOpt) - evaluateFunc(x[i]);
			if (deltaEval < 0) {
				// 6.��ԭ���Ľ���ţ�ֱ���滻
				x[i] = nextOpt;
			}
			else {
				// 7.û��ԭ���Ľ��ţ�����һ�����ʽ��н���
				// ����������޻�Խ��ԽС��ֱ�����������0
				// �����ϣ������֧Ҳ���ܲ�����
				/*if( randIn01() < exp(-deltaEval/temperature) ) {
				x[i] = nextOpt;
				}    */
			}
		}
		temperature *= deltaTemperature;
	}
	//for(i = 0; i < solutionCount; ++i) x[i].print();
}

Point3D simulatedAnnealing::getSolution() {
	int retIdx = 0;
	for (int i = 1; i < solutionCount; ++i) {
		if (evaluateFunc(x[i]) < evaluateFunc(x[retIdx])) {
			retIdx = i;
		}
	}
	return x[retIdx];
}

simulatedAnnealing& simulatedAnnealing::Instance() {
	static simulatedAnnealing inst;
	return inst;
}

int main() {
	double a, b, c, d, e, f;
	while (scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f) != EOF) {
		Point3D p1(a, b, c);
		Point3D p2(d, e, f);

		Point3DSet ps;
		ps.p[0] = p1;  ps.p[1] = p2;

		simulatedAnnealing &sa = simulatedAnnealing::Instance();
		sa.start(1, ps);
		double ans = sa.evaluateFunc(sa.getSolution());
		printf("%.7lf\n", ans);
	}
}
