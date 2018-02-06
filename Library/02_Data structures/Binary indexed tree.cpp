struct bit {
    vector<int> tree;
    int n;
    bit (int x) {
        n = (1 << (32 - __builtin_clz(x))) - 1;
        tree = vector<int>(n + 1);
    }
    int query (int x) {
        int sum = 0;
        for (; x; x -= -x & x) sum += tree[x];
        return sum;
    }
    void update (int x, int val) {
        for (; x <= n; x += -x & x) tree[x] += val;
    }
    int query (int l, int r) {
        return query(r) - query(l - 1);
    }
    void update (int l, int r, int val) {
        update(l, val); update(r + 1, -val);
    }

    //Frequencies have to be non-decreasing
    //Returns the first index of a given cumulative frequency
    //Always update up to tree.n
    int binary_search (int freq) {
        int bucket = 1 << (31 - __builtin_clz(n)), low = 0;
        for (; bucket && low < n; bucket >>= 1) {
            int mid = bucket + low;
            if (freq > tree[mid]) {
                low = mid;
                freq -= tree[mid];
            }
        }
        freq -= query(++low) - query(low - 1);
        return (freq != 0 ? -1 : low);
    }
};
