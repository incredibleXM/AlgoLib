Point list[MAX_N];
int st[MAX_N], top;

bool _cmp(Point p1, Point p2)
{
    double tmp = (p1-list[0]) ^ (p2-list[0]);
    if(sgn(tmp) > 0) return true;
    else if(sgn(tmp)==0 && sgn(dist(p1, list[0]) - dist(p2, list[0])) <= 0)
        return true;
    else return false;
}

void Graham(int n)
{
    Point p0 = list[0];
    int k = 0;
    for(int i=1; i<n; i++) {
        if((p0.y > list[i].y) || (p0.y==list[i].y && p0.x>list[i].x)) {
            p0 = list[i];
            k = i;
        }
    }
    swap(list[k], list[0]);
    sort(list+1, list+n, _cmp);
    if(n == 1) {
        top = 1;
        st[0] = 0;
        return;
    }
    if(n == 2) {
        top = 2;
        st[0] = 0;
        st[1] = 1;
        return;
    }
    st[0] = 0;
    st[1] = 1;
    top = 2;
    for(int i=2; i<n; i++) {
        while(top>1 && sgn((list[st[top-1]]-list[st[top-2]])^(list[i]-list[st[top-2]])) <= 0) top--;
        st[top++] = i;
    }
}
