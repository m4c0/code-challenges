// pass 13/15 cases

static int levenshtein(const char * a, const char * b) {
    while (*a && *b) {
        if (*a != *b) break;
        a++;
        b++;
    }
    int al = strlen(a);
    int bl = strlen(b);
    if (al == 0) return bl;
    if (bl == 0) return al;
    
    static int * c0 = NULL, * c1 = NULL;
    if (!c0) c0 = malloc(1001 * sizeof(int));
    if (!c1) c1 = malloc(1001 * sizeof(int));
    
    for (int i = 0; i < al; i++) c0[i] = i;
    
    int d = 0;
    for (int j = 1; j <= bl; j++) {
        c1[0] = j;
        for (int i = 1; i <= al; i++) {
            d = a[i - 1] == b[j - 1] ? 0 : 1;
            d += c0[i - 1];
            
            if (d > c0[i] + 1) d = c0[i] + 1;
            if (d > c1[i - 1] + 1) d = c1[i - 1] + 1;
            
            c1[i] = d;
        }
            
        int * tmp = c0;
        c0 = c1;
        c1 = tmp;
    }
    
    return d;
}

long minTransformationCost(int A_count, char** A, int B_count, char** B, int insertCost, int deleteCost) {
    if (A_count == 0) return insertCost * B_count;
    if (B_count == 0) return deleteCost * A_count;
    
    long * c0 = calloc(A_count + 1, sizeof(long));
    long * c1 = calloc(A_count + 1, sizeof(long));
    
    for (int i = 1; i <= A_count; i++) {
        c0[i] = i * insertCost;
    }

    long d = 0;    
    for (int j = 1; j <= B_count; j++) {
        c1[0] = j * deleteCost;
        for (int i = 1; i <= A_count; i++) {
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

