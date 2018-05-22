//O(|V|*|E|)
struct edge { int from, to, cost; };

edge es[MAX_E];
int d[MAX_V];
int V, E;

void shortest_path(int s)
{
    fill(d, d+V, INF);
    d[s] = 0;
    while (true) {
        bool update = false;
        for(int i=0; i<E; i++) {
            edge e = es[i];
            if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                d[e.to] = d[e.from] + e.cost;
                update = true;
            }
        }
        if(!update) break;
    }
}

bool find_negative_path()
{
    memset(d, 0, sizeof(d));

    for(int i=0; i<V; i++) {
        for(int j=0; j<E; j++) {
            edge e =es[j];
            if(d[e.to] > d[e.from] + e.cost) {
                d[e.to] = d[e.from] + e.cost;

                if(i == V-1) return true;
            }
        }
    }
    return false;
}
