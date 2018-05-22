typedef int SgTreeDataType;
struct treenode
{
    int L, R;
    SgTreeDataType sum, lazy;
    void update(SgTreeDataType v)
    {
        sum += (R-L+1)*v;
        lazy += v;
    }
} tree[MAX_N << 2];;

inline void push_down(int o)
{
    SgTreeDataType lazyval = tree[o].lazy;
    tree[2*o].update(lazyval); tree[2*o+1].update(lazyval);
    tree[o].lazy = 0;
}

inline void push_up(int o)
{
    tree[o].sum = tree[2*o].sum + tree[2*o+1].sum;
}

inline void build_tree(int L , int R , int o)
{
    tree[o].L = L, tree[o].R = R, tree[o].sum = tree[o].lazy = 0;
    if (R > L)
    {
        int mid = (L+R) >> 1;
        build_tree(L,mid,o*2);
        build_tree(mid+1,R,o*2+1);
    }
}

inline void update(int QL,int QR,SgTreeDataType v,int o)
{
    int L = tree[o].L, R = tree[o].R;
    if (QL <= L && R <= QR) tree[o].update(v);
    else
    {
        push_down(o);
        int mid = (L+R)>>1;
        if (QL <= mid) update(QL,QR,v,o*2);
        if (QR >  mid) update(QL,QR,v,o*2+1);
        push_up(o);
    }
}

inline SgTreeDataType query(int QL,int QR,int o)
{
    int L = tree[o].L , R = tree[o].R;
    if (QL <= L && R <= QR) return tree[o].sum;
    else
    {
        push_down(o);
        int mid = (L+R)>>1;
        SgTreeDataType res = 0;
        if (QL <= mid) res += query(QL,QR,2*o);
        if (QR > mid) res += query(QL,QR,2*o+1);
        push_up(o);
        return res;
    }
}
