//O(n^3)
int a[105];
int dp[105][105];
int sum[105];
const int M = 100000000;
int main()
{
    int T, n;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        sum[0] = 0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d", a+i);
            sum[i] = sum[i-1] + a[i];

        }
        for(int l=2;l<=n;l++)
            for(int i=1;i<=n-l+1;i++)
            {
                int j = i+l-1;
                dp[i][j] = M;
                for(int k=i;k<j;k++)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + sum[j]- sum[i-1]);
            }
        printf("%d\n", dp[1][n]);
    }
    return 0;
}

//O(n^2)
int a[105];
int dp[105][105];
int s[105][105];
int sum[105];
const int M = 100000000;
int main()
{
    int T, n;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        sum[0] = 0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d", a+i);
            sum[i] = sum[i-1] + a[i];
            dp[i][i] = 0;
            s[i][i] = i;
        }
        for(int l=2;l<=n;l++)
            for(int i=1;i<=n-l+1;i++)
            {
                int j = i+l-1;
                dp[i][j] = M;
                for(int k=s[i][j-1];k<=s[i+1][j];k++)
                    if(dp[i][j] > dp[i][k] + dp[k+1][j] + sum[j]- sum[i-1])
                    {
                        dp[i][j] = dp[i][k] + dp[k+1][j] + sum[j]- sum[i-1];
                        s[i][j] = k;
                    }
            }
        printf("%d\n", dp[1][n]);
    }
    return 0;
}

//O(nlogn)
int a[105];
const int M = 100000000;
int main()
{
    int T, n;
    int ans, temp;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i=1;i<=n;i++)
            scanf("%d", a+i);
        a[0] = a[n+1] = M;
        ans = 0;
        while(n >= 2)
        {
            int i, j;
            for(i = 2; i <= n; i++)
                if(a[i-1] < a[i+1])
                    break;
            temp = a[i-1] + a[i];
            ans += temp;
            for(j = i-1; j && temp > a[j-1]; j--)
                a[j] = a[j-1];
            a[j] = temp;
            for(j = i; j <= n; j++)
                a[j] = a[j+1];
            n--;
        }
        printf("%d\n",ans);
    }
    return 0;
}
