int n, V;
int c[MAX_N], w[MAX_N], m[MAX_N];
int dp[MAX_V];

scanf("%d%d", &n, &V);
for(int i=1; i<=n; i++) scanf("%d%d%d", &c[i], &w[i], &m[i]);
for(int i=1; i<=n; i++) {
    if(c[i]*m[i] >= V) {    //complete pack
        for(int v=c[i]; v<=V; v++)
            dp[v] = max(dp[v], dp[v-c[i]] + w[i]);
            continue;
    }

    int k = 1;
    while(k < m[i]) {
        for(int v=V; v>=k*c[i]; v--)   //01-pack
            dp[v] = max(dp[v], dp[v-k*c[i]]+k*w[i]);
        m[i] = m[i] - k;
        k *= 2;
    }
    for(int v=V; v>=m[i]*c[i]; v--)    //01-pack
        dp[v] = max(dp[v], dp[v-c[i]*m[i]]+m[i]*w[i]);
}

printf("%d\n", dp[V]);
