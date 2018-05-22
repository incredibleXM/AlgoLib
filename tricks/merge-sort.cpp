int n;
int cnt;  //record the number of inverted sequence
int a[MAX_N];

void merge(int l, int m, int r)
{
    int n1 = m-l+1;
    int n2 = r-m;
    int* tmp1 = new int[n1+1];
    int* tmp2 = new int [n2+1];
    for(int i=0; i<n1; i++) tmp1[i] = a[l+i];
    for(int j=0; j<n2; j++) tmp2[j] = a[m+j+1];
    tmp1[n1] = INF; tmp2[n2] = INF;
    int i=0,j=0;
    for(int k=l; k<=r; k++){
        if(tmp1[i] <= tmp2[j]) {
            a[k] = tmp1[i];
            i++;
        }else{
            a[k] = tmp2[j];
            j++;
            if(tmp1[i] != INF) cnt+=n1-i;  //count the number of inverted sequence
        }
    }
    delete tmp1;
    delete tmp2;
}

void mergesort(int l, int r)
{
    int m;
    if(l < r) {
        m = (l+r)/2;
        mergesort(l, m);
        mergesort(m+1, r);
        merge(l, m, r);
    }
}
