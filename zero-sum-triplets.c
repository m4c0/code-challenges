// Barely pass anything

#define HASH_LEN 199933

typedef struct node_s {
    int index;
    int reading;
    struct node_s * next;
    struct node_s * prev;
} node_t;

static inline int min(int a, int b) {
    return a < b ? a : b;
}

static inline int hkey(int i) {
    if (i < 0) i = ~i;
    return i % HASH_LEN;
}
static void add(node_t ** map, int idx, int rd) {
    int p = hkey(idx);

    node_t * n = malloc(sizeof(node_t));
    n->index   = idx;
    n->reading = rd;
    n->prev    = NULL;
    n->next    = map[p];
    
    if (map[p]) map[p]->prev = n;
    map[p] = n;
}
 
int** findZeroSumTripletsInWindow(int readings_count, int* readings, int windowSize, int* result_rows, int* result_columns) {
    if (readings_count < 3 || windowSize < 3) {
        *result_columns = *result_rows = 0;
        return NULL;
    }

    node_t ** map = calloc(HASH_LEN, sizeof(node_t *));
    for (int i = 1; i <= readings_count - 2; i++) {
        add(map, i, readings[i]);
    }
    
    int ** result = malloc(readings_count * sizeof(int **));
    int rows = 0;
    
    for (int i = 0; i <= readings_count - 2; i++) {
        int lim = min(readings_count, i + windowSize);
        
        for (int k = i + 2; k < lim; k++) {
            int psum = readings[i] + readings[k];
            
            for (node_t * m = map[hkey(-psum)]; m; m = m->next) {
                if (m->reading != -psum) continue;
                if (m->index <= i || m->index >= k) continue;
                
                // TODO: dedup
                int * r = result[rows] = malloc(3 * sizeof(int));
                r[0] = readings[i];
                r[1] = m->reading;
                r[2] = readings[k];
                rows++;
            }
        }
    }
    
    *result_rows = rows;
    *result_columns = 3;
    return result;
}

