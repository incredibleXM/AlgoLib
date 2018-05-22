int euler(int n)
{
    int ret = 1;
    for(int i=2; i*i<=n; i++){
        if(n%i == 0){
            n /= i, ret *= i-1;
            while(n%i == 0){
                n /= i, ret *= i;
            }
        }
    }
    if(n > 1) ret *= n-1;
    return ret;
}


//linear method
bool check[MAX_N];
int phi[MAX_N];
int prime[MAX_N];

phi[1] = 1;
int tot = 0;
for(int i=2; i<=N; i++) {
    if(!check[i]) {
        prime[tot++] = i;
        phi[i] = i - 1;
    }
    for(int j=0; j<tot; j++) {
        if(i*prime[j] > N) break;
        check[i*prime[j]] = true;
        if(i % prime[j] == 0) {
            phi[i*prime[j]] = phi[i] * prime[j];
            break;
        } else {
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}
