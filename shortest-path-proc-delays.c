static int solve(int from, int to, int n, int * h_times, int m, int ** routes, int * mask) {
    int res = -1;
    if (mask[from]) return -1;
    mask[from] = 1;
    
    for (int i = 0; i < m; i++) {
        int * route = routes[i];
        
        if (route[0] != from) continue;
        if (route[1] == to) {
            if (res == -1 || res > route[2]) res = route[2];
            continue;
        }
        
        int s = solve(route[1], to, n, h_times, m, routes, mask);
        if (s == -1) continue;
        
        s += h_times[route[1]] + route[2];
        
        if (res == -1 || res > s) res = s;
    }
    
    mask[from] = 0;
    return res;
}
 
int* computeShortestDeliveryTimes(int n, int handlingTimes_count, int* handlingTimes, int m, int routes_rows, int routes_columns, int** routes, int source, int* result_count) {
    int * res = malloc(n * sizeof(int));
    *result_count = n;
    
    int * mask = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        if (i == source) res[i] = 0;
        else res[i] = solve(source, i, n, handlingTimes, m, routes, mask);
    }
    return res;
}

