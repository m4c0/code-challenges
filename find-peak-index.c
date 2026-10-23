static inline int recurse(int * counts, int64_t l, int64_t r) {
    int64_t mid = (r + l) / 2;
    
    int c_l = counts[l];
    int c_mid = counts[mid];
    int c_r = counts[r];
    
    if (r == l) return l;
    if (r == l + 1) return c_l > c_r ? l : r;
    
    if (c_l > c_mid) return recurse(counts, l, mid);
    if (c_r > c_mid) return recurse(counts, mid, r);
        
    int rec_l = recurse(counts, l, mid);
    int rec_r = recurse(counts, mid, r);
    return counts[rec_l] > counts[rec_r] ? rec_l : rec_r;
}

int findPeakIndex(int counts_count, int* counts) {
    int res = recurse(counts, 0, counts_count - 1);
    return res;
}
