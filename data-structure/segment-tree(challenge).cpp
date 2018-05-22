const int INF = 0x3f3f3f3f;

const int MAX_N = 1 << 17;
int n, dat[2*MAX_N-1];

void init(int n_)
{
    n = 1;
    while(n < n_) n *= 2;
    for(int i=0; i<2*n-1; i++) dat[i] = INF;
}

int build(int i)
{
    if(i >= n-1) return dat[i];
    return dat[i] = min(build(2*i+1), build(2*i+2));
}

void update(int k, int a) //kth(0-indexed) -> a
{
    k += n-1;
    dat[k] = a;

    while(k > 0) {
        k = (k-1)/2;
        dat[k] = min(dat[2*k+1], dat[2*k+2]);
    }
}

//min of [a,b) usage: query(a, b, 0, 0, n)
int query(int a, int b, int k, int l, int r)
{
    if(r<=a || b<=l) return INF;
    if(a<=l && r<=b) return dat[k];
    else {
        int vl = query(a, b, 2*k+1, l, (l+r)/2);
        int vr = query(a, b, 2*k+2, (l+r)/2, r);
        return min(vl, vr);
    }
}

//interval update: add x to interval [a,b)
ll data[DAT_SIZE], datb[DAT_SIZE];

void add(int a, int b, int x, int k, int l, int r)
{
    if(a <= l && r <= b) data[k] += x;
    else if(l<b && a<r) {
        datb[k] += (min(b, r) - max(a, l)) * x;
        add(a ,b, x, k*2+1, l, (l+r)/2);
        add(a, b, x, k*2+2, (l+r)/2, r);
    }
}

ll sum(int a, int b, int k, int l, int r)
{
    if(b<=l || r<=a) return 0;
    else if(a<=l && r<=b) return data[k]*(r-l)+datb[k];
    else {
        ll res = (min(b, r) - max(a, l)) * data[k];
        res += sum(a, b, k*2+1, l, (l+r)/2);
        res += sum(a, b, k*2+2, (l+r)/2, r);
        return res;
    }
}
