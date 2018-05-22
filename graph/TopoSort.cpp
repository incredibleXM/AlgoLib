//bfs
bool TopoSort()
{
    int cnt = 0;
    queue<int> ts;
    for(int i=1; i<=n; i++) if(!deg[i]) ts.push(i);
    while(!ts.empty()) {
        int u = ts.front(); ts.pop();
        cnt++;
        for(int i=0; i<G[u].size(); i++) {
            int v = G[u][i];
            if(--deg[v] == 0) ts.push(v);
        }
    }
    if(cnt == n) return true;
    else return false;
}
