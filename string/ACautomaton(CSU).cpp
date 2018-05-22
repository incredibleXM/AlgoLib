/*
*version: csu
*/
#include <bits/stdc++.h>
#define clr(x,y) memset(x,y,sizeof(x))
using namespace std;

const int maxnode = 1000000 + 10;
const int SIGMA_SIZE = 26;
const int maxl = 55;

char T[maxnode],P[maxl];
int sz;
int ch[maxnode][SIGMA_SIZE];
int val[maxnode],f[maxnode];

void init(){ sz=1;clr(ch[0],0); clr(val,0); }

void insert(char* s){
    int n = strlen(s);
    int u = 0;
    for(int i = 0; i < n; i++){
        int c = s[i] - 'a';
        if (!ch[u][c]){
            clr(ch[sz], 0);
            val[sz] = 0;
            ch[u][c] = sz++;
        }
        u = ch[u][c];
    }
    val[u]++;
}

void getFail(){
    queue<int> Q;
    f[0] = 0;
    for(int c = 0; c < SIGMA_SIZE; c++){
        int u = ch[0][c];
        if (u) { Q.push(u); f[u] = 0; }
    }
    while(!Q.empty()){
        int r = Q.front(); Q.pop();
        for(int c = 0; c < SIGMA_SIZE; c++){
            int u = ch[r][c];
            if (!u) { ch[r][c] = ch[f[r]][c]; continue;}
            f[u] = ch[f[r]][c];
            Q.push(u);
        }
    }
}

int solve(char* s){
    int n = strlen(s);
    int u = 0, ans = 0;
    for(int i = 0; i < n; i++){
        int c = s[i] - 'a';
        u = ch[u][c];
        int v = u;
        while(v && val[v]) { ans += val[v]; val[v] = 0; v = f[v]; }
    }
    return ans;
}

int main()
{
    int t; scanf("%d",&t);
    while(t--){
        init();
        int n; scanf("%d",&n);
        while(n--){ scanf("%s",P); insert(P);};
        getFail();
        scanf("%s",T);
        printf("%d\n",solve(T));
    }
    return 0;
}
