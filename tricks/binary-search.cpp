int a[n];

//the first value equal to key
int bs(int key)
{
    int l = 0;
    int r = n-1;

    while(l <= r) {
        int m = l + (r-l>>1);
        if(a[m] >= key) r = m-1;
        else l = m+1;
    }

    if(l<n && a[l]==key) return l;
    return -1;
}

//the last value equal to key
int bs(int key)
{
    int l = 0;
    int r = n-1;

    while(l <= r) {
        int m = l + (r-l>>1);
        if(a[m] <= key) l = m+1;
        else r = m-1;
    }

    if(r>=0 && a[r]==key) return l;
    return -1;
}


//the last value <= key
int bs(int key)
{
    int l = 0;
    int r = n-1;

    while(l <= r) {
        int m = l + (r-l>>1);
        if(a[m] > key) r = m-1;
        else l = m+1;
    }

    return r;
}

//the last value < key
int bs(int key)
{
    int l = 0;
    int r = n-1;

    while(l <= r) {
        int m = l + (r-l>>1);
        if(a[m] >= key) r = m-1;
        else l = m+1;
    }

    return r;
}

//the first value >= key
int bs(int key)
{
    int l = 0;
    int r = n-1;

    while(l <= r) {
        int m = l + (r-l>>1);
        if(a[m] >= key) r = m-1;
        else l = m+1;
    }

    return l;
}

//the first value > key
int bs(int key)
{
    int l = 0;
    int r = n-1;

    while(l <= r) {
        int m = l + (r-l>>1);
        if(a[m] > key) r = m-1;
        else l = m+1;
    }

    return l;
}
