int gcd(int a, int b)
{
    if(b == 0) return a;
    return gcd(b, a%b);
}

int extgcd(int a, int b, int& x, int& y)
{
    int d = a;
    if(b != 0) {
        d =  extgcd(b, a%b, y , x);
        y -= (a/b) * x;
    } else {
        x = 1; y = 0;
    }
    return d;
}

LL mod_inverse(LL a,LL m){
    LL x,y;
    if(extgcd(a, m, x, y)==1)//ax+my=1
        return (x%m + m) % m;
    return -1;//not exist
}
