struct Trie {
    int ch[maxnode][sigma_size];
    int val[maxnode];
    int sz;
    Trie() { sz = 1; memset(ch[0], 0, sizeof(ch[0])); }
    int idx(char c) { return c - 'a'; }

    // 插入字符串s，附加信息为v。注意v必须非0，因为0代表“本结点不是单词结点”
    void insert(char *s, int v) {
        int u = 0, n = strlen(s);
        for(int i=0; i<n; i++) {
            int c = idx(s[i]);
            if(!ch[u][c]) { // 结点不存在
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0; // 中间结点的附加信息为0
                ch[u][c] = sz++; // 新建结点
            }
            u = ch[u][c]; // 往下走
        }
        val[u] = v; // 字符串的最后一个字符的附加信息为v
    }

    // 找字符串s的长度不超过len的前缀
    void find_prefixes(const char *s, int len, vector<int>& ans) {
        int u = 0;
        for(int i=0; i<len; i++) {
            if(s[i] == '\0') break;
            int c = idx(s[i]);
            if(!ch[u][c]) break;
            u = ch[u][c];
            if(val[u]) ans.push_back(val[u]);
        }
    }
};
