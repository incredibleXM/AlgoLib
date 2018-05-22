const double eps = 1e-10;
//2D
struct Point {
    double x, y;
    Point(double x=0, double y=0): x(x), y(y) {}
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }

Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x, A.y-B.y); }

Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }

Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }

bool operator < (const Point& a, const Point& b) {
    return a.x<b.x || (a.x==b.x && a.y<b.y);
}

int dcmp(double x) {
    if(fabs(x) < eps) return 0;
    else return x<0 ? -1 : 1;
}

bool operator == (const Point& a, const Point& b) {
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
double Area2(Point A, Point B, Point C) { return Cross(B-A, C-A); }

Vector Rotate(Vector A, double rad) {
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}

Vector Normal(Vector A) {
    double L = Length(A);
    return Vector(-A.y/L, A.x/L);
}

// Cross(v, w) != 0
Point GetLineIntersection(Point P, Vector v, Point Q, Vector w) {
    Vector u = P-Q;
    double t = Cross(w, u) / Cross(v, w);
    return P+v*t;
}

double DistanceToLine(Point P, Point A, Point B) {
    Vector v1 = B - A, v2 = P - A;
    return fabs(Cross(v1, v2)) / Length(v1);
}

double DistanceToSegment(Point P, Point A, Point B) {
    if(A == B) return Length(P-A);
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if(dcmp(Dot(v1, v3)) > 0) return Length(v3);
    else return fabs(Cross(v1, v2)) / Length(v1);
}

Point GetLineProjection(Point P, Point A, Point B) {
    Vector v = B - A;
    return A+v*(Dot(v, P-A) / Dot(v, v));
}

bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2) {
    double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1),
            c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

bool OnSegment(Point P, Point a1, Point a2) {
    return dcmp(Cross(a1-p, a2-p))==0 && dcmp(Dot(a1-p, a2-p))<0;
}

double PolygoArea(Point* p, int n) {
    double area = 0;
    for(int i=1; i<n-1; i++) {
        area += Cross(p[i]-p[0], p[i+1]-p[0]);
    }
    return area / 2.0;
}

//3D
