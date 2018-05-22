void dfs(int x,int f){
    for(int i=0;i<E[x].size();i++){
        int v = E[x][i];
        if(v==f)continue;
        deep[v]=deep[x]+1;
        lca[v][0]=x;
        for(int j=1;j<maxm;j++){
            int fa = lca[v][j-1];
            if(fa==0)continue;
            lca[v][j]=lca[fa][j-1];
        }
        dfs(v,x);
    }
}
int up(int x,int d)
{
    for(int i=maxm-1;i>=0;i--)
    {
        if(d<(1<<i))continue;
        x=lca[x][i];
        d-=(1<<i);
    }
    return x;
}
int Lca(int x,int y)
{
    if(deep[x]>deep[y])swap(x,y);
    y=up(y,deep[y]-deep[x]);
    if(x==y)return x;
    for(int i=maxm-1;i>=0;i--)
    {
        if(lca[x][i]!=lca[y][i])
            x=lca[x][i],y=lca[y][i];
    }
    return lca[x][0];
}
