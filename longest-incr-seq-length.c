static int find(int * tails, int l, int r, int q) {
    while (l < r) {
        int mid = (l + r) / 2;
        int tm = tails[mid];
        
        if (tm == q) return mid;
        
        if (tm > q) r = mid;
        else l = mid + 1;
    }
    return l;
}

int computeLongestIncreasingSubsequenceLength(int n, int quality_count, int* quality) {
    // tails[k] is min number of the tail of a seq with len k
    int * tails = calloc(n, sizeof(int));
    int t_size = 0;
    
    for (int i = 0; i < n; i++) {
        int q = quality[i];
        
        int idx = find(tails, 0, t_size, q);
        if (idx == t_size) {
            tails[t_size++] = q;
        } else {
            tails[idx] = q;
        }
    }
    
    return t_size;
}

