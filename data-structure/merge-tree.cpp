const int MAX_N = 1e5 + 5;

const int ST_SIZE = (1 << 18) - 1;

int n, m;
int a[MAX_N], nums[MAX_N];
int l, r, k;

vector<int> dat[ST_SIZE];

void init(int k, int l, int r)
{
    if(r - l== 1) {
        dat[k].push_back(a[l]);
    } else {
        int lch = (k<<1) + 1, rch = (k<<1) + 2;
        init(lch, l, (l+r)>>1);
        init(rch, (l+r)>>1, r);

        dat[k].resize(r-l);
        merge(dat[lch].begin(), dat[lch].end(), dat[rch].begin(), dat[rch].end(), dat[k].begin());
    }
}


//calculate the number of <=x in [l, r)
int query(int i, int j, int x, int k, int l, int r)
{
    if(j<=l || r<=i) return 0;
    else if(i<=l && r<=j) return upper_bound(dat[k].begin(), dat[k].end(), x) - dat[k].begin();
    else {
        int lc = query(i, j, x, (k<<1)+1, l, (l+r)>>1);
        int rc = query(i, j, x, (k<<1)+2, (l+r)>>1, r);
        return lc + rc;
    }
}

int main()
{
    while(~scanf("%d%d", &n, &m)) {
        for(int i=0; i<n; i++) scanf("%d", &a[i]), nums[i] = a[i];
        sort(nums, nums+n);
        init(0, 0, n);

        while(m--) {
            scanf("%d%d%d", &l, &r, &k); l--;
            int lb = -1, ub = n-1;
            while(ub - lb > 1) {
                int md = (ub + lb) >> 1;
                int c = query(l, r, nums[md], 0, 0, n);
                if(c >= k) ub = md;
                else lb = md;
            }
            printf("%d\n", nums[ub]);
        }
    }
    return 0;
}
