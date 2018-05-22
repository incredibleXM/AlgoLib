int sz[MAX_N], cnt[MAX_N], col[MAX_N];

void getsz(int v, int p)
{
    sz[v] = 1;
    for(auto u: g[v]) {
        if(u != p) {
            getsz(u, v);
            sz[v] += sz[u];
        }
    }
}
// O(n ^ 2)
void add(int v, int p, int x)
{
    cnt[col[v]] += x;
    for(auto u: g[v]) {
        if(u != p) {
            add(u, v, x);
        }
    }
}

void dfs(int v, int p)
{
    add(v, p, 1);
    // query operation
    add(v, p, -1);
    for(auto u: g[v]) {
        if(u != p) {
            dfs(u, v);
        }
    }
}

// O(n log^2 n)
map<int, int> *cnt[MAX_N];
void dfs(int v, int p)
{
    int mx = -1, bigChild = -1;
    for(auto u: g[v]) {
        if(u != p) {
            
        }
    }
}
