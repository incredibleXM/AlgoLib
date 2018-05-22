//Eratosthenes sieve
int prime[MAX_N];
bool is_prime[MAX_N + 1];

int sieve(int n)
{
    int p = 0;
    for (int i=0; i<=n; i++) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false;
    for (int i=2; i<=n; i++) {
        if(is_prime[i]) {
            prime[p++] = i;
            for(int j=2*i; j<=n; j+=i) {
                is_prime[j] = false;
            }
        }
    }
    return p;
}

//Euler sieve
bool check[MAX_N];
int prime[MAX_N];

int tot = 0;
for(int i=2; i<=MAX_N; i++) {
    if(!check[i]) {
        prime[tot++] = i;
    }
    for(int j=0; j<tot; j++) {
        if(i*prime[j] > MAX_N) break;
        check[i*prime[j]] = true;
        if(i % prime[j] == 0) break;
    }
}


//prime factorization
int prime[MAX_N], fac[MAX_N];

void div(int n)
{
    cnt = 0;
    int t = (int)sqrt(1.0 * n);
    for(int i=0; prime[i]<=t; i++) {
        if(n%prime[i] == 0) {
            fac[cnt++] = prime[i];
            while(n%prime[i] == 0) n /= prime[i];
        }
    }
    if(n > 1) fac[cnt++] = n;
}
