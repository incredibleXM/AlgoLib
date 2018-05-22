/* BKDR Hash Function */
unsigned int BKDR_hash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7FFFFFFF);
}

//字符串hash
typedef unsigned long long ull;
const int N = 100000 + 5;
const ull base = 163;
char s[N];
ull hash[N], p[N];

void init(){//处理hash值
    p[0] = 1;
    hash[0] = 0;
    int n = strlen(s + 1);
    for(int i = 1; i <=100000; i ++) p[i] = p[i-1] * base;
    for(int i = 1; i <= n; i ++) hash[i] = hash[i - 1] * base + (s[i] - 'a');
}

ull get(int l, int r, ull g[]){//取出g里l - r里面的字符串的hash值
    return g[r] - g[l - 1] * p[r - l + 1];
}

//another version
const ull B = 100000007;

// is string a in string b?
bool contain(char *a, char *b)
{
    int al = strlen(a), bl = strlen(b);
    if(al > bl) return false;

    ull t = 1;
    for(int i=0; i<al; i++) t *= B;

    ull ah = 0, bh = 0;
    for(int i=0; i<al; i++) ah = ah*B + a[i];
    for(int i=0; i<al; i++) bh = bh*B + b[i];

    for(int i=0; i+al<=bl; i++) {
        if(ah == bh) return true;
        if(i + al < bh) bh = bh*B + b[i+al] - b[i]*t;
    }
}

//max length suffix of a = prefix of b
int overlap(char *a, char *b)
{
    int al = strlen(a), bl = strlen(b);
    int ans = 0;
    ull ah = 0, bh = 0, t = 1;
    for(int i=1; i<=min(al, bl); i++) {
        ah += a[al-i] * t;
        bh = bh*B + b[i-1];
        if(ah == bh) ans = i;
        t *= B;
    }
    return ans;
}
