#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;
#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define X first
#define Y second
#define mp make_pair
#define eb emplace_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;
typedef unsigned long long uLL;

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





int main()
{
#ifdef ANONYM
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
    clock_t rtime = clock();
#endif




#ifdef ANONYM
    debug("time: %d\n",int(clock() - rtime));
#endif
    return 0;
}
