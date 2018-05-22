#include <bits/stdc++.h>
using namespace std;
int n, V, c[105], w[105], f[10005];
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> V;
    for(int i=1; i<=n; i++) {
        cin >> c[i] >> w[i];
    }
    for(int i=1; i<=n; i++) {
        for(int j=V; j>=c[i]; j--) {
            f[j] = max(f[j], f[j-c[i]] + w[i]);
        }
    }
    cout << f[V] << endl;
    return 0;
}
