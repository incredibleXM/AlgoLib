#include <bits/stdc++.h>
using namespace std;
const int M = 1000005;
int fir[M];
int sec[M];
char ch[M];
int s[M];
int sum;

void init() {
    fir[0] = sec[0] = s[0] = 0;
    sum = 1;
}
void insert(char* str) {
    int cur, h=0;
    int len = strlen(str);
    s[0]++;
    for(int i=0; i<len; i++) {
        bool f = false;
        for(cur = fir[h]; cur != 0; cur = sec[cur]) {
            if(ch[cur] == str[i]){
                f = true;
                break;
            }
        }
        if(f) s[cur]++;
        if(!f) {
            cur = sum++;
            s[cur] = 1;
            ch[cur] = str[i];
            sec[cur] = fir[h];
            fir[h] = cur;
            fir[cur] = 0;
        }
        h = cur;
    }
}

void query(char* str)
{
    int cur, h=0;
    int len = strlen(str);
    for(int i=0; i<len; i++) {
        bool f = false;
        for(cur = fir[h]; cur != 0; cur = sec[cur]) {
            if(ch[cur] == str[i]){
                f = true;
                break;
            }
        }
        if(!f) {printf("%d\n", 0); return;}
        if(i == len-1) {
            printf("%d\n", s[cur]);
            return;
        }
        h = cur;
    }
}
int n, m;
char t[12];
int main()
{
    init();
    scanf("%d", &n);
    while(n--) {
        scanf("%s", t);
        insert(t);
    }
    scanf("%d", &m);
    while(m--) {
        scanf("%s", t);
        query(t);
    }
}
