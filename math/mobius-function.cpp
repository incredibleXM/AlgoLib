bool check[MAX_N];
int mu[MAX_N];
int prime[MAX_N];

mu[1] = 1;
int tot = 0;
for(int i=2; i<=N; i++) {
    if(!check[i]) {
        prime[tot++] = i;
        mu[i] = -1;
    }
    for(int j=0; j<tot; j++) {
        if(i*prime[j] > N) break;
        check[i*prime[j]] = true;
        if(i % prime[j] == 0) {
            mu[i * prime[j]] = 0;
            break;
        } else {
            mu[i * prime[j]] = -mu[i];
        }
    }
}
