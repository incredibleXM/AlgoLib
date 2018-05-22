int  bit[MAX_N+1], n;

int sum(int i)
{
    int s = 0;
    while(i > 0) {
        s += bit[i];
        i -= i&-i;
    }
    return s;
}

int add(int i, int x)
{
    while(i <= n) {
        bit[i] += x;
        i += i&-i;
    }
}

// the number of inversions
LL solve()
{
    LL ans = 0;
    for(int j=0; j<n; j++) {
        ans += (j-sum(a[j]));
        add(a[j], 1);
    }
    return ans;
}

//interval update
LL bit0[MAX_N+1], bit1[MAX_N+1];

LL sum(LL *b, int i)
{
    int s = 0;
    while(i > 0) {
        s += b[i];
        i -= i&-i;
    }
    return s;
}

void add(LL *b, int i, int v)
{
    while(i <= n) {
        bit[i] += v;
        i += i&-i;
    }
}

/*[l,r] + x*/
add(bit0, l, -x*(l-1));
add(bit1, l ,x);
add(bit0, r+1, x*r);
add(bit1, r+1, -x);

/*query the sum of [l,r]*/
LL res = 0;
res += sum(bit0, r) + sum(bit1, r) * r;
res -= sum(bit0, l-1) + sum(bit1, l-1)*(l-1);
