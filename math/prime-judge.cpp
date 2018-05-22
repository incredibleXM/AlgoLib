//O(sqrt(n))
bool isPrime(int num)
{
    if(num ==2 || num==3) return 1 ;
    if(num%6 != 1 && num%6 != 5) return 0 ; //不在6的倍数两侧的一定不是质数
    int tmp =sqrt(num);

    for(int i=5; i<=tmp; i+=6)  //在6的倍数两侧的也可能不是质数
        if(num %i== 0||num %(i+2)==0)
            return 0 ;

    return 1 ;
}

//O(Slog(n)) Miller-Rabin
typedef unsigned long long LL;

LL modular_multi(LL x,LL y,LL mo)
{
    LL t;
    x%=mo;
    for(t=0;y;x=(x<<1)%mo,y>>=1)
        if (y&1)
            t=(t+x)%mo;
    return t;
}

LL modular_exp(LL num,LL t,LL mo)
{
    LL ret=1,temp=num%mo;
    for(;t;t>>=1,temp=modular_multi(temp,temp,mo))
        if (t&1)
            ret=modular_multi(ret,temp,mo);
    return ret;
}

bool miller_rabbin(LL n)
{
    if (n==2)return true;
    if (n<2||!(n&1))return false;
    int t=0;
    LL a,x,y,u=n-1;
    while((u&1)==0) t++,u>>=1;
    for(int i=0;i<S;i++)
    {
        a=rand()%(n-1)+1;
        x=modular_exp(a,u,n);
        for(int j=0;j<t;j++)
        {
            y=modular_multi(x,x,n);
            if (y==1&&x!=1&&x!=n-1)
                return false;
            ///其中用到定理，如果对模n存在1的非平凡平方根，则n是合数。
            ///如果一个数x满足方程x^2≡1 (mod n),但x不等于对模n来说1的两个‘平凡’平方根：1或-1，则x是对模n来说1的非平凡平方根
            x=y;
        }
        if (x!=1)///根据费马小定理,若n是素数，有a^(n-1)≡1(mod n).因此n不可能是素数
            return false;
    }
    return true;
}
