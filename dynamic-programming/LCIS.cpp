scanf("%d", &l1); for(int i=1; i<=l1; i++) scanf("%d", &a[i]);
scanf("%d", &l2); for(int i=1; i<=l2; i++) scanf("%d", &b[i]);
memset(dp, 0, sizeof(dp));

for(int i=1; i<=l1; i++) {
    ma = 0;
    for(int j=1; j<=l2; j++) {
        if(a[i]>b[j] && ma<dp[j]) ma = dp[j];
        if(a[i] == b[j]) dp[j] = ma+1;
    }
}
ma = 0;
for(int i=1; i<=l2; i++) ma = max(ma, dp[i]);
