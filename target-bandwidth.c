static int int_comp(const void * a, const void * b) {
    const int * aa = a;
    const int * bb = b;
    if (*aa == *bb) return 0;
    return *aa < *bb ? 1 : -1;
}

static int find(int * arr, int n, int val) {
    if (val == 0) return 0;
    
    // fprintf(stderr, "find %d %d\n", n, val);
    int min = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] > val) continue;
        if (arr[i] == val) {
            // fprintf(stderr, "-- found %d\n", val);
            return 1;
        }
        
        int rest = val - arr[i]; // FIXME: overflows?
        int res = find(arr + i, n - i, rest);
        if (res == -1) continue;
        
        int r = 1 + res;
        if (min == -1 || min > r) min = r;
    }
    // fprintf(stderr, "found %d %d = %d\n", n, val, min);
    return min;
}

int findMinimumPlansForBandwidth(int planSizes_count, int* planSizes, int targetBandwidth) {
    qsort(planSizes, planSizes_count, sizeof(int), int_comp);
    
    return find(planSizes, planSizes_count, targetBandwidth);
}

