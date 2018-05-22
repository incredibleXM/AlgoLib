int n;
LL m[MAX_N], r[MAX_N];

LL solve()
{
    LL M = m[1], R = r[1];
    for(int i=2; i<=n; i++) {
        LL d = __gcd(M, m[i]);
        LL c = r[i] - R;
        if(c % d) {
            return -1;
        }
        LL k1, k2;
        extgcd(M / d, m[i] /d, k1, k2);
        k1 = (c / d * k1) % (m[i] / d);
        R = R + k1 * M;
        M = M / d * m[i];
        R %= M;
    }
    if(R < 0) R += M;
    return R;
}
