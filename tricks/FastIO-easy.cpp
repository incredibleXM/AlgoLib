inline LL read()
{
    int x = 0, f = 1; char ch = getchar();
    while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch = getchar(); }
    while(ch>='0' && ch<='9') { x = x*10+ch-'0'; ch = getchar(); }
    return x * f;
}

template <typename T> inline void Read(T &x) {
    char c = getchar();
    bool f = false;
    for (x = 0; !isdigit(c); c = getchar()) {
        if (c == '-') {
            f = true;
        }
    }
    for (; isdigit(c); c = getchar()) {
        x = x * 10 + c - '0';
    }
    if (f) {
        x = -x;
    }
}

namespace FastIO {
    #define BUF_SIZE 100000
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE], *p1=buf+BUF_SIZE, *pend=buf+BUF_SIZE;
        if(p1 == pend){
            p1 = buf; pend = buf+fread(buf,1,BUF_SIZE,stdin);
            if(pend == p1){ IOerror=1;return -1; }
        }
        return *p1++;
    }
    inline bool blank(char ch){ return ch==' '||ch=='\n'||ch=='\r'||ch=='\t'; }
    inline void read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for( ; blank(ch); ch=nc());
        if(IOerror) return;
        if(ch=='-') sign=1, ch=nc();
        for( ; ch>='0'&&ch<='9'; ch=nc()) x = x*10+ch-'0';
        if(sign) x=-x;
    }
    #undef BUF_SIZE
};
using namespace FastIO;
