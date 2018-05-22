//Fermat Theory
inline int pow(const int n, const int k) {
    long long ans = 1;
    for (long long num = n, t = k; t; num = num * num % MOD, t >>= 1) if (t & 1) ans = ans * num % MOD;
    return ans;
}

inline int inv(const int num) {
    return pow(num, MOD - 2);
}

//exgcd
void exgcd(const int a, const int b, int &g, int &x, int &y) {
    if (!b) g = a, x = 1, y = 0;
    else exgcd(b, a % b, g, y, x), y -= x * (a / b);
}

inline int inv(const int num) {
    int g, x, y;
    exgcd(num, MOD, g, x, y);
    return ((x % MOD) + MOD) % MOD;
}

//recursion
inv[1] = 1;
for (int i = 2; i <= MAXN; i++) inv[i] = ((-(MOD / i) * inv[MOD % i]) % MOD + MOD) % MOD;

//n! inverse
fac[0] = 1, fac[1] = 1;
for (int i = 2; i <= MAX_N; i++) fac[i] = fac[i-1] * i % MOD;
inv[MAX_N] = mod_pow(fac[MAX_N], MOD-2);
for (int i = MAX_N - 1; i >= 0; i--) inv[i] = inv[i+1] * (i + 1) % MOD;
