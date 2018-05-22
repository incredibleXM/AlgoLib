//obviously 1-indexed
#define lson l, m, rt << 1
#define rson m+1, r, rt << 1 | 1

const int MAX_N = 100005;
int sum[MAX_N << 2];

void pushUp(int rt)
{
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}

void build(int l, int r, int rt)
{
    if(l == r) {
        scanf("%d", &sum[rt]);
        return;
    }
    int m = (l+r) >> 1;
    build(lson);
    build(rson);
    pushUp(rt);
}

void update(int p, int add, int l, int r, int rt)
{
    if(l == r) {
        sum[rt] += add;
        return;
    }
    int m = (l+r) >> 1;
    if(p <= m) update(p, add, lson);
    else update(p, add, rson);
    pushUp(rt);
}

int query(int L ,int R, int l ,int r, int rt)
{
    if(L<=l && r<=R) return sum[rt];
    int m = (l+r) >> 1;
    int ret = 0;
    if(L <= m) ret += query(L, R, lson);
    if(R > m) ret += query(L, R, rson);
    return ret;
}

// [1, n] kth of value segTree
int query(int l ,int r, int rt, int x)  // interval x-th of [1, n]
{
    if(l == r) return l;
    int m = (l+r) >> 1;
    if(x > sum[rt<<1]) return query(rson, x-sum[rt<<1]);
    else return query(lson, x);
}

//interval update
LL add[MAX_N << 2];
LL sum[maxn<<2];
void PushUp(int rt) {
       sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}

void pushDown(int rt,int m)
{
    if (add[rt]) {
        add[rt<<1] += add[rt];
        add[rt<<1|1] += add[rt];
        sum[rt<<1] += add[rt] * (m - (m >> 1));
        sum[rt<<1|1] += add[rt] * (m >> 1);
        add[rt] = 0;
    }
}

void build(int l,int r,int rt) {
       add[rt] = 0;
       if (l == r) {
              scanf("%lld",&sum[rt]);
              return ;
       }
       int m = (l + r) >> 1;
       build(lson);
       build(rson);
       PushUp(rt);
}

void update(int L, int R, int c, int l, int r, int rt)
{
    if(L<=l && r<=R) {
        add[rt] += c;
        sum[rt] += c * (r-l+1);
        return;
    }
    pushDown(rt, r-l+1);
    int m = (l+r) >> 1;
    if(L <= m) update(L, R, c, lson);
    if(m < R) update(L, R, c, rson);
    pushUp(rt);
}

LL query(int L, int R, int l, int r, int rt)
{
    if(L<=l && r<=R) return sum[rt];
    pushDown(rt, r-l+1);
    int m = (l+r) >> 1;
    LL ret = 0;
    if(L <= m) ret += query(L, R, lson);
    if(m < R) ret += query(L, R, rson);
    return ret;
}

//interval merge (POJ3667)
#define lson l, mid, rt << 1
#define rson mid+1, r, rt << 1 | 1

int n, m, t, x, d;
int lsum[MAX_N << 2], rsum[MAX_N << 2], msum[MAX_N << 2];
int cover[MAX_N << 2];

void pushUp(int rt, int mid)
{
    lsum[rt] = lsum[rt << 1];
    rsum[rt] = rsum[rt << 1 | 1];
    if(lsum[rt] == mid - (mid>>1)) lsum[rt] += lsum[rt << 1 | 1];
    if(rsum[rt] == (mid >> 1)) rsum[rt] += rsum[rt << 1];
    msum[rt] = max(lsum[rt << 1 | 1] + rsum[rt << 1], max(msum[rt << 1], msum[rt << 1 | 1]));
}

void pushDown(int rt, int mid)
{
    if(cover[rt] != -1) {
        cover[rt << 1] = cover[rt << 1 | 1] = cover[rt];
        msum[rt << 1] = lsum[rt << 1] = rsum[rt << 1] = cover[rt] ? 0 : mid - (mid>>1);
        msum[rt << 1 | 1] = lsum[rt << 1 | 1] = rsum[rt << 1 | 1] = cover[rt] ? 0 : (mid>>1);
        cover[rt] = -1;
    }
}

void build(int l, int r, int rt)
{
    msum[rt] = lsum[rt] = rsum[rt] = r - l + 1;
    cover[rt] = -1;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(lson);
    build(rson);
}

void update(int L, int R, int c, int l, int r, int rt)
{
    if(L<=l && r<=R) {
        msum[rt] = lsum[rt] = rsum[rt] = c ? 0 : r-l+1;
        cover[rt] = c;
        return;
    }
    pushDown(rt, r-l+1);
    int mid = (l+r) >> 1;
    if(L <= mid) update(L, R, c, lson);
    if(mid < R) update(L, R, c, rson);
    pushUp(rt, r-l+1);
}

int query(int w, int l, int r, int rt)
{
    if(l == r) return l;
    pushDown(rt, r-l+1);
    int mid = (l+r) >> 1;
    if(msum[rt << 1] >= w) return query(w, lson);
    else if(rsum[rt << 1] + lsum[rt << 1 | 1] >= w) return mid-rsum[rt << 1]+1;
    return query(w, rson);
}


int main()
{
#ifdef ANONYM
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
#endif

    scanf("%d%d", &n, &m);
    build(1, n, 1);
    REP(i, 0, m) {
        scanf("%d", &t);
        if(t == 1) {
            scanf("%d", &d);
            if(msum[1] < d) puts("0");
            else {
                int p = query(d, 1, n, 1);
                printf("%d\n", p);
                update(p, p+d-1, 1, 1, n, 1);
            }
        } else if(t == 2) {
            scanf("%d%d", &x, &d);
            update(x, x+d-1, 0, 1, n, 1);
        }
    }
    return 0;
}
