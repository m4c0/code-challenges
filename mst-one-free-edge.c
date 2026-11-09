// partial. Times out in 2 cases

static int comp_edge(const void * a, const void * b) {
    const int * const * aa = a;
    const int * const * bb = b;
    int ca = (*aa)[2];
    int cb = (*bb)[2];
    if (ca == cb) return 0;
    return ca < cb ? -1 : 1;
}

static int ind_jump(int * cids, int * cind, int n) {
    int i = cids[n];
    while (i != cind[i]) i = cind[i];
    return i;
}

long calculateMinimumSpanningTreeWeightWithFreeEdge(int n, int m, int edges_rows, int edges_columns, int** edges) {
    if (n <= 1) return 0;
    
    qsort(edges, edges_rows, sizeof(void *), comp_edge);
    
    int * cids = malloc(n * sizeof(int));
    int * cind = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        cids[i] = i;
        cind[i] = i;
    }
    
    long sum = 0;
    int last = 0;
    for (int i = 0; i < m; i++) {
        int * e = edges[i];
        int ca = ind_jump(cids, cind, e[0]);
        int cb = ind_jump(cids, cind, e[1]);
        
        if (ca == cb) {
            continue; // cycle
        }
        
        sum += e[2];
        last = e[2];
        
        cind[cb] = ca;
        cids[e[1]] = ca;
    }
    
    return sum - last;
}

