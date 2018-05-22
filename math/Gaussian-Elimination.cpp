//float number
const double eps = 1e-8;
typedef vector<double> vec;
typedef vector<vec> mat;

void print(const mat& s) //debug function
{
    int m = s.size();
    int n = s[0].size();
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            cout << s[i][j] << " ";
        }
        cout << endl;
    }
}

pair<int, vec> gauss_elimination(const mat& A, const vec& b) //method 1
{
    int m = A.size();
    int n = A[0].size();

    mat B(m, vec(n+1));
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            B[i][j] = A[i][j];
        }
        B[i][n] = b[i];
    }

    bool flag = false, manySolution = false;
    for(int i=0; i<n; i++) {
        flag = false;
        for(int j=i; j<m; j++) {
            if(fabs(B[j][i]) > eps) {
                swap(B[j], B[i]);
                flag = true;
                break;
            }
        }

        if(!flag) { // rank of matrix < n
            manySolution = true;
            continue;
        }

        for(int j=i+1; j<m; j++) {
            double tmp = B[j][i];
            for(int k=i; k<=n; k++) {
                B[j][k] -= B[i][k]*tmp/B[i][i];
            }
        }
    }

    for(int i=m-1; i>=0; i--) {
        bool zero = true;
        for(int j=0; j<n; j++) {
            if(fabs(B[i][j]) > eps) {
                zero = false;
                break;
            }
        }
        if(zero && fabs(B[i][n])>eps) return make_pair(-1, vec());
    }

    if(manySolution) return make_pair(1, vec());

    vec x(n);
    for(int i=n-1; i>=0; i--) {
        for(int j=i+1; j<n; j++) {
            B[i][n] -= B[i][j]*x[j];
        }
        x[i] = B[i][n] / B[i][i];
    }
    return make_pair(0, x);
}


vec gauss_jordan(const mat& A, const vec& b) //method 2
{
    int n = A.size();
    mat B(n, vec(n+1));
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            B[i][j] = A[i][j];
        }
    }
    for(int i=0; i<n; i++) B[i][n] = b[i];

    for(int i=0; i<n; i++) {
        //change max unknown coefficient to i-th row
        int pivot = i;
        for(int j=i; j<n; j++) {
            if(fabs(B[j][i]) > fabs(B[pivot][i]))
                pivot = j;
        }
        swap(B[i], B[pivot]);

        //no solution or infinite solution
        if(fabs(B[i][i]) < eps) return vec();

        for(int j=i+1; j<=n; j++) B[i][j] /= B[i][i];
        for(int j=0; j<n; j++) {
            if(i != j) {
                for(int k=i+1; k<=n; k++) {
                    B[j][k] -= B[j][i] * B[i][k];
                }
            }
        }
    }

    vec x(n);
    for(int i=0; i<n; i++) x[i] = B[i][n];
    return x;
}

//xor equation set
typedef vector<int> vec;
typedef vector<vec> mat;

pair<int, vec> gauss_xor(const mat& A, const vec& b) //method 1
{
    int m = A.size();
    int n = A[0].size();

    mat B(m, vec(n+1));
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            B[i][j] = A[i][j];
        }
        B[i][n] = b[i];
    }

    bool flag = false, manySolution = false;
    for(int i=0; i<n; i++) {
        flag = false;
        for(int j=i; j<m; j++) {
            if(B[j][i]) {
                swap(B[j], B[i]);
                flag = true;
                break;
            }
        }

        if(!flag) { // rank of matrix < n
            manySolution = true;
            continue;
        }

        for(int j=i+1; j<m; j++) {
            if(B[j][i]) {
                for(int k=i; k<=n; k++) {
                    B[j][k] ^= B[i][k];
                }
            }
        }
    }

    for(int i=m-1; i>=0; i--) {
        bool zero = true;
        for(int j=0; j<n; j++) {
            if(B[i][j]) {
                zero = false;
                break;
            }
        }
        if(zero && B[i][n]) return make_pair(-1, vec());
    }

    if(manySolution) return make_pair(1, vec());

    vec x(n);
    for(int i=n-1; i>=0; i--) {
        for(int j=i+1; j<n; j++) {
            if(B[i][j])
                B[i][n] ^= x[j];
        }
        x[i] = B[i][n];
    }
    return make_pair(0, x);
}

int gauss_xor(const mat& A, const vec& b) //return number of free variable
{
    int m = A.size();
    int n = A[0].size();

    mat B(m, vec(n+1));

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            B[i][j] = A[i][j];
        }
        B[i][n] = b[i];
    }

    int i=0, j=0, k, r, u;
    while(i<m && j<n) {
        r = i;
        for(k=i; k<m; k++) if(B[k][j]) { r = k ; break;}
        if(B[r][j]) {
            if(r != i) swap(B[r], B[i]);
            for(u=i+1; u<m; u++) {
                if(B[u][j]) {
                    for(k=i; k<=n; k++) {
                        B[u][k] ^= B[i][k];
                    }
                }
            }
            i++;
        }
        j++;
    }
    return n-i;
}

//congruential equation set
typedef vector<int> vec;
typedef vector<vec> mat;

const int mod = prime;

inline int gcd(int a, int b)
{
    while(b != 0) {
        int t = b;
        b = a%b;
        a = t;
    }
    return a;
}
inline int lcm(int a, int b)
{
    return a/gcd(a,b)*b;
}
long long inv(long long a, long long m)
{
    if(a == 1) return 1;
    return inv(m%a,m)*(m-m/a)%m;
}

pair<int, vec> Gauss(const mat& A, const vec& b)
{
    int n = A.size(), m = A[0].size();
    mat B(n, vec(m+1));
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            B[i][j] = A[i][j];
        }
    }
    for(int i=0; i<n; i++) B[i][m] = b[i];

    int max_r, col, k;
    for(k = 0, col = 0; k < n && col < m; k++,col++) {
        max_r = k;
        for(int i = k+1; i < n; i++)
            if(abs(B[i][col]) > abs(B[max_r][col]))
                    max_r = i;
        if(B[max_r][col] == 0) {
            k--;
            continue;
        }
        if(max_r != k)
            for(int j = col; j < var+1; j++)
                swap(B[k][j], B[max_r][j]);
        for(int i = k+1; i < equ; i++) {
            if(B[i][col] != 0) {
                int LCM = lcm(abs(B[i][col]), abs(B[k][col]));
                int ta = LCM / abs(B[i][col]);
                int tb = LCM / abs(B[k][col]);
                if(B[i][col] * B[k][col] < 0) tb = -tb;
                for(int j = col; j < var+1; j++)
                    B[i][j] = ((B[i][j]*ta - B[k][j]*tb)%mod + mod)%mod;
            }
        }
    }
    for(int i = k; i < n; i++)
            if(B[i][col] != 0)
                    return make_pair(-1, vec()); //no solution
    if(k < m) return make_pair(m-k, vec()); //more than one solution
    vec x(m);
    for(int i = m-1; i >= 0; i--) {
        int temp = B[i][m];
        for(int j = i+1; j < m; j++) {
            if(B[i][j] != 0) {
                temp -= B[i][j] * x[j];
                temp = (temp%mod + mod)%mod;
            }
        }
        x[i] = (temp*inv(B[i][i],mod))%mod;
    }
    return make_pair(0, x); //correct solution
}
