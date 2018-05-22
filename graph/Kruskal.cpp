//O(|E|log|V|)
//implement of union-find set can be seen in Union-Find.cpp
struct edge
{
    int u, v, cost;
    bool operator < (const edge& e) const {
        return cost < e.cost;
    }
};

edge es[MAX_E];
int V, E;

int Kruskal()
{
    sort(es, es+E);
    init_union_find(V);  //union-find set is used to judge the connected component
    int res = 0;
    for(int i=0; i<E; i++) {
        edge e = es[i];
        if(!same(e.u, e.v)) {
            unite(e.u, e.v);
            res += e.cost;
        }
    }
    return res;
}

/*
example:
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX_V = 1005;
const int MAX_E = 50005;
int fa[MAX_V];   //father node
int _rank[MAX_V]; //height of tree
struct edge
{
    int u, v, cost;
    bool operator < (const edge& e) const {
        return cost < e.cost;
    }
};

edge es[MAX_E];
int V, E;
int s, e, w;

void init(int n)
{
    for(int i=0; i<n; i++) {
        fa[i] = i;
        _rank[i] = 0;
    }
}

int find(int x) //another implementation
{
    if(fa[x] != x) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}


void unite(int x, int y)  //avoid worst situation(degenerate tree)
{
    int fx = find(x);
    int fy = find(y);
    if(fx == fy) return;
    if(_rank[fx] < _rank[fy]) {
        fa[fx] = fy;
    } else {
        fa[fy] = fx;
        if(_rank[fx] == _rank[fy]) _rank[fx]++;
    }
}


bool same(int a, int b)
{
    return find(a) == find(b);
}

int Kruskal()
{
    sort(es, es+E);
    init(V);  //union-find set is used to judge the connected component
    int res = 0;
    for(int i=0; i<E; i++) {
        edge e = es[i];
        if(!same(e.u, e.v)) {
            unite(e.u, e.v);
            res += e.cost;
        }
    }
    return res;
}


int main()
{
    cin >> V >> E;
    for(int i=0; i<E; i++) {
        cin >> s >> e >> w;
        es[i].u = s;
        es[i].v = e;
        es[i].cost = w;
    }
    cout << Kruskal() << endl;
}
