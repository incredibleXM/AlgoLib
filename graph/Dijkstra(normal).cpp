//O(|V|^2)
int cost[MAX_V][MAX_V];  //weight of (u, v), when non-existent it will be set as INF
int d[MAX_V];
bool vis[MAX_V];
int V;

void dijkstra(int s)
{
    fill(d, d+V, INF);
    memset(vis, 0, sizeof(vis));
    d[s] = 0;

    while(true)
    {
        int v = -1;
        //choose a vertex with shortest distance
        for(int u=0; u<V; u++) {
            if(!vis[u] && (v == -1 || d[u] < d[v])) v = u;
        }

        if(v == -1) break;

        vis[v] = true;
        for(int u=0; u<V; u++) {
            d[u] = min(d[u], d[v] + cost[u][v]);
        }
    }
}
