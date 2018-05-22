#include <bits/stdc++.h>
using namespace std;
const int MAX_V = 1005;
const int MAX_E = 50005;
int fa[MAX_V];   //father node
int _rank[MAX_V]; //height of tree
struct edge {
    int u, v, w;
};

edge es[MAX_E];
int V, E;
int s, e, w;

int cheap[MAX_V];

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

int Boruvka()
{
    init(V);
    int res = 0, num = V;
    while(num > 1) {
        memset(cheap, -1, sizeof(cheap));
        for(int i=0; i<E; i++) {
            int s1 = find(es[i].u);
            int s2 = find(es[i].v);
            if(s1 == s2) continue;
            if(cheap[s1]==-1 || es[cheap[s1]].w > es[i].w) cheap[s1] = i;
            if(cheap[s2]==-1 || es[cheap[s2]].w > es[i].w) cheap[s2] = i;
        }
        for(int i=0; i<V; i++) {
            if(cheap[i] != -1) {
                int s1 = find(es[cheap[i]].u);
                int s2 = find(es[cheap[i]].v);
                if(s1 == s2) continue;
                res += es[cheap[i]].w;
                unite(s1, s2);
                num--;
            }
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
        es[i].w = w;
    }
    cout << Boruvka() << endl;
}
