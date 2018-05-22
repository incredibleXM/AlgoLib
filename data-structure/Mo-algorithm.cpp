int a[maxn],pos[maxn],c[maxn],Ans[maxn];
int ans,n,m;
struct query
{
    int l,r,id;
}Q[maxn];
bool cmp(query a,query b)
{
    if(pos[a.l]==pos[b.l])
        return a.r<b.r;
    return pos[a.l]<pos[b.l];
}
void Update(int x)
{
    c[x]++;
    if(c[x]==2)ans++;
}
void Delete(int x)
{
    c[x]--;
    if(c[x]==1)ans--;
}
int main()
{
    n=read(),m=read(),m=read();
    int sz =ceil(sqrt(1.0*n));
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
        pos[i]=(i-1)/sz;
    }
    for(int i=1;i<=m;i++)
    {
        Q[i].l=read();
        Q[i].r=read();
        Q[i].id = i;
    }
    sort(Q+1,Q+1+m,cmp);
    int L=1,R=0;ans=0;
    for(int i=1;i<=m;i++)
    {
        int id = Q[i].id;
        while(R<Q[i].r)R++,Update(a[R]);
        while(L>Q[i].l)L--,Update(a[L]);
        while(R>Q[i].r)Delete(a[R]),R--;
        while(L<Q[i].l)Delete(a[L]),L++;
        Ans[id]=ans;
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",Ans[i]);
}
