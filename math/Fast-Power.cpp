typedef long long LL;

LL mul(LL a, LL b, LL p) // method 1 O(logb)
{
    LL ans = 0;
    for(; b; b >>= 1) {
        if(b & 1) ans = (ans + a) % p;
        a = a * 2 % p;
    }
    return ans;
}

LL mul(LL a, LL b, LL p) // method 2 O(1)
{
    a %= p, b %= p; // omitted when a, b in (0, p)
    LL c = (long double)a * b / p;
    LL ans = a * b - c * p;
    if(ans < 0) ans += p;
    else if(ans >= p) ans -= p;
    return ans;
}

LL power(LL a, LL b, LL p)
{
    LL ans = 0;
    for(; b; b >>= 1) {
        if(b & 1) ans = ans * a % p; // if ans * a > MAX_LONGLONG use mul
        a = a * a % p; // same as before
    }
    return ans;
}


typedef vector<int> vec;
typedef vector<vec> mat;

mat mul(mat &A, mat &B)
{
    mat C(A.size(), vec(B[0].size()));
    for(int i=0; i<A.size(); i++) {
        for(int k=0; k<B.size(); k++) {
            for(int j=0; j<B[0].size(); j++) {
                C[i][j] = (C[i][j]+A[i][k]*B[k][j]) % mod;
            }
        }
    }
    return C;
}

mat pow(mat A, LL n)
{
    mat B(A.size(), vec(A.size()));
    for(int i=0; i<A.size(); i++) {
        B[i][i] = 1;
    }

    while(n > 0) {
        if(n&1) B = mul(B, A);
        A = mul(A, A);
        n >>= 1;
    }

    return B;
}
