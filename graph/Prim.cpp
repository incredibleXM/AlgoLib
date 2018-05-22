//O(|E|log|V|)
struct edge { int to, cost; edge(int a, int b){to=a; cost=b;} };
typedef pair<int, int> P; //first: minimum weight; second: number of vertex
vector<edge> G[MAX_V];
bool vis[MAX_V];

int prim()
{
    priority_queue<P, vector<P>, greater<P> > que;
    memset(vis, 0, sizeof(vis));
    int res = 0;
    que.push(P(0, 0));

    while(!que.empty()) {
        P p = que.top(); que.pop();
        int v = p.second;
        if(vis[v]) continue;
        vis[v] = true;
        res += p.first;
        for(int i=0; i<G[v].size(); i++) {
            edge e = G[v][i];
            que.push(P(e.cost, e.to));
        }
    }
    return res;
}
