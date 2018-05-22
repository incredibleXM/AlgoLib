#include <bits/stdc++.h>
using namespace std;
int m, n; int a[50005]; int f[50005];
int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    a[0] = -0x3f3f3f3f;
    for(int i=1; i<=n; i++) cin >> a[i];
    f[0] = a[0]; m = 0;
    for(int i=1; i<=n; i++) {
        int x = lower_bound(f, f+m+1, a[i]) - f - 1; //if non-decreasing use upper_bound
        f[x+1] = a[i];
        if(x == m) m++;
    }
    cout << m << endl;
    return 0;
}
