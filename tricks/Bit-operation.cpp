0                    //empty
1<<i                 //{i}
(1<<n)-1             //{0,1,2,...,n-1}
if(S>>i&1)           //determine whether i is in set S
S|1<<i               //add i to set S
S&~(1<<i)            //delete i in set S
S|T                  //union of S and T
S&T                  //intersection of S and T

//enumeration
for(int S=0; S<1<<n; S++) {
    // operation on subset
}
//descend order
int sub = sup;
do {
    //operation on subset
    sub = (sub-1) & sup;
} while(sub != sup);

//all of subset whose size is k
int comb = (1<<k) - 1;
while(comb < 1<<n) {
    //operation
    int x = comb & -comb, y = comb + x;
    comb = ((comb & ~y) / x>>1) | y;
}

// 最低位1后有多少0
int __builtin_ctz(unsigned int x)
int __builtin_ctzll(unsigned long long x)

// 有多少位1
int __builtin_popcount(unsigned int x)
int __builtin_popcountll(unsigned long long x)

// lowbit: 最低位的1以及其后的0构成的数值
n & (-n)
