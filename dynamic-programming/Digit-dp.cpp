//count the zero from m to n
LL m, n;
LL dp[20][20];
int num[20];

LL dfs(int len, bool lead, int sta, bool limit)
{
    if(len == 0) {
        if(lead) return 1LL;
        else return sta;
    }
    if(!limit && dp[len][sta]!=-1 && !lead) return dp[len][sta];
    LL cnt = 0; int mx = (limit ? num[len] : 9);
    REP(i, 0, mx+1) {
        if(lead) {
            cnt += dfs(len-1, lead && i==0, 0, limit && i==mx);
        } else {
            if(i == 0) cnt += dfs(len-1, false, sta+1, limit && i==mx);
            else cnt += dfs(len-1, false, sta, limit && i==mx);
        }
    }
    return (limit || lead) ? cnt : dp[len][sta]=cnt;
}

LL solve(LL x)
{
    int k = 0;
    if(x == 0) k = 1;
    while(x) {
        num[++k] = x % 10;
        x /= 10;
    }
    return dfs(k, true, 0, true);
}

//usage
solve(n) - solve(m-1)
