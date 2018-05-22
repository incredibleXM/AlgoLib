struct Treap {
    int size;
    int key, fix;
    Treap *ch[2];
    Treap(int key) {
        size = 1;
        fix = rand();
        this->key = key;
        ch[0] = ch[1] = NULL;
    }
    int cmp(int x) const {
        if(x == key) return -1;
        return x < key ? 0 : 1;
    }
    void maintain() {
        size = 1;
        if(ch[0] != NULL) size += ch[0]->size;
        if(ch[1] != NULL) size += ch[1]->size;
    }
};

void rotate(Treap* &t, int d)
{
    Treap *k = t->ch[d^1];
    t->ch[d^1] = k->ch[d];
    k->ch[d] = t;
    t->maintain();
    k->maintain();
    t = k;
}

void insert(Treap* &t, int x)
{
    if(t == NULL) t = new Treap(x);
    else {
        int d = x < t->key ? 0 : 1;
        insert(t->ch[d], x);
        if(t->ch[d]->fix > t->fix)
            rotate(t, d^1);
    }
    t->maintain();
}

void deleteNode(Treap* &t, int x)
{
    int d = t->cmp(x);
    if(d == -1) {
        Treap *tmp = t;
        if(t->ch[0] == NULL) {
            t = t->ch[1];
            delete tmp;
            tmp = NULL;
        } else if(t->ch[1] == NULL) {
            t = t->ch[0];
            delete tmp;
            tmp = NULL;
        } else {
            int k = t->ch[0]->fix > t->ch[1]->fix ? 1 : 0;
            rotate(t, k);
            deleteNode(t->ch[k], x);
        }
    } else deleteNode(t->ch[d], x);
    if(t != NULL) t->maintain();
}

bool find(Treap *t, int x)
{
    while(t != NULL) {
        int d = t->cmp(x);
        if(d == -1) return true;
        t = t->d;
    }
    return false;
}

int kth(Treap *t, int k)
{
    if(t==NULL || k<=0 || k>t->size) return -1;
    if(t->ch[0]==NULL && k==1) return t->key;
    if(t->ch[0]==NULL) return kth(t->ch[1], k-1);
    if(t->ch[0]->size >= k) return kth(t->ch[0], k-1);
    if(t->ch[0]->size+1 == k) return t->key;
    return kth(t->ch[1], k-1-t->ch[0]->size);
}

int Rank(Treap *t, int x)
{
    int r;
    if(t->ch[0]==NULL) r=0;
    else  r = t->ch[0]->size;
    if(x == t->key) return r+1;
    if(x<t->key) return Rank(t->ch[0], x);
    return r+1 + Rank(t->ch[1], x);
}

void deleteTreap(Treap* &t)
{
    if(t==NULL) return;
    if(t->ch[0] != NULL) deleteTreap(t->ch[0]);
    if(t->ch[1] != NULL) deleteTreap(t->ch[1]);
    delete t;
    t = NULL;
}

void Print(Treap *t)
{
    if(t == NULL) return;
    Print(t->ch[0]);
    cout << t->key << endl;
    Print(t->ch[1]);
}
