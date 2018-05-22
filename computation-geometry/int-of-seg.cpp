//poj 1066
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

bool inter(Line l1, Line l2)
{
    return
    max(l1.s.x, l1.e.x) >= min(l2.s.x, l2.e.x) &&
    max(l2.s.x, l2.e.x) >= min(l1.s.x, l1.e.x) &&
    max(l1.s.y, l1.e.y) >= min(l2.s.y, l2.e.y) &&
    max(l2.s.y, l2.e.y) >= min(l1.s.y, l1.e.y) &&
    sgn((l2.s-l1.e)^(l1.s-l1.e)) * sgn((l2.e-l1.e)^(l1.s-l1.e)) <= 0 &&
    sgn((l1.s-l2.e)^(l2.s-l2.e)) * sgn((l1.e-l2.e)^(l2.s-l2.e)) <= 0;
}

int n;
Line l[32];
Point tar;
int ans = 0x7fffffff;
int main() {
    cin >> n;
    for(int i=0; i<n; i++) {
        scanf("%lf%lf%lf%lf", &l[i].s.x, &l[i].s.y, &l[i].e.x, &l[i].e.y);
    }
    scanf("%lf%lf", &tar.x, &tar.y);
    if(n == 0)
        ans = 1;
    for(int i=0; i<n; i++) {
        Line tmp(l[i].s, tar);
        int cnt = 0;
        for(int j=0; j<n; j++) {
            if(inter(tmp, l[j]))
                cnt++;
        }
        if(cnt < ans) ans = cnt;
        tmp.s = l[i].e;
        cnt = 0;
        for(int j=0; j<n; j++) {
            if(inter(tmp, l[j]))
                cnt++;
        }
        if(cnt < ans) ans = cnt;
    }
    printf("Number of doors = %d\n", ans);
    return 0;
}
