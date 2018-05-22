// dfs
const int M = 1005;
int C, n, m;
int sg[M];
int s[M];
bool vis[M];
int getSG(int x)
{
    if(sg[x] != -1)
        return sg[x];
    memset(vis, 0, sizeof(vis));
    for(int i=0; i<m; i++) {
        if(x >= s[i])
            vis[getSG(x-s[i])] = 1;
        else break;
    }
    for(int i=0; ; i++) {
        if(!vis[i]) {
            sg[x] = i;
            break;
        }
    }
    return sg[x];
}
int main()
{
    cin >> C;
    for(int i=0; i<M; i++)
        s[i] = i+1;
    while(C--) {
        memset(sg, -1, sizeof(sg));
        cin >> n >> m;
        if(getSG(n)) puts("first");
        else puts("second");
    }
    return 0;
}

// circuit
const int M = 1005;
int C, n, m;
int sg[M];
int s[M];
bool vis[M];
void getSG()
{
     int i, j;
     memset(sg, 0, sizeof(sg));
     for(i=1; i<=n; i++)
     {
         memset(vis, 0, sizeof(vis));
         for(j=0; j<m; j++) {
             if(i >= s[j])
                 vis[sg[i-s[j]]] = 1;
             else break;
         }
         for(j=0; ; j++)
         {
             if(vis[j] == 0)
             {
                 sg[i] = j;
                 break;
             }
         }
     }
}
int main()
{
    cin >> C;
    for(int i=0; i<M; i++)
        s[i] = i+1;
    while(C--) {
        cin >> n >> m;
        getSG();
        if(sg[n]) puts("first");
        else puts("second");
    }
    return 0;
}
