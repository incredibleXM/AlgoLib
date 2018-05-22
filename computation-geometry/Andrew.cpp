// 计算凸包,输入点数组p,个数为n,输出点数组ch.函数返回凸包顶点数
// 输入不能有重复点.函数执行完之后输入点的顺序被破坏
// 如果不希望在凸包的边上有输入点,把两个 <= 改成 <
bool _cmp(Point p1, Point p2)
{
    int tmp = sgn(p1.x-p2.x)
    if(tmp == 0) {
        if(sgn(p1.y-p2.y) < 0) return true;
        else return false;
    } else if(tmp == -1) return true;
    else return false;
}

int Andrew(vector<Point>& p, int n, vector<Point>& ch)
{
    sort(p, p+n, _cmp);
    int m = 0;
    for(int i=0; i<n; i++) {
        while(m>1 && sgn((ch[m-1]-ch[m-2]) ^ (p[i]-ch[m-2])) == -1) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i=n-2; i>=0; i--) {
        while(m>k && sgn((ch[m-1]-ch[m-2]) ^ (p[i]-ch[m-2])) == -1) m--;
        ch[m++] = p[i];
    }
    if(n > 1) m--;
    return m;
}
