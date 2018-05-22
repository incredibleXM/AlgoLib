//O(sqrt(V)E)
const int N=1005;
const int INF=1<<28;

int g[N][N];
int Mx[N];
int My[N];
int dx[N];
int dy[N];
bool used[N];
int Nx,Ny,dis;

bool searchP()
{
    dis=INF;
    int i,v,u;
    std::queue<int> Q;

    memset(dx,-1,sizeof(dx));
    memset(dy,-1,sizeof(dy));
    for(i=0;i<Nx;i++) {
        if(Mx[i]==-1) {
            Q.push(i);
            dx[i]=0;
        }
    }
    while(!Q.empty()) {
        u=Q.front();
        Q.pop();
        if(dx[u]>dis) break;
        for(v=0;v<Ny;v++) {
            if(g[u][v]&&dy[v]==-1) {
                dy[v]=dx[u]+1;
                if(My[v]==-1) dis=dy[v];
                else {
                    dx[My[v]]=dy[v]+1;
                    Q.push(My[v]);
                }
            }
        }
    }
    return dis!=INF;
}

bool DFS(int u)
{
    for(int v=0; v<Ny; v++) {
        if(g[u][v]&&!used[v]&&dy[v]==dx[u]+1) {
            used[v]=true;
            if(My[v]!=-1&&dy[v]==dis) continue;
            if(My[v]==-1||DFS(My[v])) {
                My[v]=u;
                Mx[u]=v;
                return true;
            }
        }
    }
    return false;
}

int MaxMatch()
{
    int res=0;
    memset(Mx,-1,sizeof(Mx));
    memset(My,-1,sizeof(My));
    while(searchP()) {
        memset(used,false,sizeof(used));
        for(int u=0; u<Nx; u++)
           if(Mx[u]==-1&&DFS(u))  res++;
    }
    return res;
}
