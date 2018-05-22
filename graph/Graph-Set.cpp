int V, E;

//vector
struct edge
{
    int to;
    int cost;
    edge(int _v=0, int _cost=0): v(_v), cost(_cost) {}
};
vector<edge> G[MAX_V];

for(unsigned int i=0; i<G[v].size(); i++) {
    edge e = G[v][i];
    //operations
}


//Forward Star
struct Edge
{
    int to;
    int w;
    int next;
}edge[MAX_E];

int head[MAX_V];
int cnt = 0;

void addedge(int u, int v, int w)
{
    edge[cnt].w = w;
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

for(int i=head[u]; ~i; i=edge[i].next) {
    //operations
}
