// 已知f[n]=(求和d|n)g(d),求g nlogn
for (int i = 1; i <= n; ++i)
  for (int j = i + i; j <= n; j += i)
    f[j] -= f[i];

// f[n]=(求和d|n)g(d),已知g,求f
for (int i = n; i >= 1; --i)
  for (int j = i + i; j <= n; j += i)
    f[j] += f[i];

// 已知f[n]=(求和n|d)g(d),求g nlogn
for (int i = n; i >= 1; --i)
  for (int j = i + i; j <= n; j += i)
    f[i] -= f[j];

// f[n]=(求和n|d)g(d),已知g,求f
for (int i = 1; i <= n; ++i)
  for (int j = i + i; j <= n; j += i)
    f[i] += f[j];

// f[s]存原来的元素，之后f[s]存子集所有元素和
for (int i = 0; i < n; i++)
    for (int s = 0; s < (1 << n); s++)
        if (s >> i & 1)
            f[s] += f[s ^ 1 << i];


// f[s]存子集所有元素和，之后f[s]存原来的元素
for (int i = 0; i < n; i++)
    for (int s = 0; s < (1 << n); s++)
        if (s >> i & 1)
            f[s] -= f[s ^ 1 << i];

// 数论卷积nlogn   算1-n的h[x]=(求和d|x)(f[d]*g[x/d])  已知f,g的1-n
int f[MAXN],g[MAXN],h[MAXN]={0};
void calc(int n)
{
    for(int i=1; i*i<=n; i++)
        for(int j=i; i*j<=n; j++)
            if(j==i) h[i*j] += f[i]*g[i];
            else h[i*j] += f[i]*g[j] + f[j]*g[i];
}
