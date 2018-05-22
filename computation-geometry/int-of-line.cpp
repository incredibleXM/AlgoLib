//poj 1269
#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const double eps = 1e-8;
const double PI = acos(-1.0);

int sgn(double x)
{
    if(fabs(x) < eps) return 0;
    if(x < 0) return -1;
    else return 1;
}

struct Point
{
    double x, y;
    Point(){}
    Point(double a, double b)
    {
        x = a; y = b;
    }
    Point operator -(const Point& b) const
    {
        return Point(x-b.x, y-b.y);
    }
    double operator ^(const Point& b) const
    {
        return x*b.y-y*b.x;
    }
    double operator *(const Point& b) const
    {
        return x*b.x+y*b.y;
    }
};

struct Line
{
    Point s, e;
    Line(){}
    Line(Point a, Point b)
    {
        s = a; e = b;
    }
};

Point res;
int cmp(const Line& a, const Line& b)
{
    res = a.s;
    if(sgn((a.e-a.s)^(b.e-b.s)) == 0)
    {
        if(sgn((a.e-b.s)^(b.e-a.s)) == 0)
            return 0; //重合
        else return 1; //平行
    }
    double t = ((a.s-b.s)^(b.s-b.e))/((a.s-a.e)^(b.s-b.e));
    res.x += (a.e.x-a.s.x)*t;
    res.y += (a.e.y-a.s.y)*t;
    return 2; //相交
}

int n;
Line l1[12], l2[12];
int main() {
    cin >> n;
    for (int i=0; i<n; i++) {
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &l1[i].s.x, &l1[i].s.y,
            &l1[i].e.x, &l1[i].e.y, &l2[i].s.x, &l2[i].s.y, &l2[i].e.x, &l2[i].e.y);
    }
    cout << "INTERSECTING LINES OUTPUT" << endl;
    for(int i=0; i<n; i++) {
        int t = cmp(l1[i], l2[i]);
        if(t == 0)
            cout << "LINE" << endl;
        else if(t == 1)
            cout << "NONE" << endl;
        else
            printf("POINT %.2f %.2f\n", res.x, res.y);
    }
    cout << "END OF OUTPUT" << endl;
    return 0;
}
