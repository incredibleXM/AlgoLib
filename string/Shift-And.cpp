#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2000005;
const int SN = 505;
bitset<SN> state[256], p;
char str[MAXN];
int n, len;
char S[SN];

int main()
{
	while(scanf("%s", str) != EOF)
	{
		scanf("%d", &n);
		for(int i=0 ; i<256 ; i++)
			state[i].reset();
		for(int i=1; i<=n; i++) {
			scanf("%d", &len);
			scanf("%s", S);
			for(int j=0; j<len; j++)
				state[S[j]].set(i);
		}
		int l = strlen(str);
		bool flag = false;
		p.reset();
		for(int i=0; i<l; i++) {
			p.set(0);
			p = (p<<1) & state[str[i]];
			if(p.test(n)) {
				printf("%d\n", i-n+2);
				flag = true;
			}
		}
		if(!flag) printf("NULL\n");
	}
	return 0;
}
