//O(|E|log|V|)
struct edge { int to, cost; edge(int a, int b){to=a; cost=b;} };
typedef pair<int, int> P; //first: shortest distance; second: number of vertex

int V;
vector<edge> G[MAX_V];
int d[MAX_V];
int prev[MAX_V];

void dijkstra (int s) // implement with priority_queue
{
    priority_queue<P, vector<P>, greater<P> > que;
    fill(d, d+V, INF);
    memset(prev, -1, sizeof(prev));
    d[s] = 0;
    que.push(P(0, s));

    while(!que.empty())
    {
        P p = que.top(); que.pop();
        int v = p.second;
        if(d[v] < p.first) continue;
        for(int i=0; i<(int)G[v].size(); i++) {
            edge &e = G[v][i];
            if(d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                prev[e.to] = v; //record the prev node
                que.push(P(d[e.to], e.to));
            }
            //if any other factor need to be considered, just
            //else if(d[e.to] == d[v] + e.cost) {update operation}
        }
    }
}

vector<int> get_path(int t)
{
    vector<int> path;
    for(; t != -1; t = prev[t]) path.push_back(t);
    reverse(path.begin(), path.end());
    return path;
}

//secondary shortest path
int dist[MAX_V], dist2[MAX_V];
void solve(int s)
{
    priority_queue<P, vector<P>, greater<P> >q;
    fill(dist, dist + V, INF);
    fill(dist2, dist2 + V, INF);
    dist[s] = 0;
    q.push(P(0, s));
    while (!q.empty()) {
        P u = q.top(); q.pop();
        int v = u.second, d = u.first;
        if (dist2[v] < d)continue; //取出的不是次短距离，抛弃
        for (int i = 0; i < G[v].size(); i++) {
            edge &e = G[v][i];
            int d2 = d + e.cost;
            if (dist[e.to]>d2) {  //更新最短距离
                swap(dist[e.to], d2);
                q.push(P(dist[e.to], e.to));
            }
            if (dist2[e.to]>d2 && dist[e.to]<d2) {  //更新次短距离
                dist2[e.to] = d2;
                q.push(P(dist2[e.to], e.to));
            }
        }
    }
}
