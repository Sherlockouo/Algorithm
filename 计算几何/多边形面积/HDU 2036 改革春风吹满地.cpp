// HDU 2036
// ���㼸�Σ���������
// ��� �������

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

struct Point {
	Point() {

	}
	Point(double _x, double _y) : x(_x), y(_y) {

	}

	void Scanf() {
		scanf("%lf %lf", &x, &y);
	}

	Point operator+(const Point& o) {
		return Point(x + o.x, y + o.y);
	}


	Point operator-(const Point& o) {
		return Point(x - o.x, y - o.y);
	}

	double cross(const Point& o) {
		return x * o.y - y * o.x;
	}

private:
	double x, y;

}P[1000];

int n;
int main() {

	int i;
	while (scanf("%d", &n) != EOF && n) {
		for (i = 0; i < n; ++i) {
			P[i].Scanf();
		}
		double ans = 0;
		for (i = 1; i < n - 1; ++i) {
			ans += (P[i] - P[0]).cross(P[i + 1] - P[0]);
		}
		printf("%.1lf\n", fabs(ans) / 2);
	}
	return 0;
}