inline long long pow(const long long x, const long long n, const long long p) {
    long long ans = 1;
    for (long long num = x, tmp = n; tmp; tmp >>= 1, num = num * num % p) if (tmp & 1) ans = ans * num % p;
    return ans;
}

inline long long root(const long long p) {
    for (int i = 2; i <= p; i++) {
        int x = p - 1;
        bool flag = false;
        for (int k = 2; k * k <= p - 1; k++) if (x % k == 0) {
            if (pow(i, (p - 1) / k, p) == 1) {
                flag = true;
                break;
            }
            while (x % k == 0) x /= k;
        }

        if (!flag && (x == 1 || pow(i, (p - 1) / x, p) != 1)) {
            return i;
        }
    }
    throw;
}

inline void exgcd(const long long a, const long long b, long long &g, long long &x, long long &y) {
    if (!b) g = a, x = 1, y = 0;
    else exgcd(b, a % b, g, y, x), y -= x * (a / b);
}

inline long long inv(const long long a, const long long p) {
    long long g, x, y;
    exgcd(a, p, g, x, y);
    return (x + p) % p;
}

struct NumberTheoreticTransform {
    long long omega[MAXM_EXTENDED], omegaInverse[MAXM_EXTENDED];

    void init(const int n) {
        long long g = root(MOD), x = pow(g, (MOD - 1) / n, MOD);
        for (int i = 0; i < n; i++) {
            assert(i < MAXM_EXTENDED);
            omega[i] = (i == 0) ? 1 : omega[i - 1] * x % MOD;
            omegaInverse[i] = inv(omega[i], MOD);
        }
    }

    void transform(long long *a, const int n, const long long *omega) {
        int k = 0;
        while ((1 << k) != n) k++;
        for (int i = 0; i < n; i++) {
            int t = 0;
            for (int j = 0; j < k; j++) if (i & (1 << j)) t |= (1 << (k - j - 1));
            if (t > i) std::swap(a[i], a[t]);
        }
        for (int l = 2; l <= n; l *= 2) {
            int m = l / 2;
            for (long long *p = a; p != a + n; p += l) {
                for (int i = 0; i < m; i++) {
                    long long t = omega[n / l * i] * p[i + m] % MOD;
                    p[i + m] = (p[i] - t + MOD) % MOD;
                    (p[i] += t) %= MOD;
                }
            }
        }
    }

    void dft(long long *a, const int n) {
        transform(a, n, omega);
    }

    void idft(long long *a, const int n) {
        transform(a, n, omegaInverse);
        long long x = inv(n, MOD);
        for (int i = 0; i < n; i++) a[i] = a[i] * x % MOD;
    }
} ntt;


//Acdreamer
const int N = 1 << 18;
const int P = (479 << 21) + 1;
const int G = 3;
const int NUM = 20;

LL  wn[NUM];
LL  a[N], b[N];
char A[N], B[N];

LL quick_mod(LL a, LL b, LL m)
{
    LL ans = 1;
    a %= m;
    while(b)
    {
        if(b & 1)
        {
            ans = ans * a % m;
            b--;
        }
        b >>= 1;
        a = a * a % m;
    }
    return ans;
}

void GetWn()
{
    for(int i = 0; i < NUM; i++)
    {
        int t = 1 << i;
        wn[i] = quick_mod(G, (P - 1) / t, P);
    }
}

void Prepare(char A[], char B[], LL a[], LL b[], int &len)
{
    len = 1;
    int L1 = strlen(A);
    int L2 = strlen(B);
    while(len <= 2 * L1 || len <= 2 * L2) len <<= 1;
    for(int i = 0; i < len; i++)
    {
        if(i < L1) a[i] = A[L1 - i - 1] - '0';
        else a[i] = 0;
        if(i < L2) b[i] = B[L2 - i - 1] - '0';
        else b[i] = 0;
    }
}

void Rader(LL a[], int len)
{
    int j = len >> 1;
    for(int i = 1; i < len - 1; i++)
    {
        if(i < j) swap(a[i], a[j]);
        int k = len >> 1;
        while(j >= k)
        {
            j -= k;
            k >>= 1;
        }
        if(j < k) j += k;
    }
}

void NTT(LL a[], int len, int on)
{
    Rader(a, len);
    int id = 0;
    for(int h = 2; h <= len; h <<= 1)
    {
        id++;
        for(int j = 0; j < len; j += h)
        {
            LL w = 1;
            for(int k = j; k < j + h / 2; k++)
            {
                LL u = a[k] % P;
                LL t = w * a[k + h / 2] % P;
                a[k] = (u + t) % P;
                a[k + h / 2] = (u - t + P) % P;
                w = w * wn[id] % P;
            }
        }
    }
    if(on == -1)
    {
        for(int i = 1; i < len / 2; i++)
            swap(a[i], a[len - i]);
        LL inv = quick_mod(len, P - 2, P);
        for(int i = 0; i < len; i++)
            a[i] = a[i] * inv % P;
    }
}

void Conv(LL a[], LL b[], int n)
{
    NTT(a, n, 1);
    NTT(b, n, 1);
    for(int i = 0; i < n; i++)
        a[i] = a[i] * b[i] % P;
    NTT(a, n, -1);
}

void Transfer(LL a[], int n)
{
    int t = 0;
    for(int i = 0; i < n; i++)
    {
        a[i] += t;
        if(a[i] > 9)
        {
            t = a[i] / 10;
            a[i] %= 10;
        }
        else t = 0;
    }
}

void Print(LL a[], int n)
{
    bool flag = 1;
    for(int i = n - 1; i >= 0; i--)
    {
        if(a[i] != 0 && flag)
        {
            //使用putchar()速度快很多
            putchar(a[i] + '0');
            flag = 0;
        }
        else if(!flag)
            putchar(a[i] + '0');
    }
    puts("");
}

int main()
{
    GetWn();
    while(scanf("%s %s", A, B) != EOF)
    {
        int len;
        Prepare(A, B, a, b, len);
        Conv(a, b, len);
        Transfer(a, len);
        Print(a, len);
    }
    return 0;
}  
