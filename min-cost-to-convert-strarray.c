static long levenshtein(const char * a, const char * b) {
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    
    long al = strlen(a);
    long bl = strlen(b);
    while (al > 0 && bl > 0 && a[al - 1] == b[bl - 1]) {
        al--;
        bl--;
    }
    
    if (al == 0) return bl;
    if (bl == 0) return al;
    
    static long * c0 = NULL, * c1 = NULL;
    if (!c0) c0 = malloc(1001 * sizeof(long));
    if (!c1) c1 = malloc(1001 * sizeof(long));
    
    for (int i = 0; i <= al; i++) c0[i] = i;
    
    long d = 0;
    for (int j = 1; j <= bl; j++) {
        c1[0] = j;
        for (int i = 1; i <= al; i++) {
            d = a[i - 1] == b[j - 1] ? 0 : 1;
            d += c0[i - 1];
            
            if (d > c0[i] + 1) d = c0[i] + 1;
            if (d > c1[i - 1] + 1) d = c1[i - 1] + 1;
            
            c1[i] = d;
        }
            
        long * tmp = c0;
        c0 = c1;
        c1 = tmp;
    }
    
    return d;
}

long minTransformationCost(int A_count, char** A, int B_count, char** B, int insertCost, int deleteCost) {
    if (A_count == 0) return (long)insertCost * B_count;
    if (B_count == 0) return (long)deleteCost * A_count;
    
    long * c0 = calloc(A_count + 1, sizeof(long));
    long * c1 = calloc(A_count + 1, sizeof(long));
    
    for (long i = 1; i <= A_count; i++) {
        c0[i] = i * deleteCost;
    }

    long d = 0;    
    for (long j = 1; j <= B_count; j++) {
        c1[0] = j * insertCost;
        for (long i = 1; i <= A_count; i++) {
            d = levenshtein(A[i - 1], B[j - 1]) + c0[i - 1];
            
            long du = c0[i] + insertCost;
            if (du < d) d = du;
            
            long dl = c1[i - 1] + deleteCost;
            if (dl < d) d = dl;
            
            c1[i] = d;
        }
        
        long * tmp = c0;
        c0 = c1;
        c1 = tmp;
    }
    return d;
}

