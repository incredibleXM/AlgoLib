typedef long long LL;

LL to_gray(LL x)
{
    return x ^= (x >> 1);
}

LL to_bin(LL x)
{
    LL y = x;
    while(x >>= 1) {
        y ^= x;
    }
    return y;
}

//construct gray code (lenth: n)
std::vector<int> G;
for(int i=0; i<(1<<n); i++) {
    G.push_back(to_gray(i));
}
