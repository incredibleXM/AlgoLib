const int MAX_N = 1005;
int fa[MAX_N];   //father node
int sum[MAX_N];  //sum of nodes
int rank[MAX_N]; //height of tree

void init(int n)
{
    for(int i=0; i<n; i++) {
        fa[i] = i;
        sum[i] = 1;
        rank[i] = 0;
    }
}

int find(int x) //route compress
{
    int r = x;
    while(fa[r] != r) r = fa[r];

    int temp, head = r;
    r = x;
    while (fa[r] != r) {
        temp = fa[r];
        fa[r] = head;
        r = temp;
    }

    return head;
}

int find_recur(int x) //another implementation
{
    if(fa[x] != x) {
        fa[x] = find_recur(fa[x]);
    }
    return fa[x];
}

void unite(int x, int y)  //avoid worst situation(degenerate tree)
{
    int fx = find(x);
    int fy = find(y);
    if(fx == fy) return;
    if(rank[fx] < rank[fy]) {
        fa[fx] = fy;
        sum[fy] += sum[fx];
    } else {
        fa[fy] = fx;
        sum[fx] += sum[fy];
        if(rank[fx] == rank[fy]) rank[fx]++;
    }
}
