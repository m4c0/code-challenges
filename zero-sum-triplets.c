// Only pass 8/16

#define HASH_LEN 199933

typedef struct node_s {
    int index;
    int reading;
    struct node_s * next;
} node_t;
typedef struct result_s {
    int * triplet;
    struct result_s * next;
} result_t;

static inline int min(int a, int b) {
    return a < b ? a : b;
}

static inline int hkey(int i) {
    if (i < 0) i = ~i;
    return i % HASH_LEN;
}
static void add_node(node_t ** map, int idx, int rd) {
    int p = hkey(rd);

    node_t * n = malloc(sizeof(node_t));
    n->index   = idx;
    n->reading = rd;
    n->next    = map[p];
    
    map[p] = n;
}

static inline int hkey_result(int * r) {
    int a = hkey(r[0]);
    int b = hkey(r[1]);
    int c = hkey(r[2]);
    return hkey(a * 337 + b * 13 + c);
}
static int add_result(result_t ** map, int * res) {
    int p = hkey_result(res);
    
    for (result_t * r = map[p]; r; r = r->next) {
        if (r->triplet[0] != res[0]) continue;
        if (r->triplet[1] != res[1]) continue;
        if (r->triplet[2] != res[2]) continue;
        return 0;
    }

    result_t * n = malloc(sizeof(result_t));
    n->triplet = res;
    n->next    = map[p];
    
    map[p] = n;
    return 1;
}

int** findZeroSumTripletsInWindow(int readings_count, int* readings, int windowSize, int* result_rows, int* result_columns) {
    if (readings_count < 3 || windowSize < 3) {
        *result_columns = *result_rows = 0;
        return NULL;
    }

    node_t ** map = calloc(HASH_LEN, sizeof(node_t *));
    for (int i = 0; i <= readings_count - 1; i++) {
        add_node(map, i, readings[i]);
    }
        
    result_t ** resmap = calloc(HASH_LEN, sizeof(int **));
    int rows = 0;
    
    for (int i = 0; i <= readings_count - 2; i++) {
        int lim = min(readings_count, i + windowSize);
        
        for (int k = i + 2; k < lim; k++) {
            int psum = readings[i] + readings[k];
            
            for (node_t * m = map[hkey(-psum)]; m; m = m->next) {
                if (m->reading != -psum) continue;
                if (m->index <= i || m->index >= k) continue;
                
                int * r = malloc(3 * sizeof(int));
                r[0] = readings[i];
                r[1] = m->reading;
                r[2] = readings[k];
                if (add_result(resmap, r)) {
                    rows++;
                } else {
                    free(r);
                }
            }
        }
    }
    
    *result_rows = rows;
    *result_columns = 3;
    
    int ** result = malloc(rows * sizeof(int *));
    for (int i = 0; i < HASH_LEN; i++) {
        for (result_t * r = resmap[i]; r; r = r->next) {
            result[--rows] = r->triplet;
        }
    }
    return result;
}

