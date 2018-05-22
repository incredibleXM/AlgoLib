//O(|V|^3)
int d[MAX_V][MAX_V];  //weight of (u, v), when non-existent it will be set as INF, d[i][i] = 0
int V;

void floyd()
{
    for(int k=0; k<V; k++)
        for(int i=0; i<V; i++)
            for(int j=0; j<V; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
