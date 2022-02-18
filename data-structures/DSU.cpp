struct DSU {
    int p[100005] = {};
    DSU() { memset(p, -1, sizeof p); }
    void init() { memset(p, -1, sizeof p); }
    int root(int x) { return p[x] < 0 ? x : p[x] = root(p[x]); }
    bool mer(int x, int y) {
        if ((x = root(x)) == (y = root(y))) return 0;
        if (p[y] < p[x]) swap(x, y);
        p[x] += p[y]; p[y] = x; return 1;
    }
};