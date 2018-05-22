const int MAX_N = 100005;
const int MAX_LOG = 17; // Math.log2(100000) = 16.609640474436812

int n, a[MAX_N], st[MAX_N][MAX_LOG + 1], logx[MAX_N];

inline void sparseTable()
{
    for (int i = 1; i <= n; i++) {
        int t = 0;
        while ((1 << (t + 1)) <= i) t++;
        logx[i] = t;
    }

    for (int i = 1; i <= n; i++) st[i][0] = a[i]; // 初始值，以每个位置开始 2 ^ 0 = 1 长度的区间，即自身

    for (int j = 1; j <= logx[n]; j++) {
        for (int i = 1; i <= n; i++) {
            // 判断当前要计算的区间是否越界
            if (i + (1 << (j - 1)) <= n)
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            else st[i][j] = st[i][j - 1];
        }
    }
}

inline int rmq(int l, int r)
{
    int t = logx[r - l];
    return max(st[l][t], st[r - (1 << t) + 1][t]); // 左右两个区间，恰好覆盖
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    sparseTable();

    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", rmq(l, r));
    }

    return 0;
}
