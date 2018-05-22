//O(|E|log|V|)
struct edge { int to, cost; };

int V;
vector<edge> G[MAX_V];
int d[MAX_V];
int cnt[MAX_V];  //record the times of being pushed into the queue
bool vis[MAX_V];


//bfs version
bool spfa (int s)
{
    queue<int> que;
    fill(d, d+V, INF);
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    d[s] = 0; cnt[s] = 1; vis[s] = true;
    que.push(P(0, s));

    while(!que.empty())
    {
        int u = que.front(); que.pop();
        vis[u] = false;
        for(int i=0; i<(int)G[u].size(); i++) {
            edge e = G[u][i];
            if(d[e.to] > d[u] + e.cost) {
                d[e.to] = d[u] + e.cost;
                if(!vis[e.to]) {
                    vis[e.to] = true;
                    que.push(e.to);
                    if(++cnt[e.to] > V) return true;
                }
            }
        }
    }

    return false;
}

//dfs version
bool flag = false;
void spfa(int u)
{
     int v;

     for(unsigned int i=0; i<G[u].size(); i++) {
         edge e = G[u][i];
         v = e.to;

         if(d[v] > d[u] + e.cost) {
             if(vis[v]) {            //appear once more on route
                 flag = true;
                 return ;
             } else {
                 d[v] = d[u] + e.cost;
                 vis[v] = true;
                 spfa(v);
             }
         }
     }
}
